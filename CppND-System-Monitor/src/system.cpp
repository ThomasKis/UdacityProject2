#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();
    while(!pids.empty()){
      Process a;
      a.Pid(pids.back());
      pids.pop_back();
      
      a.User(a.Pid());

      
      
      //Ausgabe << a.Pid() << " " << pids.size() << "\n";
      processes_.push_back(a);
      //Ausgabe << a.Pid() << " " << pids.size() << "\n";
    }
    std::sort (processes_.begin(),processes_.end());
    return processes_; }

// ===== TK: Done: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// ===== TK: Done: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// ===== TK: Done: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// ===== TK: Done: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// ===== TK: Done: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// ===== TK: Done: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }