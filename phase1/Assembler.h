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
        uint16_t returnFormat1(); //based on flag, use format 1 - 0
        uint16_t returnFormat2_ADDR(); //based on flag, use format 2 addr - 1
        uint16_t returnFormat2_CONST(); //based on flag, use format 2 const - 2
        void storeSNN(string &); // store OPCODE and N!, if cin.good() store N2
        void appendToFinal(int &); //append produced # to final prog.o
        void initializeMemberFields() const;
        // int returnNumIn2sComp(); //if num is negative, reformat before adding to instruction
        

        //member field
        map <string, array<uint16_t, 2>> opcodes; //stores opcode in decimal value and immediate "flag"
        map <int, uint16_t> RD; //stores register destination values in decimal value - can apply for
                            //both formats' RD are in the same location
        map <int, uint16_t> RS; //stores source register in decimal value and immediate "flag"
        string FinalObjProg; //stores final produced after being appended to sequentially
        uint16_t immediateConversion[]; //stores Immediate Register conversion - "flags" made to match
                                                                            // with array indices
        uint16_t RDestination; // Register Destination
        uint16_t ADDR; //could be empty 
        uint16_t CONST; //needs 8 bit two's comp num. subject to change
        string instruct_opcode; //stores string of opcode
        bool isOneNum; // does the current operation consist of only one number
             
};
#endif
