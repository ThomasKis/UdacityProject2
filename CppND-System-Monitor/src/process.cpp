#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "processor.h"

using std::string;
using std::to_string;
using std::vector;

// ===== TK: Done: Return this process's ID
int Process::Pid() { return pid_; }
void Process::Pid(int Pid_Pids) {Process::pid_ = Pid_Pids;}

// ===== TK: Done: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    float seconds = LinuxParser::UpTime() - (float(LinuxParser::UpTime(pid_)) / sysconf(_SC_CLK_TCK));

    float CpuUtilization = (float(LinuxParser::ActiveJiffies(pid_)) / sysconf(_SC_CLK_TCK)) / seconds;
    return CpuUtilization; 
    }


// ===== TK: Done: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// ===== TK: Done: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// ===== TK: Done: Return the user (name) that generated this process
string Process::User() { return user_; }
void Process::User(int pid) { user_ = LinuxParser::User(pid);}

// =====TK: Done: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - (float(LinuxParser::UpTime(pid_)) / sysconf(_SC_CLK_TCK)); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return CpuUtilization() > a.CpuUtilization(); }