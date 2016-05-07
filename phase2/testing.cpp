#include<iostream>
using namespace std;

int main()
{
   class SR
   {
       public:
           unsigned CARRY:1;
           unsigned GREATER_THAN:1;
           unsigned EQUAL_TO:1;
           unsigned LESS_THAN:1;
           unsigned OVERFLOW:1;
           unsigned RETURN_STATUS:3;
           unsigned IN_OUT_REGS:2;
           unsigned DONTCARE:6;     
   };

   union STATUS_REGISTER{
           int i;
           SR s;
        };

    STATUS_REGISTER sr,sr1,sr2,sr3,sr4,sr5,sr6,sr7;
    
    sr.i = 0x0000;

    cout << "This is the RETURN_STATUS: " << sr.s.RETURN_STATUS << endl;

    sr1.i = 0x0020;

    cout << "This is the RETURN_STATUS: " << sr1.s.RETURN_STATUS << endl;

    sr2.i = 0x0040;

    cout << "This is the RETURN_STATUS: " << sr2.s.RETURN_STATUS << endl;

    sr3.i = 0x0060;

    cout << "This is the RETURN_STATUS: " << sr3.s.RETURN_STATUS << endl;

    sr4.i = 0x0080;

    cout << "This is the RETURN_STATUS: " << sr4.s.RETURN_STATUS << endl;

    sr5.i = 0x00A0;

    cout << "This is the RETURN_STATUS: " << sr5.s.RETURN_STATUS << endl;

    sr6.i = 0x00C0;

    cout << "This is the RETURN_STATUS: " << sr6.s.RETURN_STATUS << endl;

    sr7.i = 0x00E0;

    cout << "This is the RETURN_STATUS: " << sr7.s.RETURN_STATUS << endl;


}