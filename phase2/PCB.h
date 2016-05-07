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
	    uint16_t CARRY:1;
	    uint16_t GREATERTHAN:1;
	    uint16_t EQUALTO:1;
	    uint16_t LESSTHAN:1;
	    uint16_t OVERFLOW:1;
	    uint16_t VMRETURNSTATUS:3;
	    uint16_t IOREG:2;
	    uint16_t DONTCARE:6;
	};



union s_r {
	int i;
	sr status;
};
