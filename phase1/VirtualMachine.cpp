#include "VirtualMachine.h"

using namespace std;

VirtualMachine::VirtualMachine(){
  populateMemory(); //set base and limit in there

  //start fetch-decode-execute cycle
  while (pc < MEM_SIZE){
    ir = mem[pc++] //fetch
    execute(pc); //
  }
}

void VirtualMachine::populateMemory(){
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

void VirtualMachine::execute(int &pc){
	instruction ins(pc); // make constructor with int as parameter
	(*instr[ins.f1.OP])();  // ==  (functionName)(); functionName.base == beginning addr in mem loc
}


void VirtualMachine::setCarryBit()
{

}

void VirtualMachine::setLessBit()
{

}

void VirtualMachine::setEqualBit()
{

}

void VirtualMachine::setGreaterBit()
{

}

void VirtualMachine::LOAD(){
	int RD = 
	r[RD] += mem[ADDR];
}

void VirtualMachine::LOADI(){
	r[RD] += CONST;
}

void VirtualMachine::Store()
{
	mem[ADDR] = r[RD];
}

void VirtualMachine::Add()
{
	r[RD] += r[RS];
    setCarryBit();
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

void VirtualMachine::Addi(int RD, uint16_t CONST)
{
	r[RD] += CONST;
    setCarryBit();
}

void VirtualMachine::Addc(int RD, int RS)
{
	r[RD] += r[RS] + returnCarryBit();
	setCarryBit();	//guarantees to set the carry bit
}

void VirtualMachine::Addci(int RD, uint16_t CONST)
{
	r[RD] += CONST + returnCarryBit();
    setCarryBit();	//guarantees to set the carry bit
}

void VirtualMachine::Sub(int RD, int RS)
{
	r[RD] -= r[RS];
	setCarryBit();
}

void VirtualMachine::Subi(int RD, uint16_t CONST)
{
	r[RD] -= CONST;
	setCarryBit();
}

void VirtualMachine::Subc(int RD, int RS)
{
	r[RD] = r[RD] - r[RS] - returnCarryBit();
	setCarryBit();
}

void VirtualMachine::Subci(int RD, uint16_t CONST)
{
	r[RD] = r[RD] - CONST - returnCarryBit();
}

void VirtualMachine::And(int RD, int RS)
{
	r[RD] = r[RD] & r[RS];
}

void VirtualMachine::Andi(int RD, uint16_t CONST)
{
	r[RD] = r[RD] & CONST;
}

void VirtualMachine::Xor(int RD, int RS)
{
	r[RD] = r[RD] ^ r[RS];
}

void VirtualMachine::Xori(int RD, uint16_t CONST)
{
	r[RD] = r[RD] ^ CONST;
}

void VirtualMachine::Compl(int RD)
{
	r[RD] = ~r[RD];	//bit negation
}

void VirtualMachine::Shl(int RD)
{
	r[RD] = r[RD] << 1;
	//shift bit needs to be set to 0 **LOOK INTO THIS**
}

void VirtualMachine::Shla(int RD)
{
	//shift left arithmetic
}

void VirtualMachine::Shr(int RD)
{
	r[RD] = r[RD] >> 1;	
	//shift bit needs to be set to 0
}

void VirtualMachine::Shra(int RD)
{
	//shift right arithmetic
}

void VirtualMachine::Compr(int RD, int RS)
{
	if (r[RD] < r[RS])
	    setLessBit();
	else if (r[RD] == r[RS])
		setEqualBit();
	else (r[RD] > r[RS])
		setGreaterBit();
}

void VirtualMachine::Compri(int RD, uint16_t CONST)
{
	if(r[RD]<CONST)
	   setLessBit();
	else if(r[RD] == CONST)
		setEqualBit();
	else (r[RD] > CONST)
		setGreaterBit();
}

void VirtualMachine::GetStat(int RD)
{
	r[RD] = SR;
}

void VirtualMachine::PutStat(int RD)
{
	SR = r[RD];
}

void VirtualMachine::Jump(uint16_t ADDR)
{
	pc = ADDR;
	//Needs work
}

void VirtualMachine::Jumpl(uint16_t ADDR)
{
	if(setLessBit() == 1)
	    pc = ADDR;
	//Needs work
}

void VirtualMachine::Jumpe(int pc, uint16_t ADDR)
{
	if(setEqualBit() == 1)
	    pc=ADDR;
	//Needs work
}

void VirtualMachine::Jumpg(int pc, uint16_t ADDR)
{
	if(setGreaterBit() == 1)
	    pc = ADDR;
	//Needs work
}

void VirtualMachine::Call(int pc, uint16_t ADDR)
{
	stack<uint16_t> x;
	pc = ADDR
	x.push(pc);

	//Needs work
}

void VirtualMachine::Return()
{
	x.pop();
	pc -> where it was pointing initially... would this be a location in mem?


	//Needs work
}

void VirtualMachine::Read(int RD)
{
		
//read new content of r[RD] from .in file?
}

void VirtualMachine::Write(int RD)
{
	//write r[RD] into .outfile
}

void VirtualMachine::Halt()
{
	//halt exec.done()?
}

void VirtualMachine::Noop()
{

}
