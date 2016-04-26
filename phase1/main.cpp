#include "Assembler.h"
#include "VirtualMachine.h"

using namespace std;

int main(int argc, char *argv[]){
	Assembler assembler;
	VirtualMachine vm;

	assembler.assemble(argv[1]);
    cout << endl << " is Assembled between" << endl;

	vm.run(argv[1]);
}