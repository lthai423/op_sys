// include guard
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// forward declared dependencies
class Assembler;

// included dependencies
#include <iostream> // std::cout
#include <map>  // std::map
#include <string> // std::string
#include <sstream> //std::istringstream

using namespace std;

class Assembler{
    public:
        Assembler(); //main logic
        string sendFinalObjProg(); //sends catted final prog.o file
    private:
        int returnFormat1(); //based on flag, use format 1
        int returnFormat2(); //based on flag, use format 2
        void storeSNN(string &); // store OPCODE and N!, if cin.good() store N2
        void appendToFinal(int &); //append produced # to final prog.o
        void initializeMemberFields() const;
        int returnNumIn2sComp(); //if num is negative, reformat before adding to instruction
        
        map <string, int[]> opcodes;
        map <int, int> RD;
        map <int, int> RS;
        string FinalObjProg;
        int n1;
        int n2;

};
#endif
