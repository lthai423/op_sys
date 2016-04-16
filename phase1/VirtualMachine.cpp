#include "VirtualMachine.h"

using namespace std;

VirtualMachine::VirtualMachine(){
  populateMemory(); //set base and limit in there

  //start fetch-decode-execute cycle
  while (pc < MEM_SIZE){
    ir = mem[pc++] //fetch
    execute(pc); //
  }
}

void VirtualMachine::populateMemory(){
  r = vector <int> (REG_FILE_SIZE);
  mem = vector <int> (MEM_SIZE);
  fstream prog;
  prog.open("prog.o");
  string line, temp;
  istringstream iss;
  getline(prog, line);
  int i;
  while(!prog.eof()){
        iss << temp; //ensures no whitespace
    mem[i++] = (uint16_t)atoi(temp.c_str());
  }
  base = 0;
  limit = i;
  //memory is now populated
}

void VirtualMachine::execute(int &pc){
        instruction ins(pc); // make constructor with int as parameter
        (*instr[ins.f1.OP])();  // ==  (functionName)(); functionName.base == beginning addr in mem loc
}


void VirtualMachine::setCarryBit()
{

}

{

}

void VirtualMachine::setEqualBit()
{

}

void VirtualMachine::setGreaterBit()
{

}

void VirtualMachine::LOAD(){
        int RD =
        r[RD] += mem[ADDR];
}

void VirtualMachine::LOADI(){
        r[RD] += CONST;
}

void VirtualMachine::STORE()
{
        mem[ADDR] = r[RD];
}

void VirtualMachine::ADD()
{
        r[RD] += r[RS];
    setCarryBit();
}

void VirtualMachine::populateFunctionMap(){
        instr = {
                { 0 , &VirtualMachine::LOAD },
                { 0 , &VirtualMachine::LOADI },
                { 1 , &VirtualMachine::STORE },
                { 2 , &VirtualMachine::ADD },
                { 2 , &VirtualMachine::ADDI },
                { 3 , &VirtualMachine::ADDC },
                { 3 , &VirtualMachine::ADDCI },
                { 4 , &VirtualMachine::SUB },
                { 4 , &VirtualMachine::SUBI },
                { 5 , &VirtualMachine::SUBC },
                { 5 , &VirtualMachine::SUBCI },
                { 6 , &VirtualMachine::AND },
                { 6 , &VirtualMachine::ANDI },
                { 7 , &VirtualMachine::XOR },
                { 7 , &VirtualMachine::XORI },
                { 8 , &VirtualMachine::COMPL },
                { 9 , &VirtualMachine::SHL },
                { 10 , &VirtualMachine::SHLA },
                { 11 , &VirtualMachine::SHR },
                { 12 , &VirtualMachine::SHRA },
                { 13 , &VirtualMachine::COMPR },
                { 13 , &VirtualMachine::COMPRI },
                { 14 , &VirtualMachine::GETSTAT },
                { 15 , &VirtualMachine::PUTSTAT },
                { 16 , &VirtualMachine::JUMP },
                { 17 , &VirtualMachine::JUMPL },
                { 18 , &VirtualMachine::JUMPE },
                { 19 , &VirtualMachine::JUMPG },
                { 20 , &VirtualMachine::CALL },
                { 21 , &VirtualMachine::RETURN },
                { 22 , &VirtualMachine::READ },
                { 23 , &VirtualMachine::WRITE },
                { 24 , &VirtualMachine::HALT },
                { 25 , &VirtualMachine::NOOP }
        }
}

void VirtualMachine::ADDI()
{
    r[RD] += CONST;
    setCarryBit();
}

void VirtualMachine::ADDC()
{
        r[RD] += r[RS] + returnCarryBit();
        setCarryBit();  //guarantees to set the carry bit
}

void VirtualMachine::ADDCI()
{
    r[RD] += CONST + returnCarryBit();
    setCarryBit();      //guarantees to set the carry bit
}

void VirtualMachine::SUB()
{
        r[RD] -= r[RS];
        setCarryBit();
}

void VirtualMachine::SUBI()
{
        r[RD] -= CONST;
        setCarryBit();
}

void VirtualMachine::SUBC()
{
        r[RD] = r[RD] - r[RS] - returnCarryBit();
        setCarryBit();
}

void VirtualMachine::SUBCI()
{
        r[RD] = r[RD] - CONST - returnCarryBit();
	  setCarryBit();
}

void VirtualMachine::AND()
{
        r[RD] = r[RD] & r[RS];
}

void VirtualMachine::ANDI()
{
        r[RD] = r[RD] & CONST;
}

void VirtualMachine::XOR()
{
        r[RD] = r[RD] ^ r[RS];
}

void VirtualMachine::XORI()
{
        r[RD] = r[RD] ^ CONST;
}

void VirtualMachine::COMPL()
{
        r[RD] = ~r[RD]; //bit negation
}

void VirtualMachine::SHL()
{
        r[RD] = r[RD] << 1;
        //shift bit needs to be set to 0 **LOOK INTO THIS**
}

void VirtualMachine::SHLA()
{
        //shift left arithmetic
}

void VirtualMachine::SHR()
{
        r[RD] = r[RD] >> 1;
        //shift bit needs to be set to 0
}

void VirtualMachine::SHRA()
{
        //shift right arithmetic
}

void VirtualMachine::COMPR()
{
        if (r[RD] < r[RS])
            setLessBit();
        else if (r[RD] == r[RS])
                setEqualBit();
        else (r[RD] > r[RS])
                setGreaterBit();
}

void VirtualMachine::COMPRI()
{
        if(r[RD]<CONST)
           setLessBit();
        else if(r[RD] == CONST)
                setEqualBit();
        else (r[RD] > CONST)
                setGreaterBit();
}

void VirtualMachine::GETSTAT()
{
        r[RD] = SR;
}

void VirtualMachine::PUTSTAT()
{
        SR = r[RD];
}

void VirtualMachine::JUMP()
{
        pc = ADDR;
        //Needs work
}

void VirtualMachine::JUMPL()
{
        if(setLessBit() == 1)
            pc = ADDR;
        //Needs work
}

void VirtualMachine::JUMPE()
{
        if(setEqualBit() == 1)
            pc=ADDR;
        //Needs work
}

void VirtualMachine::JUMPG()
{
        if(setGreaterBit() == 1)
            pc = ADDR;
        //Needs work
}

void VirtualMachine::CALL()
{
        stack<uint16_t> x;
        pc = ADDR
        x.push(pc);

        //Needs work
}

void VirtualMachine::RETURN()
{
        x.pop();
        pc -> where it was pointing initially... would this be a location in mem?


        //Needs work
}

void VirtualMachine::READ()
{

        //read new content of r[RD] from .in file?
}

void VirtualMachine::WRITE()
{
        //write r[RD] into .outfile
}

void VirtualMachine::HALT()
{
        //halt exec.done()?
}

void VirtualMachine::NOOP()
{

}


