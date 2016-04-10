// include guard
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// forward declared dependencies
class Assembler;

// included dependencies
#include <iostream> // std::cin
#include <map>  // std::map
#include <string> // std::string
#include <sstream> //std::istringstream, std::ostringstream
#include <stdlib.h>  // std::atoi

using namespace std;

class Assembler{

    public:
        Assembler(); //main logic
        // string sendFinalObjProg(); //sends catted final prog.o file

    private:
        //internal "helper" functions
        unsigned returnFormat1(); //based on flag, use format 1
        unsigned returnFormat2(); //based on flag, use format 2 addr
        unsigned returnFormat3(); //based on flag, use format 2 const
        void storeSNN(string &); // store OPCODE and N!, if cin.good() store N2
        void appendToFinal(int &); //append produced # to final prog.o
        void initializeMemberFields() const;
        int returnNumIn2sComp(); //if num is negative, reformat before adding to instruction
        

        //member field
        map <string, array<unsigned, 3>> opcodes; //stores opcode in decimal value and immediate "flag"
        map <int, unsigned> RD; //stores register destination values in decimal value - can apply for
                            //both formats' RD are in the same location
        map <int, unsigned> RS; //stores source register in decimal value and immediate "flag"
        string FinalObjProg; //stores final produced after being appended to sequentially
        unsigned immediateConversion[]; //stores Immediate Register conversion - "flags" made to match
                                                                            // with array indices
        unsigned RDestination; // Register Destination
        unsigned num_2; //could be empty
        string instruct_opcode; //stores string of opcode
        bool isOneNum; // does the current operation consist of only one number
             
};
#endif
