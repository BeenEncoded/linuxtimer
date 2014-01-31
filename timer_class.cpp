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
    ofstream& operator<<(ofstream& out, clock_class& c)
    {
        out<< c.t.tv_sec<< c.delim;
        return out;
    }
    
    ifstream& operator>>(ifstream& in, clock_class& c)
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
    
    
}