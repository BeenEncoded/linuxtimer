#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED
#include <string>
#include <iostream>
#include <unistd.h>

#include "cwrapper.hpp"
#include "global_defines.hpp"

namespace common
{
    inline void center(const std::string& s)
    {
        int middle(s.size() / 2);
        switch(middle >= cout.mid())
        {
            case true:
            {
                middle = 0;
            }
            break;
            
            case false:
            {
                middle = (cout.mid() - middle);
            }
            break;
            
            default:
                break;
        }
        for(int x = 0; x < middle; x++) cout<< " ";
        cout<< s;
    }
    
    bool is_letter(const char&);
    bool is_number(const char&);
    bool is_special(const char&);
    bool is_char(const char&);
    
    inline bool string_is_int(const std::string& s)
    {
        if(s.size() == 0)
        {
            return false;
        }
        for(std::string::const_iterator it = s.begin(); it != s.end(); ++it)
        {
            if(!is_number(*it))
            {
                return false;
            }
        }
        return true;
    }
    
    namespace input
    {
        std::string get_user_string(const std::string&);
    }
    
}

#endif