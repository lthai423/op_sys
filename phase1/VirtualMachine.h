// include guard
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

// forward declared dependencies
class VirtualMachine;

// included dependencies
#include <iostream> // std::cin
#include <map>  // std::map
#include <string> // std::string
#include <sstream> //std:: istringstream, std::ostringstream
#include <fstream> // std::fstream
#include <stdlib.h>  // std::atoi
#include <stdint.h> // std::uint16_t
//#include <array>
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
	uint16_t clock;
        
	//helper functions
    public:
	VirtualMachine();
      	
};

#endif

