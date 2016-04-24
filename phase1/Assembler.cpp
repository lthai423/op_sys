#include "Assembler.h" // depends declared in interfaces



using namespace std;

Assembler::Assembler(){
    ifstream assemblyProg;
    assemblyProg.open("prog.s");
    if (!assemblyProg.is_open())
        exit(0);
    initializeMemberFields();
    string line;
    getline(assemblyProg, line);
    instruction ins = instruction(0);
    while(!assemblyProg.eof()){
        storeSNN(line);
        if ((opcodes[instruct_opcode])[1] == 0)
            setFormat1(ins);
        else if ((opcodes[instruct_opcode])[1] == 1)
            setFormat2_ADDR(ins);
        else if ((opcodes[instruct_opcode])[1] == 2)
            setFormat2_CONST(ins);
        else
            setFormat3(ins);
        appendToFinal(ins);
        getline(assemblyProg, line);
        ins.i = 0;
    }
    //close first
    assemblyProg.close();

    //open/close and output program
    ofstream assembledProg;
    assembledProg.open ("prog.o", ofstream::out);
    if (!assembledProg.is_open())
        exit(2);
    assembledProg << FinalObjProg;
    assembledProg.close();

}

void Assembler::setFormat1(instruction &ins){
    ins.f1.OP = opcodes[instruct_opcode][0];   
    ins.f1.RD = first_num;
    ins.f1.RS = second_num;

    //defaulted to zero already, might remove
    ins.f1.I = 0;
    if (instruct_opcode == "halt"){
    }

}

void Assembler::setFormat2_CONST(instruction &ins){
    ins.f3.OP = opcodes[instruct_opcode][0];
    ins.f3.RD = first_num;
    ins.f3.CONST = second_num;
    ins.f3.I = 1;

}

void Assembler::setFormat2_ADDR(instruction &ins){
    ins.f2.OP = opcodes[instruct_opcode][0];
    ins.f2.RD = first_num;
    ins.f2.ADDR = second_num;
    if (instruct_opcode != "load")
        ins.f2.I = 1;

}

void Assembler::setFormat3(instruction &ins){
    ins.f2.OP = opcodes[instruct_opcode][0];
    ins.f2.ADDR = first_num;
    ins.f2.I = 1;
}
void Assembler::storeSNN(string &SNN){
    istringstream iss(SNN);
    int i = 0;
    string temp;
    while(iss >> temp){
        if (i == 0)
            instruct_opcode = temp;
        else if (i == 1)
            first_num = (uint16_t)atoi(temp.c_str());  //cast into 16 bit unsigned integer
        else
            second_num = (uint16_t)atoi(temp.c_str());
        i++;
    }
    if ( i == 1)
        first_num = second_num = 0; //zero out for one word opcode.

}

void Assembler::appendToFinal(instruction &ins){
    string castedString = to_string(ins.i);
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
        { "getstat", {{14, 0}} },
        { "putstat", {{15,0}} },
        { "jump", {{16,3}} },
        { "jumpl", {{17,3}} },
        { "jumpe", {{18,3}} },
        { "jumpg", {{19,3}} },
        { "call", {{20,3}} },
        { "return", {{21,0}} },
        { "read", {{22,0}} },
        { "write", {{23,0}} },
        { "halt", {{24,0}} },
        { "noop", {{25,0}} }

    };

    first_num = -9999; //defaulted to out of bound values
    second_num = -9999;

}

void Assembler::printContent(){
    cout << endl << FinalObjProg << endl;
}
