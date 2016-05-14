#include "os.h"
using namespace std;

//constructor
os::os()
{
     system("ls *.s > progs");

     systemTime = 0;
     ConSwitchTime = 0;
     jobsCPUtime = 0;
     numofprocessesCompleted = 0;
     SysCPUutilization = 0;
     userCPUutilization = 0;
     throughput = 0;
     vm.limit = 0;
     vm.__clock = 0;

     ifstream progfile;
     progfile.open("progs", ios::in)
     if(!progfile.is_open())
     {
          cout << "Progfile didn't open" << endl;
     }

     while(!progfile.eof())
     {
          string filename;
          getline(progfile, filename);

          PCB* p = new PCB(filename);
          jobs.push_back(p);
          assm.assemble(filename.c_str(), p);
     }
}
