#include "VirtualMachine.h"

using namespace std;

VirtualMachine::VirtualMachine(){
	populateMemory(); //set base and limit in there
	//start fetch-decode-execute cycle
	while (pc != limit){
    	ir = mem[pc++]; //fetch
    	execute();
      cout << endl << "SR:  " << sr <<endl;
    	}
    cout << "yues this is current" << endl;

}

void VirtualMachine::populateMemory(){
	//initialize memory and registers
	r = vector <unsigned> (REG_FILE_SIZE);
	mem = vector <unsigned> (MEM_SIZE);
	pc = 0;

	//open and populate memory
	fstream prog;
	prog.open("prog.o");
	//check if its open
	string line, temp;
	istringstream iss;
	getline(prog, line);
	while(!prog.eof()){
		mem[pc++] = (unsigned)atoi(line.c_str());
		getline(prog, line);
	}

	//set mem base and limits
	limit = pc;
	pc = base = __clock = sr = 0;
    sp = 255;

	populateFunctionMap();
}

void VirtualMachine::execute(){
	instruction ins(ir); // include in class to optimize. repeated instantiations -> performance cost
    cout << ins.i << endl;
    cout << ins.f1.OP << " " << ins.f1.RD << " " << ins.f1.I << " " << ins.f1.RS << " " << ins.f1.UNUSED << endl;
    cout << ins.f2.OP << " " << ins.f2.RD << " " << ins.f2.I << " " << ins.f2.ADDR << endl;
    cout << ins.f3.OP << " " << ins.f3.RD << " " << ins.f3.I << " " << ins.f3.CONST << endl;
    cout << "SR :  " << sr << endl;	
    if(ins.f1.I)
		(this->*instr_1_immed[ins.f1.OP])(ins);  // ==  (functionName)(); functionName.base == beginning addr in mem loc
	else
		(this->*instr_0_immed[ins.f1.OP])(ins);

    cout << "PC:  " << pc <<  "   r[0]    " << r[0] << "   r[1]   " << r[1] << "  r[2]  " << r[2] << "  r[3]  " << r[3] << endl<< endl;
}


void VirtualMachine::setCarryBit(){
	sr |= 1;
}

void VirtualMachine::setLessBit(){
	sr &= 25; // set less, equal, and greater bit to zero, AND 010001 preserves state of overflow and carry bits.
	sr |= 8;
    cout << endl << " set less bit  " << sr << endl;
}


void VirtualMachine::setEqualBit(){
	sr &= 21;
	sr |= 4;
}

void VirtualMachine::setGreaterBit(){
	sr &= 19;
	sr |= 2;
    cout << endl << "setGreaterBit   " << sr << endl;
}

bool VirtualMachine::isLessBit(){
  if ( (sr & 8) == 8 )
		return true;
	return false;
}

bool VirtualMachine::isGreaterBit(){
    cout << endl << "SR   "  << sr << endl;
	if ( (sr & 2) == 2){
		return true;
        cout << endl << "true" << endl;
    }
	return false;
}

bool VirtualMachine::isEqualBit(){
	if ( (sr & 4) == 4){
		cout << endl << sr << "  is EQUAL " << endl;
        return true;
    }
	return false;
}

void VirtualMachine::populateFunctionMap(){
	instr_0_immed = {
        { 0 , &VirtualMachine::LOAD },
        { 2 , &VirtualMachine::ADD },
        { 3 , &VirtualMachine::ADDC },
        { 4 , &VirtualMachine::SUB },
        { 5 , &VirtualMachine::SUBC },
        { 6 , &VirtualMachine::AND },
        { 7 , &VirtualMachine::XOR },
        { 8 , &VirtualMachine::COMPL },
        { 9 , &VirtualMachine::SHL },
        { 10 , &VirtualMachine::SHLA },
        { 11 , &VirtualMachine::SHR },
        { 12 , &VirtualMachine::SHRA },
        { 13 , &VirtualMachine::COMPR },
        { 14 , &VirtualMachine::GETSTAT },
        { 15 , &VirtualMachine::PUTSTAT },
        { 21 , &VirtualMachine::RETURN },
        { 22 , &VirtualMachine::READ },
        { 23 , &VirtualMachine::WRITE },
        { 24 , &VirtualMachine::HALT },
        { 25 , &VirtualMachine::NOOP }
        
    };
    instr_1_immed = {
        { 0 , &VirtualMachine::LOADI },
        { 1 , &VirtualMachine::STORE },
        { 2 , &VirtualMachine::ADDI },
        { 3 , &VirtualMachine::ADDCI },
        { 4 , &VirtualMachine::SUBI },
        { 5 , &VirtualMachine::SUBCI },
        { 6 , &VirtualMachine::ANDI },
        { 7 , &VirtualMachine::XORI },
        { 13 , &VirtualMachine::COMPRI },
        { 16 , &VirtualMachine::JUMP },
        { 17 , &VirtualMachine::JUMPL },
        { 18 , &VirtualMachine::JUMPE },
        { 19 , &VirtualMachine::JUMPG },
        { 20 , &VirtualMachine::CALL }

    };
}

void VirtualMachine::LOAD(instruction &ins){
    r[ins.f2.RD] = mem[ins.f2.ADDR];
    __clock += 4;
    cout << endl << "exit LOAD" << endl;

}

void VirtualMachine::LOADI(instruction &ins){
    r[ins.f3.RD] = ins.f3.CONST;
    __clock++;

    cout << endl << "exit LOADI  " << sr << endl;
}

void VirtualMachine::STORE(instruction &ins){
    cout << endl << "mem  "  << ins.f2.ADDR << "   " << r[ins.f2.RD] << endl;
    mem[ins.f2.ADDR] = r[ins.f2.RD];
    __clock += 4;
    cout << endl << "exit STORE   " << mem[ins.f2.ADDR] << endl;

}


void VirtualMachine::ADD(instruction &ins){
    r[ins.f1.RD] += r[ins.f1.RS];
    if (r[ins.f1.RD] > 65535){
        setCarryBit();
        //r[ins.f1.RD] &= 65535;
    }
    else{
        zeroCarryBit();
    }

    __clock++;
}

void VirtualMachine::ADDI(instruction &ins){
    r[ins.f3.RD] += ins.f3.CONST;
    if ( r[ins.f3.RD] > 65535 && r[ins.f3.RD] < 131070){
        setCarryBit();
        r[ins.f3.RD] &= 65535;
    }
    else if ((~r[ins.f3.RD] + 1) > 65535 && (~r[ins.f3.RD] + 1 ) < 131070){
        setCarryBit();
        r[ins.f3.RD] = -65535;
        cout << endl << "second else if  " << endl;
    }

    __clock++;
}

void VirtualMachine::ADDC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] + r[ins.f1.RS] + (sr & 1);
    if ( r[ins.f3.RD] > 65535 && r[ins.f3.RD] < 131070){
        setCarryBit();
        r[ins.f3.RD] &= 65535;
    }
    else if ((~r[ins.f3.RD] + 1) >= 131070){
        setCarryBit();
        r[ins.f3.RD] = -65535;
    }
    __clock++;
}

void VirtualMachine::ADDCI(instruction &ins){
    r[ins.f3.RD] = r[ins.f3.RD] + r[ins.f3.CONST] + (sr & 1);
    if ( r[ins.f3.RD] > 65535 && r[ins.f3.RD] < 131070){
        setCarryBit();
        r[ins.f3.RD] &= 65535;
    }
    else if ((~r[ins.f3.RD] + 1) > 131070){
        setCarryBit();
        r[ins.f3.RD] = -65535;
    }
    __clock++;
}

void VirtualMachine::SUB(instruction &ins){
    r[ins.f1.RD] -= r[ins.f1.RS];
    if ( r[ins.f3.RD] > 65535 && r[ins.f3.RD] < 131070){
        setCarryBit();
        r[ins.f3.RD] &= 65535;
    }
    else if ((~r[ins.f3.RD] + 1) > 131070){
        setCarryBit();
        r[ins.f3.RD] = -65535;
    }

    __clock++;
}

void VirtualMachine::zeroCarryBit(){
    sr &= 30;
}

void VirtualMachine::SUBI(instruction &ins){
    r[ins.f3.RD] -= ins.f3.CONST;
    if ((int)r[ins.f3.RD] > 65535 || (int)r[ins.f3.RD] < -65535)
        setCarryBit();
    else
        zeroCarryBit();

    cout << endl << "exit SUBI" << endl;

    __clock++;
}

void VirtualMachine::SUBC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] - r[ins.f1.RS] - (sr & 1);
    if ((~r[ins.f3.RD] + 1 ) > 65535)
        setCarryBit();
    
    __clock++;
}

void VirtualMachine::SUBCI(instruction &ins){
    r[ins.f3.RD] = r[ins.f3.RD] - ins.f3.CONST - (sr & 1);
    if ((~r[ins.f3.RD] + 1) > 65535)
        setCarryBit();
    
    __clock++;
}

void VirtualMachine::AND(instruction &ins){
    r[ins.f1.RD] &= r[ins.f1.RS];
}

void VirtualMachine::ANDI(instruction &ins){
    r[ins.f3.RD] &= ins.f3.CONST;

    cout << endl << "exit ANDI" << endl;

}

void VirtualMachine::XOR(instruction &ins){
    r[ins.f1.RD] ^= r[ins.f1.RS];
}

void VirtualMachine::XORI(instruction &ins){
    r[ins.f3.RD] ^= ins.f3.CONST;
}

void VirtualMachine::COMPL(instruction &ins){
    r[ins.f1.RD] = ~r[ins.f1.RD];
}

void VirtualMachine::SHL(instruction &ins){
    r[ins.f1.RD] <<= 1;
    cout << endl << "exit SHL" << endl;

}

void VirtualMachine::SHLA(instruction &ins){
	if(r[ins.f1.RD] & 1 == 1){
		r[ins.f1.RD] <<= 1;
		r[ins.f1.RD] |= 1;
	}
	else
		r[ins.f1.RD] <<= 1;
 
}

void VirtualMachine::SHR(instruction &ins){
    if ((r[ins.f1.RD] & 1) == 1)
        setCarryBit();
    else
        zeroCarryBit();
    
    r[ins.f1.RD] >>= 1;
    cout << endl << "exit SHR" << endl;

}

void VirtualMachine::SHRA(instruction &ins){
    if ( r[ins.f1.RD] >> 15 == 1 ){  //if 
	r[ins.f1.RD] >>= 1;
	r[ins.f1.RD] |= 32768;	
    }
    else
	r[ins.f1.RD] >>= 1;
}

void VirtualMachine::COMPR(instruction &ins){
    if (r[ins.f1.RD] < r[ins.f1.RS])
        setLessBit();
    else if (r[ins.f1.RD] == r[ins.f1.RS])
        setEqualBit();
    else
        setGreaterBit();
}

void VirtualMachine::COMPRI(instruction &ins){
    if(r[ins.f3.RD]< ins.f3.CONST)
       setLessBit();
    else if(r[ins.f3.RD] == ins.f3.CONST)
        setEqualBit();
    else
        setGreaterBit();
    cout << endl << "exit COMPRI" << endl;

}

void VirtualMachine::GETSTAT(instruction &ins){
    r[ins.f1.RD] = sr;

    cout << endl << "exit getstat" << endl;

}

void VirtualMachine::PUTSTAT(instruction &ins){
    sr = r[ins.f1.RD];
}

void VirtualMachine::JUMP(instruction &ins){
    pc = ins.f2.ADDR;
}

void VirtualMachine::JUMPL(instruction &ins){
    if(isLessBit())
        pc = ins.f2.ADDR;
}

void VirtualMachine::JUMPE(instruction &ins){
    if(isEqualBit())
        pc = ins.f2.ADDR;
    cout << endl << "exit JUMPE" << endl;

}

void VirtualMachine::JUMPG(instruction &ins){
    cout << endl << " exit JUMPG" << endl;
	if(isGreaterBit())
        pc = ins.f2.ADDR;
}

void VirtualMachine::CALL(instruction &ins){
	//push VM status
	mem[sp--] = sr;
	mem[sp--] = ir;
	mem[sp--] = r[0];
	mem[sp--] = r[1];
	mem[sp--] = r[2];
	mem[sp--] = r[3];
	mem[sp--] = pc;

	//jump to new location in mem
    pc = ins.f2.ADDR;
    cout << "inside call " << endl;
}

void VirtualMachine::RETURN(instruction &ins){
	//pull VM status
    ++sp; //sp is pointing at free space, ready to push status.  need to bring back up to current head before assignments
	pc = mem[sp++];
	r[3] = mem[sp++];
	r[2] = mem[sp++];
	r[1] = mem[sp++];
	r[0] = mem[sp++];
	ir = mem[sp++];
	sr = mem[sp];

    cout << endl << "exit RETURN" << endl;

}

void VirtualMachine::READ(instruction &ins){
	fstream prog;
	prog.open("VirtualMachine.in");
	if (!prog.is_open())
		exit(3);
	string line;
	getline(prog, line);
	r[ins.f1.RD] = (unsigned)atoi(line.c_str()); //effecient method for string to int cast
	prog.close();
    cout << endl << r[ins.f1.RD] << endl;

    cout << endl << "exit read" << endl;

}

void VirtualMachine::WRITE(instruction &ins){
	ofstream ofs;
	ofs.open ("VirtualMachine.out", ofstream::out);
	if (!ofs.is_open())
		exit(2);
	ofs << to_string(r[ins.f1.RD]); //an effecient method for string casting
	ofs.close();
    cout << endl << "did it" << endl;
    cout << endl << "exit WRITE" << endl;

}

void VirtualMachine::HALT(instruction &ins){
	
    cout << endl << "exit HALT" << endl;

    exit(0);
}

void VirtualMachine::NOOP(instruction &ins){

    cout << endl << "exit NOOP" << endl;

	void(0);
}


