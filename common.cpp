#include <iostream>
#include <string>
#include <stdlib.h>

#include "common.hpp"
#include "global_defines.hpp"

using namespace cwrap;

namespace
{
    inline bool char_match(const char& ch, const std::string& s)
    {
        for(std::string::const_iterator it = s.begin(); it != s.end(); ++it)
        {
            if(ch == *it)
            {
                return true;
            }
        }
        return false;
    }
    
}

namespace common
{
    bool is_letter(const char& ch)
    {
        return char_match(ch, LETTERS);
    }
    
    bool is_number(const char& ch)
    {
        return char_match(ch, NUMBERS);
    }
    
    bool is_special(const char& ch)
    {
        return char_match(ch, SPECIALS);
    }
    
    bool is_char(const char& ch)
    {
        return (is_letter(ch) || is_number(ch) || is_special(ch));
    }
    
    
}