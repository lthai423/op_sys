#include "os.h"
#include "PCB.h"
#include "Assembler.h"
#include "VirtualMachine.h"
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

	  p->ofile.open(p->ofileName.c_str(), ios::in);
	  if(!p->ofile.is_open())
          {
               cout << "Error: " << p->ofileName << "failed to open" << endl;
	       exit();

          }
          int limit = p->base;
	  string line;
	  getline(p->ofile, line);
	  istringstream str(line.c_str());
	  str >> vm.mem[limit];
	  limit++;
	  vm.limit++;
	  while(getline(p->ofile,line).good())
	  {
	       istringstream str(line.c_str());
	       str >> vm.mem[limit];
	       limit++;
	       vm.limit++;
          }
	  if(p->base>0)
              p->limit += p->base;
	  p->ofile.close();
 	  p->outfile.open(p->outfileName.c_str(), ios::out);
	  p->infile.open(p->infileName.c_str(), ios::in);

     }
     
     for(list<PCB::iterator it = jobs.begin; it!=jobs.end(); it++)
     {
	  readyQ.push(*it);
     }
}

os::run()
{
	running = readyQ.front();
	readyQ.pop();
	while(true)
	{
	

	}
        
        vm.ir=0;
	
}
