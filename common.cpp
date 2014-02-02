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
    
    namespace input
    {
        std::string get_user_string(const std::string& message)
        {
            std::string input;
            char ch;
            while(true)
            {
                cls();
                for(short x = 0; x < 10; x++) cout<< endl;
                cout<< ((message.size() > 0) ? message : ">> ")<< input;
                ch = gkey();
                switch(is_char(ch))
                {
                    case true:
                    {
                        input += ch;
                    }
                    break;

                    case false:
                    {
                        switch(ch)
                        {
                            case char(KEY_BACKSPACE):
                            {
                                if(input.size() > 0)
                                {
                                    input.resize((input.size() - 1));
                                }
                            }
                            break;

                            case char(ESCAPE_KEY):
                            {
                                input.erase();
                                return GSTRING_CANCEL;
                            }
                            break;
                            
                            case char(ENTER_KEY):
                            {
                                return input;
                            }
                            break;

                            default:
                            {
                            }
                            break;
                        }
                    }
                    break;

                    default:
                        break;
                }
            }
            return GSTRING_CANCEL;
        }
    }
    
}