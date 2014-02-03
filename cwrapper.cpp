
#include "cwrapper.hpp"

namespace cwrap
{
    bool curses_wrapper_class::initialized = false;
    short curses_wrapper_class::counter = 0;
    
    curses_wrapper_class curses_objects::curses_base = curses_wrapper_class();
    curses_wrapper_output curses_objects::stat_cout = curses_wrapper_output();
    curses_wrapper_input curses_objects::stat_cin = curses_wrapper_input();
}