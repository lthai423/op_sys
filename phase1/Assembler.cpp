#include "Assembler.h" // depends declared in interfaces



using namespace std;

Assembler::Assembler(){
    fstream assemblyProg;
    assemblyProg.open("prog.s");
    initializeMemberFields();
    string line;
    getline(assemblyProg, line);
    while(!assemblyProg.eof()){
        storeSNN(line);
        if ((opcodes[instruct_opcode])[1] == 0)
            appendToFinal(returnFormat1());
        else if ((opcodes[instruct_opcode])[1] == 1)
            appendToFinal(returnFormat2_ADDR());
        else
            appendToFinal(returnFormat2_CONST());
        getline(assemblyProg, line);
    }

}

uint16_t Assembler::returnFormat1(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-11

    if (isOneNum){
        uint16_t destRegister = RD[RDestination];//bits 10-9
        // rest are dont cares
        return currentOpcode + destRegister ;  //SR bits 7-6 and unused bits 5-0 are don't cares
    }
    else{
        uint16_t destRegister = RD[RDestination]; //bits 10-9
        uint16_t sourceRegister = RS[ADDR_or_CONST]; //bits 7-6
        // bits 5-0 unused

        return currentOpcode + destRegister + sourceRegister;
    }

}

uint16_t Assembler::returnFormat2_ADDR(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    uint16_t destRegister = RD[RDestination];
    uint16_t immediate = 256; //#
    return currentOpcode + destRegister + immediate + ADDR_or_CONST;
}

uint16_t Assembler::returnFormat2_CONST(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    uint16_t destRegister = RD[RDestination];
    uint16_t immediate = 256; //#
    return currentOpcode + destRegister + immediate + ADDR_or_CONST;
}

void Assembler::storeSNN(string &SNN){
    istringstream iss(SNN);
    int i = 0;
    string temp;
    while(iss >> temp){
        if (i == 0)
            instruct_opcode = temp;
        else if (i == 1)
            RDestination = (uint16_t)atoi(temp.c_str());  //cast into 16 bit unsigned integer
        else
            ADDR_or_CONST = (uint16_t)atoi(temp.c_str());
        i++;
    } 
    if (i == 1) //ensure that num_2 is set out of bounds if there is only one value
        ADDR_or_CONST = -129; 
        isOneNum = true;
}

void Assembler::appendToFinal(uint16_t instr){
    string castedString = static_cast<ostringstream*>( &(ostringstream() << instr) )->str();
    FinalObjProg = castedString + "\n";
}

void Assembler::initializeMemberFields(){
    opcodes = {
        { "load", {{0,1}} },
        { "loadi", {{0,2}} },
        { "store", {{2048,1}} },
        { "add", {{4096,0}} },
        { "addi", {{4096,2}} },
        { "addc", {{6144,0}} },
        { "addci", {{6144,2}} },
        { "sub", {{8192,0}} },
        { "subi", {{8192,2}} },
        { "subc", {{10240,0}} },
        { "subci", {{10240,2}} },
        { "and", {{12248,0}} },
        { "andi", {{12248,2}} },
        { "xor", {{14336,0}} },
        { "xori", {{14336,2}} },
        { "compl", {{16384,0}} },
        { "shl", {{18432,0}} },
        { "shla", {{20480,0}} },
        { "shr", {{22528,0}} },
        { "shra", {{24576,0}} },
        { "compr", {{26624,0}} },
        { "compri", {{26624,2}} },
        { "getstat", {{28672,0}} },
        { "putstat", {{30720,0}} },
        { "jump", {{32768,1}} },
        { "jumpl", {{34816,1}} },
        { "jumpe", {{36864,1}} },
        { "jumpg", {{38912,1}} },
        { "call", {{40960,1}} },
        { "return", {{43008,0}} },
        { "read", {{45056,0}} },
        { "write", {{47104,0}} },
        { "halt", {{49152,0}} },
        { "noop", {{51200,0}} }
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

    RDestination = -9999; //defaulted to out of bound values
    ADDR_or_CONST = -9999;
    isOneNum = false;

}

