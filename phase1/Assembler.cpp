#include "Assembler.h" // depends declared in interfaces

using namespace std;

Assembler::Assembler(){
    initializeMemberFields();
    string line;
    int rawBin;
    while(getline(cin, line)){
        storeSNN(line);
        if (opcodes.second[1] == 0){\
            rawBin = returnFormat1();
        else
            rawBin = returnFormat2();
        
        appendToFinal(rawBin);
    }

}

int Assembler::returnFormat1(){

}

int Assembler::returnFormat2(){

}

void Assembler::storeSNN(string &SNN){
    istringstream iss(SNN);
    int i = 0;
    string temp;
    while(iss >> temp){
        if (i == 0)
            instruct_opcode = temp;
        else if (i == 1)
            //cast int to string
            N1 = temp;
        else
            //cast string to int
            N2 = temp;
    } 
}

void Assembler::appendToFinal(int &){
    
}

void Assembler::initializeMemberFunctions() const{
    opcodes = {
                {"load", {


    }
}
