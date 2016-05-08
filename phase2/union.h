#ifndef UNION_H
#define UNION_H


#include <iostream>
//#include <iomanip>
#include <stdint.h>

using namespace std;

class format0 {
	public:
	    uint16_t CARRY:1;
	    uint16_t GREATERTHAN:1;
	    uint16_t EQUALTO:1;
	    uint16_t LESSTHAN:1;
	    uint16_t OVERFLOW:1;
	    uint16_t VMRETURNSTATUS:3;
	    uint16_t IOREG:2;
	    uint16_t DONTCARE:6;
};

class format1 {
	public:
		uint16_t UNUSED:6;
		uint16_t RS:2;
		uint16_t I:1;
		uint16_t RD:2;
		uint16_t OP:5;
	};

class format2 {
	public:
		uint16_t ADDR:8;
		uint16_t I:1;
		uint16_t RD:2;
		uint16_t OP:5;
	};


class format3 {
	public:
		int CONST:8;
		uint16_t I:1;
		uint16_t RD:2;
		uint16_t OP:5;

	};

union instruction {
	int i;
        format0 sr;
	format1 f1;
	format2 f2;
	format3 f3;
	instruction(int i){
		this -> i = i;
	}

};

#endif
