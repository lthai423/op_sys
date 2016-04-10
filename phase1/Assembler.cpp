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
    opcode = opcodes

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
            RDestination = temp;
        else
            //cast string to int
            num_2 = temp;
        i++;
    } 
    if (i == 1) //ensure that num_2 is 0  if there is only one value
        num_2 = 0;
}

void Assembler::appendToFinal(int &){
    
}

void Assembler::initializeMemberFields() const{
    opcodes = {
                {"load", {


    }
}

int Assembler::returnNumIn2sComp(){

}