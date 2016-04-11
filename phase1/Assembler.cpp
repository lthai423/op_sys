#include "Assembler.h" // depends declared in interfaces

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

unsigned Assembler::returnFormat1(){
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

unsigned Assembler::returnFormat2_ADDR(){
    unsigned currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    unsigned destRegister = RD[RDestination];
    unsigned immediate = 256; //#
    return currentOpcode + destRegister + immediate + ADDR;
}

unsigned Assembler::returnFormat2_CONST(){
    unsigned currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    unsigned destRegister = RD[RDestination];
    unsigned immediate = 256; //#
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
            Rdestination = atoi(temp.c_str());
        else
            num_2 = atoi(temp.c_str());
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
        { 2 , 256 },
        { 3 , 512 },
        { 4 , 768 }
    };

    RS = {
        { 1 , 0 },
        { 2 , 32 },
        { 3 , 64 },
        { 4 , 96 }
    };

    immediateConversion = { 0 , 256 };

    RDestination = 0;
    num_2 = 0;
    isOneNum = false;

}

int Assembler::returnNumIn2sComp(){

}