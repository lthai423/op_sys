#include "PCB.h"

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
    string name = filename + ".in";
    infile.open(name.c_str(),fstream::in);
    name = filename + ".o";
    ofile.open(name.c_str(),fstream::in);
    name = filename + ".st";
    stfile.open(name.c_str(),fstream::out);
    stfile.close();
    stfile.open(name.c_str(),fstream::out | fstream::in);
    name = filename + ".out";
    outfile.open(name.c_str(), fstream::out);
    assert(outfile.open());	
    ProcessName = filename;
    assert(stfile.open());
        
    CPUTime=0;
    WaitTime=0;
    TurnaroundTime=0;
    IOTime=0;
    LargestStackSize=0;
}
