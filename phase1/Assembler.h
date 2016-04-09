// include guard
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// forward declared dependencies
class Assembler;

// included dependencies
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Assembler{
    public:
        Assembler(); //main logic
        string sendFinalObjProg(); //sends catted final prog.o file
    private:
        returnFormat1(); //based on flag, use format 1
        returnFormat2(); //based on flag, use format 2
        storeSNN(); // store OPCODE and N!, if cin.good() store N2
        appendToFinal(); //append produced # to final prog.o
        initializeMemberFields();
        return_2s_comp_format(); //if num is negative, reformat before adding to instruction
        
        map <string, int[]> opcodes;
        map <int, int> RD;
        map <int, int> RS;
        string FinalObjProg;
        int n1;
        int n2;

};
#endif
