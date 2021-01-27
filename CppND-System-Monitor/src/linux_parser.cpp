#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// ===== TK: Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, MemType;
  float value, MemValue01=0, MemValue02=0;
  std::ifstream InputFile(kProcDirectory + kMeminfoFilename);
  if (InputFile.is_open()){
    while (std::getline(InputFile, line)) {
      std::istringstream linestream(line);
      linestream >> MemType >> value;
      if (MemType == "MemTotal:") {
        MemValue01 = value;
      }
      else if(MemType == "MemFree:") {
        MemValue02 = value;
      }
      else if(MemValue01 !=0 &&  MemValue02 !=0) {
      break;
      }
    }  
  }
  //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xxAusgabe.txt");
  //Ausgabe << line << "\n";
  //Ausgabe << MemType01 << " " << MemValue01 << "\n" << "\n";
  //Ausgabe << MemValue01 << " " << MemValue02 << "\n" << "\n";
  //Ausgabe << (MemValue01-MemValue02)/MemValue01;
  InputFile.close();
  return (MemValue01-MemValue02)/MemValue01;
   
}

// ===== TK: Done: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::string line;
long value01, value02; 
std::ifstream InputFile(kProcDirectory+kUptimeFilename);
if(InputFile.is_open()){
  std::getline(InputFile, line);
  std::stringstream linestream(line);
  linestream >> value01 >> value02;  
//std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xxAusgabe.txt");
//Ausgabe << line << "\n";
//Ausgabe << value01 << " " << value02 << "\n" << "\n";
}
InputFile.close();
return value01; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// ===== TK: Done: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line, value;
  long ActiveJiffiesPID = 0;
  std::ifstream InputFile(kProcDirectory+"/"+std::to_string(pid)+kStatFilename);
  if(InputFile.is_open()){
    getline(InputFile, line);
    std::stringstream linestream(line);
    //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
    for(int i=1; i<=15;i++){
      linestream >> value;
      //Ausgabe << value << "\n";
      if(i==14 || i==15){
        ActiveJiffiesPID = ActiveJiffiesPID + stoi(value);
      }
    }
  }
  InputFile.close();
  return ActiveJiffiesPID; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// ===== TK: Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, type, value;
  vector<string> cpu;
  std::ifstream InputFile(kProcDirectory+kStatFilename);
  if(InputFile.is_open()){
    while(getline(InputFile, line)){
      std::stringstream linestream(line);
      linestream >> type;
      if(type == "cpu"){
        while(linestream >> value){
          cpu.push_back(value);
        }
        break;
      }
    }
  }
//std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
//Ausgabe << line << "\n";
//Ausgabe << cpu.at(0) << " " << cpu.at(1) << " " << cpu.at(2) << " " << cpu.at(3) << " " << cpu.at(4) << "\n" << "\n";
  return cpu; 
}

// ===== TK: Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
std::string line, type;
int value; 
std::ifstream InputFile(kProcDirectory+kStatFilename);
if(InputFile.is_open()){
  while(std::getline(InputFile, line)){
    std::stringstream linestream(line);
    linestream >> type >> value;
    if(type == "processes"){
      break;
    } 
  }
}
InputFile.close();
return value;
}

// ===== TK: Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
std::string line, type;
int value; 
std::ifstream InputFile(kProcDirectory+kStatFilename);
if(InputFile.is_open()){
  while(std::getline(InputFile, line)){
    std::stringstream linestream(line);
    linestream >> type >> value;
    if(type == "procs_running"){
      break;
    } 
  }
}
InputFile.close();
return value;  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string line;
  std::ifstream InputFile(kProcDirectory+"/"+std::to_string(pid)+kCmdlineFilename);
  if(InputFile.is_open()){
    std::getline(InputFile, line);
  }
  //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
  //Ausgabe << line << "\n";
  InputFile.close();
  return line; 
}

// ===== TK: Done: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string line, type, value;
  std::ifstream InputFile(kProcDirectory+"/"+std::to_string(pid)+kStatusFilename);
  if(InputFile.is_open()){
    while(std::getline(InputFile, line)){
      std::stringstream linestream(line);
      linestream >> type >> value;
      if(type == "VmSize:"){
        //value = std::to_string(std::stoi(value)/1000);
        value.insert(value.end()-3,1,'.');
        value.erase(value.end()-2,value.end());
        break;
      }

    }
  }
  //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
  //Ausgabe << type << " " << value << "\n";
  InputFile.close();
  return value; 
}

// ===== TK: Done: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::string line, type, value;
  std::ifstream InputFile(kProcDirectory+"/"+std::to_string(pid)+kStatusFilename);
  if(InputFile.is_open()){
    //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xxAusgabe.txt");
    while(std::getline(InputFile, line)){
      std::stringstream linestream(line);
      linestream >> type >> value;
      if(type == "Uid:"){
       break;
      }
    }
    //Ausgabe << pid << " " << value << "\n";
  }
  InputFile.close();
  return value; 
}

// ===== TK: Done: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
string line, value, x, user;
  std::ifstream InputFile(kPasswordPath);
  if (InputFile.is_open()) {
    while (std::getline(InputFile, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::stringstream linestream(line);
      linestream >> user >> x >> value;
      //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xxAusgabe.txt");
      //Ausgabe << user << " " << x << " " << value << "\n";
      if(value == LinuxParser::Uid(pid)) {
        break;
      }
    }
  }
  InputFile.close();
  return user; 
}

// ===== TK: Done: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, value;
  long UpTimePID = 0;
  std::ifstream InputFile(kProcDirectory+"/"+std::to_string(pid)+kStatFilename);
  if(InputFile.is_open()){
    getline(InputFile, line);
    std::stringstream linestream(line);
    //std::ofstream Ausgabe("/home/workspace/CppND-System-Monitor/xAusgabe.txt");
    for(int i=1; i<=22;i++){
      linestream >> value;
      //Ausgabe << value << "\n";
      if(i==22){
        UpTimePID = stoi(value);
      }
    }
  }
  InputFile.close();
  return UpTimePID; }