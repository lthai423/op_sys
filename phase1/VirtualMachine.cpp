#include "VirtualMachine.h"

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

void VirtualMachine::load(int RD, uint16_t ADDR){
	r[RD] += mem[ADDR];
}

void VirtualMachine::loadi(int RD, uint16_t CONST){
	r[RD] += CONST;
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

