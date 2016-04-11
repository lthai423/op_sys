#include "Assembler.h" // depends declared in interfaces

using namespace std;

Assembler::Assembler(){
    initializeMemberFields();
    string line;
    int rawBin;

    while(getline(cin, line)){
        storeSNN(line);
        if ((opcodes[instruct_opcode])[1] == 0){
            appendToFinal(returnFormat1());
        else
            appendToFinal(returnFormat2());
    }

}

int Assembler::returnFormat1(){
    int currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-11
    int immediate = immediateConversion[opcodes[instruct_opcode][1]]; //bit 8

    if (isOneNum){
        
    }
    else{
        int destRegister = RD[RDestination]; //bits 10-9
        int sourceRegister = RS[num_2]; //bits 7-6
        // bits 5-0 unused

        return currentOpcode + destRegister + immediate + sourceRegister;
    }

}

int Assembler::returnFormat2(){
    int currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    int destRegister = RD[RDestination];
    int immediate = immediateConversion[opcodes[instruct_opcode][1]];
    if (isOneNum){

    }
    else{
        
    }
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
    if (i == 1) //ensure that num_2 is 0  if there is only one value
        num_2 = 0;
        isOneNum = true;
}

void Assembler::appendToFinal(int &instr){
    string castedString = static_cast<ostringstream*>( &(ostringstream() << instr) )->str();
    FinalObjProg = castedString + "\n";
}

void Assembler::initializeMemberFields() const{
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

    RDestination = 0;
    num_2 = 0;
    isOneNum = false;

}

int Assembler::returnNumIn2sComp(){



}
