#include<fstream>
#include<map>
#include<vector>
#include<stdint.h>
#include<string>
#include<cassert>

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
         int pc, sp, base, limit, clock;
	 string ProcessName, ofileName, infileName, outfileName, stackfileName;
	 int CPUTime, WaitTime, TurnaroundTime, IOTime, LargestStackSize;

    public:
	PCB(string filename);
};

#endif

