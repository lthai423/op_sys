#include "Assembler.h" // depends declared in interfaces
#include<stdint.h>  //library required to compute the two's-complement of an 8-bit binary number

using namespace std;

Assembler::Assembler(){
    fstream assemblyProg;
    initializeMemberFields();
    string line;
    int rawBin;
    getline(assemblyProg, line)
    while(!assemblyProg.eof()){
        storeSNN(line);
        if ((opcodes[instruct_opcode])[1] == 0)
            appendToFinal(returnFormat1());
        else if ((opcodes[instruct_opcode])[1] == 1)
            appendToFinal(returnFormat2_ADDR());
        else
            appendToFinal(returnFormat2_CONST())
    }

}

uint16_t Assembler::returnFormat1(){
    int currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-11

    if (isOneNum){
        int destRegister = RD[RDestination];//bits 10-9
        // rest are dont cares
        return currentOpcode + destRegister ;  //SR bits 7-6 and unused bits 5-0 are don't cares
    }
    else{
        int destRegister = RD[RDestination]; //bits 10-9
        int sourceRegister = RS[num_2]; //bits 7-6
        // bits 5-0 unused

        return currentOpcode + destRegister + sourceRegister;
    }

}

uint16_t Assembler::returnFormat2_ADDR(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    uint16_t destRegister = RD[RDestination];
    uint16_t immediate = 256; //#
    return currentOpcode + destRegister + immediate + ADDR;
}

uint16_t Assembler::returnFormat2_CONST(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    uint16_t destRegister = RD[RDestination];
    uint16_t immediate = 256; //#
    return currentOpcode + destRegister + immediate + CONST;
}

void Assembler::storeSNN(string &SNN){
    istringstream iss(SNN);
    int i = 0;
    string temp;
    while(iss >> temp){
        if (i == 0)
            instruct_opcode = temp;
        else if (i == 1)
            Rdestination = (uint16_t)atoi(temp.c_str());  //cast into 16 bit unsigned integer
        else
            num_2 = (uint16_t)atoi(temp.c_str());
        i++;
    } 
    if (i == 1) //ensure that num_2 is set out of bounds if there is only one value
        num_2 = -129; 
        isOneNum = true;
}

void Assembler::appendToFinal(int &instr){
    string castedString = static_cast<ostringstream*>( &(ostringstream() << instr) )->str();
    FinalObjProg = castedString + "\n";
}

void Assembler::initializeMemberFields() const{
    opcodes = {
        { "load", {{ 0 , 1 }} },  //add extra element containing the format used.
        { "loadi", {{72,1}} },   //see interface for details about format
        { "store", {{,1}} },       //SECOND ELEMENTS ARE WRONG! MUST FIX BEFORE USE
        { "add", {{,0}} },      
        { "addi", {{,1}} },
        { "addc", {{,0}} },
        { "addci", {{,1}} },
        { "sub", {{,0}} },
        { "subi", {{,1}} },
        { "subc", {{,0}} },
        { "subci", {{,1}} },
        { "and", {{,0}} },
        { "andi", {{,1}} },
        { "xor", {{,0}} },
        { "xori", {{,1}} },
        { "compl", {{,0}} },
        { "shl", {{,0}} },
        { "shla", {{,0}} },
        { "shr", {{,0}} },
        { "shra", {{,0}} },
        { "compr", {{,0}} },
        { "compri", {{,1}} },
        { "getstat", {{,}} },
        { "putstat", {{,}} },
        { "jump", {{,1}} },
        { "jumpl", {{,1}} },
        { "jumpe", {{,1}} },
        { "jumpg", {{,1}} },
        { "call", {{,1}} },
        { "return", {{,0}} },
        { "read", {{,0}} },
        { "write", {{,0}} },
        { "halt", {{,0}} },
        { "noop", {{,0}} }
    };
    RD = {
        { 1 , 0 },
        { 2 , 512 },
        { 3 , 1024 },
        { 4 , 1536 }
    };

    RS = {
        { 1 , 0 },
        { 2 , 64 },
        { 3 , 128 },
        { 4 , 192 }
    };

    immediateConversion = { 0 , 256 };

    RDestination = 0;
    num_2 = 0;
    isOneNum = false;

}

