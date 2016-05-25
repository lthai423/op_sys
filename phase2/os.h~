#ifndef OS_H
#define OS_H
#include<list>
#include<queue>
#include<map>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include "Assembler.h"
#include "VirtualMachine.h"
#include "PCB.h"

using namespace std;

class os
{
private:
    Assembler assm;
    VirtualMachine vm;
    vector<string> progs;
    list<PCB *> jobs;
    queue<PCB *> readyQ, waitQ;
    PCB * running;
    fstream progfile;
    int systemTime, ConSwitchTime, jobsCPUtime, numofprocessesCompleted;
    float SysCPUutilization, userCPUutilization, throughput;

    void ContextSwitch();
    friend class VirtualMachine;
     	 	

public:
     os();
     void run();
};

#endif
