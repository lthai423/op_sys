#ifndef SR_H
#define SR_H


#include <iostream>
//#include <iomanip>
#include <stdint.h>

using namespace std;

class sr {
	public:
		uint16_t UNUSED:6;
		uint16_t RS:2;
		uint16_t I:1;
		uint16_t RD:2;
		uint16_t OP:5;
	};



union s_r {
	int i;
	sr status;
};

#endif