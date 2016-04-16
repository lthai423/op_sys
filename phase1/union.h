#ifndef UNION_H
#define UNION_H


#include <iostream>
//#include <iomanip>

using namespace std;

class format1 {
	public:
		unsigned UNUSED:6;
		unsigned RS:2;
		unsigned I:1;
		unsigned RD:2;
		unsigned OP:5;
	};

class format2 {
	public:
		unsigned ADDR:8;
		unsigned I:1;
		unsigned RD:2;
		unsigned OP:5;
	};


class format3 {
	public:
		int CONST:8;
		unsigned I:1;
		unsigned RD:2;
		unsigned OP:5;

	};

union instruction {
	int i;
	format1 f1;
	format2 f2;
	format3 f3;
	instruction(int instr){
		i = instr;
	}
};

#endif