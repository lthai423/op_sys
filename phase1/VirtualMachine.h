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
#include <vector>

using namespace std;

class VirtualMachine{

    private:
    typedef void (VirtualMachine::*FP)(instruction &);

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
	int __clock;
	map <int, FP> instr;
        
	//helper functions
  	void execute();
  	void populateMemory();
  	void populateFunctionMap();
  	void setCarryBit();
  	void setGreaterBit();
  	void setLessBit();
  	void setEqualBit();

  	bool isGreaterBit();
  	bool isLessBit();
  	bool isEqualBit();


  	//opcode functions
  	void LOAD(instruction &);
  	void LOADI(instruction &);
  	void STORE(instruction &);
  	void ADD(instruction &);
  	void ADDI(instruction &);
  	void ADDC(instruction &);
  	void ADDCI(instruction &);
  	void SUB(instruction &);
  	void SUBI(instruction &);
  	void SUBL(instruction &);
  	void SUBC(instruction &);
  	void SUBCI(instruction &);
  	void AND(instruction &);
  	void ANDI(instruction &);
  	void XOR(instruction &);
  	void XORI(instruction &);
  	void COMPL(instruction &);
  	void SHL(instruction &);
  	void SHLA(instruction &);
  	void SHR(instruction &);
  	void SHRA(instruction &);
  	void COMPR(instruction &);
  	void COMPRI(instruction &);
  	void GETSTAT(instruction &);
  	void PUTSTAT(instruction &);
  	void JUMP(instruction &);
  	void JUMPL(instruction &);
  	void JUMPE(instruction &);
  	void JUMPG(instruction &);
  	void CALL(instruction &);
  	void RETURN(instruction &);
  	void READ(instruction &);
  	void WRITE(instruction &);
  	void HALT(instruction &);
  	void NOOP(instruction &);
  	//end of instr functions

    public:
	VirtualMachine();
      	
};

#endif

