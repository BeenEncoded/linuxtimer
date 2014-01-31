#include <iostream>
#include <unistd.h>
#include <sstream>

#include "cwrapper.hpp"
#include "common.hpp"
#include "timer_class.hpp"

using namespace cwrap;


/** Menu stuff: */
namespace
{
    template<class type1, class type2>
    inline type2 conv(const type1& t1)
    {
        std::stringstream ss;
        type2 t2;
        ss<< t1;
        ss>> t2;
        return t2;
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
    
    inline void display_timer(const timerObj::time_info_data& timer, const bool& finished)
    {
        common::center(std::string(
                (finished ? "OVERTIME: " : std::string("")) + 
                formatted_number(timer.hours, 2) + " : " + 
                formatted_number(timer.minutes, 2) + " : " +
                formatted_number(timer.seconds, 2) + " : " +
                formatted_number(timer.miliseconds, 2)));
    }
    
    inline void test_timer()
    {
        using namespace timerObj;
        using namespace common;
        
        timer_class timer;
        timer.set(5);
        timer.start();
        while(!kbhit())
        {
            cls();
            for(short x = 0; x < 10; x++) cout<< endl;
            display_timer(timer.time_left(), timer.finished());
            usleep((1000000 / 30));
        }
    }
    
    inline void main_menu()
    {
        cout.set_color(white);
        using namespace common;
        
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
            cout<< " 1 -  Start timer (under testing)"<< endl;
            cout<< " 2 -  Set timer (under construction!)"<< endl;
            cout<< endl;
            cout<< " q -  Exit"<< endl;
            ch = tolower(gkey());
            switch(ch)
            {
                case '1':
                {
                    test_timer();
                }
                break;
                
                case '2':
                {
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
}

int main()
{
    main_menu();
    return 0;
}