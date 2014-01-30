#include <iostream>

#include "cwrapper.hpp"
#include "common.hpp"

using namespace cwrap;


/** Menu stuff: */
namespace
{
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
            cout<< " 1 -  Start timer (under construction!)"<< endl;
            cout<< " 2 -  Set timer (under construction!)"<< endl;
            cout<< endl;
            cout<< " q -  Exit"<< endl;
            ch = tolower(gkey());
            switch(ch)
            {
                case '1':
                {
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