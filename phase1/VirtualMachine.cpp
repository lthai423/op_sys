#include "VirtualMachine.h"

using namespace std;

VirtualMachine::VirtualMachine(){
	populateMemory(); //set base and limit in there

	//start fetch-decode-execute cycle
	while (pc < limit){
	ir = mem[pc++] //fetch
	execute(); //
	}
}

void VirtualMachine::populateMemory(){
	__clock = 0;
	r = vector <int> (REG_FILE_SIZE);
	mem = vector <int> (MEM_SIZE);
	fstream prog;
	prog.open("prog.o");
	string line, temp;
	istringstream iss;
	getline(prog, line);
	int i;
	while(!prog.eof()){
	    iss << temp; //ensures no whitespace
	mem[i++] = (uint16_t)atoi(temp.c_str());
	}
	base = 0;
	limit = i;
	//memory is now populated
}

void VirtualMachine::execute(){
	instruction ins(ir); // make constructor with int as parameter
	(*instr[ins.f1.OP])();  // ==  (functionName)(); functionName.base == beginning addr in mem loc
	sr = 0;
	__clock++;
}


void VirtualMachine::setCarryBit(){
	sr |= 1;
}

void VirtualMachine::setLessBit(){
	sr = 8;
}

void VirtualMachine::setEqualBit(){}
	sr = 4;
}

void VirtualMachine::setGreaterBit(){
	sr = 2;
}

void VirtualMachine::populateFunctionMap(){
    instr = {
        { 0 , &VirtualMachine::LOAD },
        { 0 , &VirtualMachine::LOADI },
        { 1 , &VirtualMachine::STORE },
        { 2 , &VirtualMachine::ADD },
        { 2 , &VirtualMachine::ADDI },
        { 3 , &VirtualMachine::ADDC },
        { 3 , &VirtualMachine::ADDCI },
        { 4 , &VirtualMachine::SUB },
        { 4 , &VirtualMachine::SUBI },
        { 5 , &VirtualMachine::SUBC },
        { 5 , &VirtualMachine::SUBCI },
        { 6 , &VirtualMachine::AND },
        { 6 , &VirtualMachine::ANDI },
        { 7 , &VirtualMachine::XOR },
        { 7 , &VirtualMachine::XORI },
        { 8 , &VirtualMachine::COMPL },
        { 9 , &VirtualMachine::SHL },
        { 10 , &VirtualMachine::SHLA },
        { 11 , &VirtualMachine::SHR },
        { 12 , &VirtualMachine::SHRA },
        { 13 , &VirtualMachine::COMPR },
        { 13 , &VirtualMachine::COMPRI },
        { 14 , &VirtualMachine::GETSTAT },
        { 15 , &VirtualMachine::PUTSTAT },
        { 16 , &VirtualMachine::JUMP },
        { 17 , &VirtualMachine::JUMPL },
        { 18 , &VirtualMachine::JUMPE },
        { 19 , &VirtualMachine::JUMPG },
        { 20 , &VirtualMachine::CALL },
        { 21 , &VirtualMachine::RETURN },
        { 22 , &VirtualMachine::READ },
        { 23 , &VirtualMachine::WRITE },
        { 24 , &VirtualMachine::HALT },
        { 25 , &VirtualMachine::NOOP }
    }
}

void VirtualMachine::LOAD(){
    r[ins.f2.RD] += mem[ins.f2.ADDR];
}

void VirtualMachine::LOADI(){
    r[ins.f3.RD] += ins.f3.CONST;
}

void VirtualMachine::STORE(){
    mem[ins.f2.ADDR] = r[ins.f2.RD];
}

void VirtualMachine::ADD(){
    r[ins.f1.RD] += r[ins.f1.RS];
    setCarryBit();
}

void VirtualMachine::ADDI(){
    r[ins.f3.RD] += ins.f3.CONST;
    setCarryBit();
}

void VirtualMachine::ADDC(){
    r[ins.f1.RD] = r[ins.f1.RD] + r[ins.f1.RS] + 1;
    setCarryBit();
}

void VirtualMachine::ADDCI(){
    r[ins.f3.RD] = r[ins.f3.RD] + r[ins.f3.CONST] + 1;
    setCarryBit();
}

void VirtualMachine::SUB(){
    r[ins.f1.RD] -= r[ins.f1.RS];
    setCarryBit();
}

void VirtualMachine::SUBI(){
    r[ins.f3.RD] -= ins.f3.CONST;
    setCarryBit();
}

void VirtualMachine::SUBC(){
    r[ins.f1.RD] = r[ins.f1.RD] - r[ins.f1.RS] - 1;
    setCarryBit();
}

void VirtualMachine::SUBCI(){
 	r[ins.f3.RD] = r[ins.f3.RD] - CONST - 1;
    setCarryBit();
}

void VirtualMachine::AND(){
    r[ins.f1.RD] &= r[ins.f1.RS];
}

void VirtualMachine::ANDI(){
    r[ins.f3.RD] &= ins.f3.CONST;
}

void VirtualMachine::XOR(){
    r[ins.f1.RD] ^= r[ins.f1.RS];
}

void VirtualMachine::XORI(){
    r[ins.f3.RD] ^= ins.f3.CONST;
}

void VirtualMachine::COMPL(){
    r[ins.f1.RD] = ~r[ins.f1.RD];
}

void VirtualMachine::SHL(){
    r[ins.f1.RD] <<= 1;
}

void VirtualMachine::SHLA(){
    //shift left arithmetic
}

void VirtualMachine::SHR(){
    r[ins.f1.RD] >>= 1;
}

void VirtualMachine::SHRA(){
    //shift right arithmetic
}

void VirtualMachine::COMPR(){
    if (r[ins.f1.RD] < r[ins.f1RS])
        setLessBit();
    else if (r[ins.f1.RD] == r[ins.f1.RS])
        setEqualBit();
    else
        setGreaterBit();
}

void VirtualMachine::COMPRI(){
    if(r[ins.f3.RD]< ins.f3.CONST)
       setLessBit();
    else if(r[ins.f3.RD] == ins.f3.CONST)
        setEqualBit();
    else
        setGreaterBit();
}

void VirtualMachine::GETSTAT(){
    r[ins.f1.RD] = sr;
}

void VirtualMachine::PUTSTAT(){
    sr = r[ins.f1.RD];
}

void VirtualMachine::JUMP(){
    pc = ins.f2.ADDR;
}

void VirtualMachine::JUMPL(){
    if(isLessBit())
        pc = ins.f2.ADDR;
}

void VirtualMachine::JUMPE(){
    if(isEqualBit())
        pc = ins.f2.ADDR;
}

void VirtualMachine::JUMPG(){
	if(isGreaterBit())
        pc = ins.f2.ADDR;
}

void VirtualMachine::CALL(){
	//push VM status
	mem[sp--] = sr;
	mem[sp--] = ir;
	mem[sp--] = r[0];
	mem[sp--] = r[1];
	mem[sp--] = r[2];
	mem[sp--] = r[3];
	mem[sp--] = pc;

	//jump to new location in mem
    pc = ins.f2.ADDR
}

void VirtualMachine::RETURN(){
	pc = mem[pc++];
	r[3] = mem[pc++];
	r[2] = mem[pc++];
	r[1] = mem[pc++];
	r[0] = mem[pc++];
	ir = mem[pc++];
	sr = mem[pc++];
}

void VirtualMachine::READ(){
	fstream prog;
	prog.open("VirtualMachine.in");
	string line;
	getline(prog, line);
	r[ins.f1.RD] = (uint16_t)atoi(temp.c_str());
}

void VirtualMachine::WRITE(){
  ofstream ofs;
  ofs.open ("VirtualMachine.out", ofstream::out);
  ofs << static_cast<ostringstream*>( &(ostringstream() << ins.f1.RD) )->str();
  ofs.close();
}

void VirtualMachine::HALT(){
	exit(0);
}

void VirtualMachine::NOOP(){
	void(0);
}


