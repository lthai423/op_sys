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

void VirtualMachine::load(){
	r[RD] += mem[ADDR];
}

void VirtualMachine::loadi(){
	r[RD] += CONST;
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

