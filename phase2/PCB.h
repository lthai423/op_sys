#include<fstream>
#include<map>
#include<vector>
#include<stdint.h>
#include<string>

#infdef PCB_H
#define PCB_H

class PCB
{
    private: 
	 friend class os;
	 friend class VirtualMachine;
         vector<int> reg;
	 sr StatusReg;
         fstream infile, outfile, ofile, stfile;	//will read in and out of different types of files
         int pc, sp, base, limit, read, write, clock;
	 string ProcessName;
	 int CPUTime, WaitTime, TurnaroundTime, IOTime, LargestStackSize;
	 
};

#endif

class sr {
	public:
	    uint16_t UNUSED:6;
	    uint16_t RS:2;
	    uint16_t I:1;
	    uint16_t RD:2;
	    uint16_t OP:5;
	};



union s_r {
	int i;
	sr status;
};
