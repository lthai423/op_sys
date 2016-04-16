#include "VirtualMachine.h"
#include<stack>
using namespace std;

VirtualMachine::VirtualMachine(){
  r = vector <int> (REG_FILE_SIZE);
  mem = vector <int> (MEM_SIZE);
  populateMemory(); //set base and limit in there

  //start fetch-decode-execute cycle
  while (pc < MEM_SIZE){
    ir = mem[pc++] //fetch
    execute(pc); //
  }
}

void VirtualMachine::populateMemory(){
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

void VirtualMachine::setLessThanBit()
{

}

void VirtualMachine::setEqualToBit()
{

}

void VirtualMachine::setGreaterThanBit()
{

}

void VirtualMachine::Load(int RD, uint16_t ADDR){
	r[RD] += mem[ADDR];
}

void VirtualMachine::Loadi(int RD, uint16_t CONST){
	r[RD] += CONST;
}

void VirtualMachine::Store(int RD, uint16_t ADDR)
{
	mem[ADDR] = r[RD];
}

void VirtualMachine::Add(int RD, int RS)
{
	r[RD] += r[RS];
        setCarryBit();
}

void VirtualMachine::Addi(int RD, uint16_t CONST)
{
	r[RD] += CONST;
        setCarryBit();
}

void VirtualMachine::Addc(int RD, int RS)
{
	r[RD] += r[RS] + setCarryBit();
	setCarryBit();	//guarantees to set the carry bit
}

void VirtualMachine::Addci(int RD, uint16_t CONST)
{
	r[RD] += CONST + setCarryBit();
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
	r[RD]=r[RD]-r[RS] - setCarryBit();
	setCarryBit();
}

void VirtualMachine::Subci(int RD, uint16_t CONST)
{
	r[RD] = r[RD] - CONST - setCarryBit();
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
	    setLessThanBit();
	else if (r[RD] == r[RS])
		setEqualToBit();
	else (r[RD] > r[RS])
		setGreaterThanBit();
}

void VirtualMachine::Compri(int RD, uint16_t CONST)
{
	if(r[RD]<CONST)
	   setLessThanBit();
	else if(r[RD] == CONST)
		setEqualToBit();
	else (r[RD] > CONST)
		setGreaterThanBit();
}

void VirtualMachine::GetStat(int RD)
{
	int SR=0;
	r[RD] = SR;
}

void VirtualMachine::PutStat(int RD)
{
	int SR=0;
	SR = r[RD];
}

void VirtualMachine::Jump(int pc, uint16_t ADDR)
{
	pc = ADDR;
}

void VirtualMachine::Jumpl(int pc, uint16_t ADDR)
{
	if(setLessThanBit() == 1)
	    pc = ADDR;
}

void VirtualMachine::Jumpe(int pc, uint16_t ADDR)
{
	if(setEqualToBit() == 1)
	    pc=ADDR;
}

void VirtualMachine::Jumpg(int pc, uint16_t ADDR)
{
	if(setGreaterThanBit() == 1)
	    pc = ADDR;
}

void VirtualMachine::Call(int pc, uint16_t ADDR)
{
	stack<uint16_t> x;
	pc = ADDR
	x.push(pc);
}

void VirtualMachine::Return()
{
	x.pop();
	pc -> where it was pointing initially... would this be a location in mem?
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
/*

Research:

[SOLVED] How to "link" map of function pointers to current class? Are we going to keep it in this class? Or should we include it.

How to "link" union in class.  I want to use external.  make it so. plus rethink the scope of the union and its' ability to access 
member fields in the different  class, encapsulation

Start thinking of how to define the functions that we call. MAHHHFUCKAAHHH

TEAM ON 3.....
1 2 3
TEAM
!!!!!

