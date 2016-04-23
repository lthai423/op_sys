#include "Assembler.h" // depends declared in interfaces



using namespace std;

Assembler::Assembler(){
    ifstream assemblyProg;
    assemblyProg.open("prog.s");
    initializeMemberFields();
    string line;
    getline(assemblyProg, line);
    int i = 0; //remove after testing
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
    assemblyProg.close();
    ofstream prog("prog.o", ofstream::out);
    prog << FinalObjProg;
    prog.close();

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
    return currentOpcode + destRegister + immediate + immediate + ADDR_or_CONST;
}

uint16_t Assembler::returnFormat2_CONST(){
    uint16_t currentOpcode = (opcodes[instruct_opcode][0]); //bits 15-10
    uint16_t destRegister = RD[RDestination];
    uint16_t immediate = 256; //#
    return currentOpcode + destRegister + immediate + immediate + ADDR_or_CONST;
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
    FinalObjProg = FinalObjProg + castedString + "\n";
}

void Assembler::initializeMemberFields(){
    opcodes = {
        { "load", {{0,1}} },
        { "loadi", {{0,2}} },
        { "store", {{1,1}} },
        { "add", {{2,0}} },
        { "addi", {{2,2}} },
        { "addc", {{3,0}} },
        { "addci", {{3,2}} },
        { "sub", {{4,0}} },
        { "subi", {{4,2}} },
        { "subc", {{5,0}} },
        { "subci", {{5,2}} },
        { "and", {{6,0}} },
        { "andi", {{6,2}} },
        { "xor", {{7,0}} },
        { "xori", {{7,2}} },
        { "compl", {{8,0}} },
        { "shl", {{9,0}} },
        { "shla", {{10,0}} },
        { "shr", {{11,0}} },
        { "shra", {{12,0}} },
        { "compr", {{13,0}} },
        { "compri", {{13,2}} },
        { "getstat", {{14,0}} },
        { "putstat", {{15,0}} },
        { "jump", {{16,1}} },
        { "jumpl", {{17,1}} },
        { "jumpe", {{18,1}} },
        { "jumpg", {{19,1}} },
        { "call", {{20,1}} },
        { "return", {{21,0}} },
        { "read", {{22,0}} },
        { "write", {{23,0}} },
        { "halt", {{24,0}} },
        { "noop", {{25,0}} }
    };

    immediateConversion = { 0 , 256 };

    RDestination = -9999; //defaulted to out of bound values
    ADDR_or_CONST = -9999;
    isOneNum = false;

}


