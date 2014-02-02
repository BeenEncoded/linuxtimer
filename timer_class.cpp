#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

#include "timer_class.hpp"

using namespace std;

namespace
{
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        stringstream ss;
        type2 t2;
        ss<< t1;
        ss>> t2;
        return t2;
    }
    
    
}


/** File Stream Operators: */
namespace timerObj
{
    ostream& operator<<(ostream& out, clock_class& c)
    {
        out<< c.t.tv_sec<< c.delim;
        return out;
    }
    
    istream& operator>>(istream& in, clock_class& c)
    {
        c.t.tv_nsec = 0;
        if(!in.good())
        {
            return in;
        }
        string *temps(new string(""));
        getline(in, *temps, c.delim);
        if(!in.fail())
        {
            c.t.tv_nsec = conv<string, clock_t>(*temps);
        }
        temps->erase();
        delete temps;
        return in;
    }
    
    ostream& operator<<(ostream& out, timer_class& timer)
    {
        out<< timer.beg<< timer.seconds_set;
        return out;
    }
    
    istream& operator>>(istream& in, timer_class& timer)
    {
        timer = timer_class();
        if(in.good())
        {
            in>> timer.beg;
        }
        if(in.good())
        {
            in>> timer.seconds_set;
        }
        return in;
    }
    
    
}