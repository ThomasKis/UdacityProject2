#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  long JiffiesIdle();
  long JiffiesActive();
  long JiffiesTotal();

  // TODO: Declare any necessary private members
 private:
    int previdle_ = 0;
    int prevtotal_ = 0;
    long idle_jiffies_ = 0;
    long active_jiffies_ = 0;
    long jiffies_ = 0; 
};

#endif