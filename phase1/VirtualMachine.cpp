#include "VirtualMachine.h"

using namespace std;

VirtualMachine::VirtualMachine(){
	populateMemory(); //set base and limit in there

	//start fetch-decode-execute cycle
	while (pc <= limit){
	ir = mem[pc++]; //fetch
	execute();
	}

}

void VirtualMachine::populateMemory(){
	//initialize memory and registers
	r = vector <uint16_t> (REG_FILE_SIZE);
	mem = vector <uint16_t> (MEM_SIZE);
	pc = 0;

	//open and populate memory
	fstream prog;
	prog.open("prog.o");
	string line, temp;
	istringstream iss;
	getline(prog, line);
	while(!prog.eof()){
		mem[pc++] = (uint16_t)atoi(line.c_str());
		getline(prog, line);
	}

	//set mem base and limits
	limit = pc;
	pc = base = __clock = 0;

	//other
	populateFunctionMap();
}

void VirtualMachine::execute(){
	instruction ins(ir); // include in class to optimize. repeated instantiations -> performance cost
	if(ins.f1.I)
		(this->*instr_1_immed[ins.f1.OP])(ins);  // ==  (functionName)(); functionName.base == beginning addr in mem loc
	else
		(this->*instr_0_immed[ins.f1.OP])(ins);
	sr = 0;
	__clock++;
}


void VirtualMachine::setCarryBit(){
	sr |= 1;
}

void VirtualMachine::setLessBit(){
	sr &= 17; // set less, equal, and greater bit to zero, AND 010001 preserves state of overflow and carry bits.
	sr |= 8;
}

void VirtualMachine::setEqualBit(){
	sr &= 17;
	sr |= 4;
}

void VirtualMachine::setGreaterBit(){
	sr &= 17;
	sr |= 2;
}

bool VirtualMachine::isLessBit(){
	if ( sr & 8 == 8 )
		return true;
	return false;
}

bool VirtualMachine::isGreaterBit(){
	if ( sr & 2 == 2)
		return true;
	return false;
}

bool VirtualMachine::isEqualBit(){
	if ( sr & 4 == 4)
		return true;
	return false;
}

void VirtualMachine::populateFunctionMap(){
	instr_0_immed = {
        { 0 , &VirtualMachine::LOAD },
        { 1 , &VirtualMachine::STORE },
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
		
	};
    instr_1_immed = {
        { 0 , &VirtualMachine::LOADI },
        { 2 , &VirtualMachine::ADDI },
        { 3 , &VirtualMachine::ADDCI },
        { 4 , &VirtualMachine::SUBI },
        { 5 , &VirtualMachine::SUBCI },
        { 6 , &VirtualMachine::ANDI },
        { 7 , &VirtualMachine::XORI },
        { 13 , &VirtualMachine::COMPRI },
    };
}

void VirtualMachine::LOAD(instruction &ins){
    r[ins.f2.RD] = mem[ins.f2.ADDR];
}

void VirtualMachine::LOADI(instruction &ins){
    r[ins.f3.RD] = ins.f3.CONST;
}

void VirtualMachine::STORE(instruction &ins){
    mem[ins.f2.ADDR] = r[ins.f2.RD];
}

void VirtualMachine::ADD(instruction &ins){
    r[ins.f1.RD] += r[ins.f1.RS];
    setCarryBit();
}

void VirtualMachine::ADDI(instruction &ins){
    r[ins.f3.RD] += ins.f3.CONST;
    setCarryBit();
}

void VirtualMachine::ADDC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] + r[ins.f1.RS] + 1;
    setCarryBit();
}

void VirtualMachine::ADDCI(instruction &ins){
    r[ins.f3.RD] = r[ins.f3.RD] + r[ins.f3.CONST] + 1;
    setCarryBit();
}

void VirtualMachine::SUB(instruction &ins){
    r[ins.f1.RD] -= r[ins.f1.RS];
    setCarryBit();
}

void VirtualMachine::SUBI(instruction &ins){
    r[ins.f3.RD] -= ins.f3.CONST;
    setCarryBit();
}

void VirtualMachine::SUBC(instruction &ins){
    r[ins.f1.RD] = r[ins.f1.RD] - r[ins.f1.RS] - 1;
    setCarryBit();
}

void VirtualMachine::SUBCI(instruction &ins){
 	r[ins.f3.RD] = r[ins.f3.RD] - ins.f3.CONST - 1;
    setCarryBit();
}

void VirtualMachine::AND(instruction &ins){
    r[ins.f1.RD] &= r[ins.f1.RS];
}

void VirtualMachine::ANDI(instruction &ins){
    r[ins.f3.RD] &= ins.f3.CONST;
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
}

void VirtualMachine::SHLA(instruction &ins){
    //shift left arithmetic
}

void VirtualMachine::SHR(instruction &ins){
    r[ins.f1.RD] >>= 1;
}

void VirtualMachine::SHRA(instruction &ins){
    //shift right arithmetic
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
}

void VirtualMachine::GETSTAT(instruction &ins){
    r[ins.f1.RD] = sr;
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
}

void VirtualMachine::JUMPG(instruction &ins){
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
}

void VirtualMachine::RETURN(instruction &ins){
	//pull VM status
	pc = mem[pc++];
	r[3] = mem[pc++];
	r[2] = mem[pc++];
	r[1] = mem[pc++];
	r[0] = mem[pc++];
	ir = mem[pc++];
	sr = mem[pc++];
}

void VirtualMachine::READ(instruction &ins){
	fstream prog;
	prog.open("VirtualMachine.in");
	string line;
	getline(prog, line);
	r[ins.f1.RD] = (uint16_t)atoi(line.c_str());
	prog.close();
	cout << endl << r[ins.f1.RD] << endl;
}

void VirtualMachine::WRITE(instruction &ins){
	ofstream ofs;
	ofs.open ("VirtualMachine.out", ofstream::out);
	ofs << static_cast<ostringstream*>( &(ostringstream() << r[ins.f1.RD]) )->str();
	ofs.close();
}

void VirtualMachine::HALT(instruction &ins){
	exit(0);
}

void VirtualMachine::NOOP(instruction &ins){
	void(0);
}


