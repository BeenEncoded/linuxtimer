#include <iostream>
#include <unistd.h>
#include <sstream>

#include "cwrapper.hpp"
#include "common.hpp"
#include "timer_class.hpp"
#include "global_defines.hpp"

using namespace cwrap;


/** Menu stuff: */
namespace
{
    
    void main_menu();
    void set_timer(timerObj::timer_class&);
    void start_timer(timerObj::timer_class&);
    void display_timer(const timerObj::time_info_data&, const bool&);
    std::string formatted_number(const unsigned int&, const short&);
    
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        std::stringstream ss;
        type2 t2;
        ss<< t1;
        ss>> t2;
        return t2;
    }
    
    inline void main_menu()
    {
        cout.set_color(white);
        using namespace common;
        
        timerObj::timer_class timer;
        
        char ch;
        while(true)
        {
            cls();
            cout<< endl;
            center("Timer");
            cout<< endl;
            for(short x = 0; x < 3; x++) cout<< endl;
            cout.set_color(blue);
            center("UNDER CONSTRUCTION!");
            cout.set_color(white);
            cout<< endl;
            cout<< " 1 -  Start timer"<< endl;
            cout<< " 2 -  Set timer"<< endl;
            cout<< endl;
            cout<< " q -  Exit"<< endl;
            ch = tolower(gkey());
            switch(ch)
            {
                case '1':
                {
                    start_timer(timer);
                }
                break;
                
                case '2':
                {
                    set_timer(timer);
                }
                break;
                
                case 'q':
                {
                    return;
                }
                break;
                
                default:
                    break;
            }
        }
    }
    
    inline void set_timer(timerObj::timer_class& timer)
    {
        using namespace common;
        using namespace common::input;
        timerObj::time_info_data tempt = timer.time_set();
        
        std::string temps("");
        int ch;
        while(true)
        {
            cls();
            cout<< endl;
            center("Set Timer: ");
            cout<< endl;
            for(short x = 0; x < 3; x++) cout<< endl;
            cout<< " 1 -  Hours: "<< formatted_number(tempt.hours, 2)<< endl;
            cout<< " 2 -  Minutes: "<< formatted_number(tempt.minutes, 2)<< endl;
            cout<< " 3 -  Seconds: "<< formatted_number(tempt.seconds, 2)<< endl;
            cout<< endl;
            cout<< " [BACKSPACE] -  Done"<< endl;
            ch = gkey();
            switch(is_char(char(ch)))
            {
                case true:
                {
                    switch(char(ch))
                    {
                        case '1':
                        {
                            temps = get_user_string(("Hours currently set to: " + conv<unsigned int, std::string>(tempt.hours) +
                                    std::string("\n\n\nEnter the number of hours: ")));
                            if(temps != GSTRING_CANCEL)
                            {
                                (string_is_int(temps) ? (tempt.hours = conv<std::string, unsigned int>(temps)) : (tempt.hours = 0));
                                timer.set(timerObj::clock_class(tempt));
                            }
                            temps.erase();
                        }
                        break;

                        case '2':
                        {
                            temps = get_user_string(("Minutes currently set to: " + conv<unsigned int, std::string>(tempt.minutes) +
                                    std::string("\n\n\nEnter the number of Minutes: ")));
                            if(temps != GSTRING_CANCEL)
                            {
                                (string_is_int(temps) ? (tempt.minutes = conv<std::string, unsigned int>(temps)) : (tempt.minutes = 0));
                                timer.set(timerObj::clock_class(tempt));
                            }
                            temps.erase();
                        }
                        break;

                        case '3':
                        {
                            temps = get_user_string("Seconds currently set to: " + conv<unsigned int, std::string>(tempt.seconds) + 
                                    std::string("\n\n\nEnter the number of seconds: "));
                            if(temps != GSTRING_CANCEL)
                            {
                                (string_is_int(temps) ? (tempt.seconds = conv<std::string, unsigned int>(temps)) : (tempt.seconds = 0));
                                timer.set(timerObj::clock_class(tempt));
                            }
                            temps.erase();
                        }
                        break;

                        default:
                            break;
                    }
                }
                break;
                
                case false:
                {
                    switch(ch)
                    {
                        case KEY_BACKSPACE:
                        {
                            return;
                        }
                        break;
                        
                        default:
                            break;
                    }
                }
                break;
                
                default:
                    break;
            }
        }
    }
    
    inline void start_timer(timerObj::timer_class& timer)
    {
        using namespace common;
        timer.start();
        while(!kbhit())
        {
            cls();
            for(short x = 0; x < 10; x++) cout<< endl;
            display_timer(timer.time_left(), timer.finished());
            
            //run at 30-frames per second.  This should be enough to not over-tax the terminal
            usleep(1000000 / 30);
        }
    }
    
    inline void display_timer(const timerObj::time_info_data& timer, const bool& finished)
    {
        common::center(std::string(
                (finished ? "OVERTIME: " : std::string("")) + 
                formatted_number(timer.hours, 2) + " : " + 
                formatted_number(timer.minutes, 2) + " : " +
                formatted_number(timer.seconds, 2) + " : " +
                formatted_number(timer.miliseconds, 2)));
    }
    
    inline std::string formatted_number(const unsigned int& x, const short& digits)
    {
        std::string temps("");
        short digits_of_x(conv<unsigned int, std::string>(x).size());
        if(digits_of_x < digits)
        {
            for(short y = digits_of_x; y < digits; y++)
            {
                temps += "0";
            }
        }
        temps += conv<unsigned int, std::string>(x);
        return temps;
    }
    
}

int main()
{
    main_menu();
    return 0;
}