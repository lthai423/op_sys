// include guard
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

// forward declared dependencies
class Assembler;

// included dependencies
#include <iostream> // std::cin
#include <map>  // std::map
#include <string> // std::string
#include <sstream> //std:: istringstream, std::ostringstream
#include <fstream> // std::fstream
#include <stdlib.h>  // std::atoi
#include <stdint.h> // std::uint16_t
#include <array>  //utilize c++ 11 only directives
#include "union.h" //used to build object code

using namespace std;

class Assembler{

    public:
        Assembler(); //main logic
        // string sendFinalObjProg(); //sends catted final prog.o file
        void assemble(string);
    private:
        //internal "helper" functions
        void setFormat1(instruction &); //based on flag, use format 1 - 0
        void setFormat2_ADDR(instruction &); //based on flag, use format 2 addr - 1
        void setFormat2_CONST(instruction &); //based on flag, use format 2 const - 2
        void setFormat3(instruction &);
        void storeSNN(string &); // store OPCODE and N!, if cin.good() store N2
        void appendToFinal(instruction &); //append produced # to final prog.o
        void initializeMemberFields();
        // int returnNumIn2sComp(); //if num is negative, reformat before adding to instruction
        

        //member field
        map <string, array<int, 2>> opcodes; //stores opcode in decimal value and immediate "flag"
        string FinalObjProg; //stores final produced after being appended to sequentially 
        uint16_t first_num; // Register Destination
        uint16_t second_num; //could be empty 
        string instruct_opcode; //stores string of opcode
        string prog;
             
};
#endif
