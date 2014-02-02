#ifndef TIMER_LOADER_HPP_INCLUDED
#define TIMER_LOADER_HPP_INCLUDED
#include <string>

#include "timer_class.hpp"

namespace timerLoad
{
    /* returns true if loaded, false if failed. */
    bool load_timer(timerObj::timer_class&);
    
    
}

#endif