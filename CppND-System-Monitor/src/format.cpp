#include <string>

#include "format.h"

using std::string;

// ===== TK: Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int s,m,h;
    string dtime, dh, dm, ds;
    h = seconds/60/60;
    m = (seconds-h*60*60)/60;
    s = seconds - h*60*60 - m*60;
    if(h<10){
     dh = "0" + std::to_string(h);
    }
    else{
     dh = std::to_string(h);  
    }
    if(m<10){
     dm = "0" + std::to_string(m);
    }
    else{
     dm = std::to_string(m);  
    }
    if(s<10){
     ds = "0" + std::to_string(s);
    }
    else{
     ds = std::to_string(s);  
    }
    dtime = dh + ":" + dm + ":" + ds;
    return dtime;
}