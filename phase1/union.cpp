/*********************************************************************
union.cpp
K Zemoudeh
4/5/10

This program illustrates how to use "union" in parsing different VM
formats.
**********************************************************************/

#include <iostream>
#include "union.h"

class printInstr{
public:
	printInstr(){printIt();};
private:
	void printIt(){instruction ins(12412); cout << ins.f1.OP << " " << ins.f1.RD << " " << ins.f1.I << " " << ins.f1.RS << " " << ins.f1.UNUSED << endl;};



};

main()
{
	printInstr print1;


	// instruction ins(13512);

	// //ins.i = 0xa007;
	// // ins.i = 1351;
	// //ins.i = 1093;

	// //cout << hex;
	// cout << ins.i << endl;
	// cout << ins.f1.OP << " " << ins.f1.RD << " " << ins.f1.I << " " << ins.f1.RS << " " << ins.f1.UNUSED << endl;
	// cout << ins.f2.OP << " " << ins.f2.RD << " " << ins.f2.I << " " << ins.f2.ADDR << endl;
	// cout << ins.f3.OP << " " << ins.f3.RD << " " << ins.f3.I << " " << ins.f3.CONST << endl;
}
