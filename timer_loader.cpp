#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

#include "timer_loader.hpp"
#include "global_defines.hpp"
#include "timer_class.hpp"

namespace
{
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        using namespace std;
        stringstream ss;
        type2 t2;
        ss<< t1;
        ss>> t2;
        return t2;
    }
    
    inline bool is_file(const std::string& s)
    {
        using namespace boost::filesystem;
        return is_regular_file(path(s));
    }
    
    inline std::string timer_file()
    {
        return std::string(boost::filesystem::current_path().string() + "/" + std::string(TIMER_FILE));
    }
    
    
}

namespace timerLoad
{
    bool load_timer(timerObj::timer_class& timer)
    {
        using namespace timerObj;
        /*defaulting timer so that what we return is in accordance with what
        we retrieve: I.E. if we get nothing, we return nothing.*/
        timer = timer_class();
        
        //this is where the file should be: "./TIMER_FILE"
        std::string file(timer_file());
        if(!is_file(file))
        {
            file.erase();
            return false;
        }
        
        //so now we assume that the file exists:
        std::ifstream in;

        in.open(file.c_str(), std::ios::in);
        if(in.good())
        {
            in>> timer;
        }
        in.close();
        
        return (timer != timerObj::timer_class());
    }
    
    
}