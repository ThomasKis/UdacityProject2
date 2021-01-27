#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"
#include "process.h"

// ===== TK: Done: Return the aggregate CPU utilization
float Processor::Utilization() { 
    
    std::vector<std::string> cpuvalues = LinuxParser::CpuUtilization();
    
    int idle = std::stoi(cpuvalues.at(3)) + std::stoi(cpuvalues.at(4));
    int active = std::stoi(cpuvalues.at(0)) + std::stoi(cpuvalues.at(1)) + std::stoi(cpuvalues.at(2));
    int total = active + idle;

    float cpu1 = (total - prevtotal_) - (idle - previdle_);
    float cpu2 = (total - prevtotal_);
    float cpu = cpu1/cpu2;
    

    previdle_ = idle;
    prevtotal_ = total;

    idle_jiffies_ = idle;
    active_jiffies_ = active;
    jiffies_ = total;

//std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xxAusgabe.txt");
//Ausgabe << idle << ", Size:" << sizeof(idle) <<"\n";
//Ausgabe << idle_jiffies_ << ", Size:" << sizeof(idle_jiffies_) << "\n";
//Ausgabe << cpu << "\n";
//Ausgabe << cpu*100 << "\n";

    return cpu;
}

long Processor::JiffiesIdle() {return idle_jiffies_;}
  