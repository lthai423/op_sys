#include "PCB.h"
#include "Assembler.h"
#include "VirtualMachine.h"
#include "os.h"

using namespace std;

PCB::PCB(string filename)
{
    StatusReg.i = 0;
    sp=256;
    base=0;
    pc=base;
    limit=0;
    reg = vector<int>(4);
    reg[0]=0;
    reg[1]=0;
    reg[2]=0;
    reg[3]=0;
    ProcessName = filename.substr(0, filename.size()-2);
    ofileName = ProcessName + ".o";
    infileName = ProcessName + ".in";
    outfileName = ProcessName + ".out";
    stackfileName = ProcessName + ".st";
        
    CPUTime=0;
    WaitTime=0;
    TurnaroundTime=0;
    IOTime=0;
    LargestStackSize=0;
}
