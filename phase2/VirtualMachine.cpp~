#include "VirtualMachine.h"

using namespace std;


void VirtualMachine::run(string prog_name){
	populateMemory(prog_name); //set base and limit in there

	//start fetch-decode-execute cycle
	while ( 1 ){ //infinite loop
    	ir = mem[pc++]; //fetch
    	execute();
    }
    writeClock();
}

void VirtualMachine::populateMemory(string prog_name){
	//initialize memory and registers
	r = vector <unsigned> (REG_FILE_SIZE);
	mem = vector <unsigned> (MEM_SIZE);
	pc = 0;
    prog_o = prog_name;

	//open and populate memory with instructions
	fstream prog;
	prog.open(prog_o + ".o");
	if (!prog.is_open())
        exit(0);
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

void VirtualMachine::writeClock(){
	ofstream ofs;
	ofs.open("__clock.out");
	if (!ofs.is_open())
		exit(8);
	ofs << __clock;
	//ofs.close();  //closed implicitly
}

void VirtualMachine::execute(){
	instruction ins(ir); // include in class to optimize. repeated instantiations -> performance cost
    if(ins.f1.I)
		(this->*instr_1_immed[ins.f1.OP])(ins);  // ==  (functionName)(); functionName.base == beginning addr in mem loc
	else
		(this->*instr_0_immed[ins.f1.OP])(ins);
}


void VirtualMachine::setCarryBit(){
	sr |= 1;
}

void VirtualMachine::setLessBit(){
	sr &= 25; // set less, equal, and greater bit to zero, AND 010001 preserves state of overflow and carry bits.
	sr |= 8;
}


void VirtualMachine::setEqualBit(){
	sr &= 21;
	sr |= 4;
}

void VirtualMachine::setGreaterBit(){
	sr &= 19;
	sr |= 2;
}

bool VirtualMachine::isLessBit(){
  if ( (sr & 8) == 8 )
		return true;
	return false;
}

bool VirtualMachine::isGreaterBit(){
	if ( (sr & 2) == 2)
		return true;
	return false;
}

bool VirtualMachine::isEqualBit(){
	if ( (sr & 4) == 4)
        return true;
	return false;
}

void VirtualMachine::zeroCarryBit(){
    sr &= 30;
}

void VirtualMachine::checkCarryBit(instruction &ins){
	if ((int)r[ins.f3.RD] > 65535){
        setCarryBit();
        r[ins.f3.RD] = 65535;
    }
    else if ((int)r[ins.f3.RD] < -65535){
    	setCarryBit();
    	r[ins.f3.RD] = -65535;
    }
    else{
    	zeroCarryBit();
    }
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
}

void VirtualMachine::LOADI(instruction &ins){
    r[ins.f3.RD] = ins.f3.CONST;
    __clock++;
}

void VirtualMachine::STORE(instruction &ins){
    mem[ins.f2.ADDR] = r[ins.f2.RD];
    __clock += 4;
}


void VirtualMachine::ADD(instruction &ins){
    r[ins.f1.RD] += r[ins.f1.RS];
    checkCarryBit(ins);

    __clock++;
}

void VirtualMachine::ADDI(instruction &ins){
    r[ins.f3.RD] += ins.f3.CONST;
    checkCarryBit(ins);

    __clock++;
}

void VirtualMachine::ADDC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] + r[ins.f1.RS] + (sr & 1);
    checkCarryBit(ins);

    __clock++;
}

void VirtualMachine::ADDCI(instruction &ins){
    r[ins.f3.RD] = r[ins.f3.RD] + r[ins.f3.CONST] + (sr & 1);
    checkCarryBit(ins);

    __clock++;
}

void VirtualMachine::SUB(instruction &ins){
    r[ins.f1.RD] -= r[ins.f1.RS];
    checkCarryBit(ins);

    __clock++;
}


void VirtualMachine::SUBI(instruction &ins){
    r[ins.f3.RD] -= ins.f3.CONST;
    checkCarryBit(ins);

    __clock++;
}

void VirtualMachine::SUBC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] - r[ins.f1.RS] - (sr & 1);
    checkCarryBit(ins);
    
    __clock++;
}

void VirtualMachine::SUBCI(instruction &ins){
    r[ins.f3.RD] = r[ins.f3.RD] - ins.f3.CONST - (sr & 1);
    checkCarryBit(ins);
    
    __clock++;
}

void VirtualMachine::AND(instruction &ins){
    r[ins.f1.RD] &= r[ins.f1.RS];
    __clock++;
}

void VirtualMachine::ANDI(instruction &ins){
    r[ins.f3.RD] &= ins.f3.CONST;
    __clock++;
}

void VirtualMachine::XOR(instruction &ins){
    r[ins.f1.RD] ^= r[ins.f1.RS];
    __clock++;
}

void VirtualMachine::XORI(instruction &ins){
    r[ins.f3.RD] ^= ins.f3.CONST;
    __clock++;
}

void VirtualMachine::COMPL(instruction &ins){
    r[ins.f1.RD] = ~r[ins.f1.RD];
    __clock++;
}

void VirtualMachine::SHL(instruction &ins){
	if((r[ins.f1.RD] >> 15) == 1)
		setCarryBit();
	else
		zeroCarryBit();

    r[ins.f1.RD] <<= 1;
    __clock++;
}

void VirtualMachine::SHLA(instruction &ins){
	if((r[ins.f1.RD] >> 15) == 1){
		r[ins.f1.RD] <<= 1;
		r[ins.f1.RD] |= 1;
		setCarryBit();
	}
	else{
		r[ins.f1.RD] <<= 1;
		zeroCarryBit();
	}

	__clock++;
}

void VirtualMachine::SHR(instruction &ins){
    if ((r[ins.f1.RD] & 1) == 1)
        setCarryBit();
    else
        zeroCarryBit();
    
    r[ins.f1.RD] >>= 1;
    __clock++;
}

void VirtualMachine::SHRA(instruction &ins){
    if ( (r[ins.f1.RD] >> 15) == 1 ){  //if 
		r[ins.f1.RD] >>= 1;
		r[ins.f1.RD] |= 32768;
		setCarryBit();
    }
    else
    	zeroCarryBit();

	r[ins.f1.RD] >>= 1;
	__clock++;
}

void VirtualMachine::COMPR(instruction &ins){
    if (r[ins.f1.RD] < r[ins.f1.RS])
        setLessBit();
    else if (r[ins.f1.RD] == r[ins.f1.RS])
        setEqualBit();
    else
        setGreaterBit();
    __clock++;
}

void VirtualMachine::COMPRI(instruction &ins){
    if(r[ins.f3.RD]< ins.f3.CONST)
       setLessBit();
    else if(r[ins.f3.RD] == ins.f3.CONST)
        setEqualBit();
    else
        setGreaterBit();
	__clock++;
}

void VirtualMachine::GETSTAT(instruction &ins){
    r[ins.f1.RD] = sr;
    __clock++;
}

void VirtualMachine::PUTSTAT(instruction &ins){
    sr = r[ins.f1.RD];
    __clock++;
}

void VirtualMachine::JUMP(instruction &ins){
    pc = ins.f2.ADDR;
    __clock++;
}

void VirtualMachine::JUMPL(instruction &ins){
    if(isLessBit())
        pc = ins.f2.ADDR;
    __clock++;
}

void VirtualMachine::JUMPE(instruction &ins){
    if(isEqualBit())
        pc = ins.f2.ADDR;
	__clock++;
}

void VirtualMachine::JUMPG(instruction &ins){
	if(isGreaterBit())
        pc = ins.f2.ADDR;
    __clock++;
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

    __clock++;
}

void VirtualMachine::RETURN(instruction &ins){
	//pull VM status
	pc = mem[++sp];
	r[3] = mem[++sp];
	r[2] = mem[++sp];
	r[1] = mem[++sp];
	r[0] = mem[++sp];
	ir = mem[++sp];
	sr = mem[++sp];

	__clock++;

}

void VirtualMachine::READ(instruction &ins){
	fstream prog;
	prog.open(prog_o + ".in");
	if (!prog.is_open())
		exit(3);
	string line;
	getline(prog, line);
	r[ins.f1.RD] = (unsigned)atoi(line.c_str()); //effecient method for string to int cast
	prog.close();

	__clock += 28;
}

void VirtualMachine::WRITE(instruction &ins){
	ofstream ofs;
	ofs.open (prog_o + ".out", ofstream::out);
	if (!ofs.is_open())
		exit(2);
	ofs << to_string(r[ins.f1.RD]); //an effecient method for string casting
	ofs.close();

	__clock += 28;
}

void VirtualMachine::HALT(instruction &ins){
	__clock++;
    exit(0);
}

void VirtualMachine::NOOP(instruction &ins){
	__clock++;
	void(0);
}


