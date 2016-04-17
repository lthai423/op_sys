// include guard
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

// forward declared dependencies
class VirtualMachine;

// included dependencies
// #include <iostream> // std::cin
#include <map>  // std::map
#include <string> // std::string
#include <sstream> //std:: istringstream, std::ostringstream
#include <fstream> // std::fstream
#include <stdlib.h>  // std::atoi
#include <stdint.h> // std::uint16_t
#include "union.h" // facilitates parsing of prog.o

using namespace std;

class VirtualMachine{

    private:
	//member fields required for VM
	static const int REG_FILE_SIZE = 4;
	static const int MEM_SIZE = 256;
	vector <uint16_t> r;
	vector <uint16_t> mem;
	int pc;
	uint16_t ir;
	uint16_t sr;
	int sp;
	int base;
	int limit;
	int clock;
	map <int, FP> instr;
        
	//helper functions
  	void execute();
  	void populateMemory();
  	void populateFunctionMap();
  	void flopCarryBit();
  	void setGreaterBit();
  	void setLessBit();
  	void setEqualBit();


  	//opcode functions
  	void LOAD();
  	void LOADI();
  	void STORE();
  	void ADD();
  	void ADDI();
  	void ADDC();
  	void ADDCI();
  	void SUB();
  	void SUBL();
  	void SUBC();
  	void SUBCI();
  	void AND();
  	void ANDI();
  	void XOR();
  	void XORI();
  	void COMPL();
  	void SHL();
  	void SHLA();
  	void SHR();
  	void SHRA();
  	void COMPR();
  	void COMPRI();
  	void GETSTAT();
  	void PUTSTAT();
  	void JUMP();
  	void JUMPL();
  	void JUMPE();
  	void JUMPG();
  	void CALL();
  	void RETURN();
  	void READ();
  	void WRITE();
  	void HALT();
  	void NOOP();
  	//end of instr functions

    public:
	VirtualMachine();
      	
};

#endif

