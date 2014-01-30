#ifndef CWRAPPER_HPP_INCLUDED
#define CWRAPPER_HPP_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "curses.h"

namespace
{
    
    inline bool kbhit()
    {
        nodelay(stdscr, TRUE);
        noecho();
        cbreak();
        return (getch() != ERR);
    }
    
    /* equivilant of getch() */
    inline char gkey()
    {
        nodelay(stdscr, FALSE);
        cbreak();
        noecho();
        char ch(getch());
        return ch;
    }
    
    inline void cls()
    {
        clear();
    }
}

namespace cwrap
{
    class curses_wrapper_class;
    class curses_wrapper_output;
    class curses_wrapper_input;
    
    //all the different colors:
    enum color_type{
        red = 1,
        green = 2,
        yellow = 3,
        blue = 4,
        cyan = 5,
        magneta = 6,
        white = 7,
        black = 8
    };
    
    /* Base for the wrapper: */
    class curses_wrapper_class
    {
    public:
        explicit curses_wrapper_class()
        {
            initscr();
            keypad(stdscr, TRUE);
            nocbreak();
            echo();
            
            if (has_colors())
            {
                start_color();
                init_pair(1, COLOR_RED,     COLOR_BLACK);
                init_pair(2, COLOR_GREEN,   COLOR_BLACK);
                init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
                init_pair(4, COLOR_BLUE,    COLOR_BLACK);
                init_pair(5, COLOR_CYAN,    COLOR_BLACK);
                init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
                init_pair(7, COLOR_WHITE,   COLOR_BLACK);
                init_pair(8, COLOR_BLACK, COLOR_WHITE);
            }
        }
        
        ~curses_wrapper_class()
        {
            endwin();
        }
         
    };
    
    /* output: */
    class curses_wrapper_output : public curses_wrapper_class
    {
    public:
        
        template<class type>
        curses_wrapper_output& operator<<(const type& t)
        {
            std::stringstream *ss(new std::stringstream());
            (*ss)<< t;
            char ch;
            
            while(ss->good())
            {
                ss->get(ch);
                if(!ss->fail())
                {
                    this->print_char(ch);
                }
            }
            delete ss;
            return *this;
        }
        
        void set_color(const color_type& col) const
        {
            short cx(stdscr->_curx), cy(stdscr->_cury);
            this->setcol(col);
            
            for(short x = stdscr->_begx; x <= COLS; x++)
            {
                for(short y = stdscr->_begy; y <= LINES; y++)
                {
                    mvaddch(y, x, inch());
                }
            }
            move(cy, cx);
        }
        
        short mid() const
        {
            return (COLS / 2);
        }
        
    private:
        void setcol(const short& col) const
        {
            if(has_colors())
            {
                attrset(COLOR_PAIR(col));
            }
        }
        
        void print_char(const char& ch) const
        {
            addch(ch);
        }
    };
    
    /* Input */
    class curses_wrapper_input : public curses_wrapper_class
    {
    public:
        
        template<class type>
        curses_wrapper_input& operator>>(const type& t)
        {
            std::stringstream *ss(new std::stringstream());
            do
            {
                (*ss)<< gkey();
            }
            while(ss->str().back() != ' ');
            ss>> t;
            delete ss;
            return *this;
        }
        
    };
    
}

namespace
{
    cwrap::curses_wrapper_output cout;
    cwrap::curses_wrapper_input cin;
    
    /* Equivilant of the STL version. */
    inline void getline(cwrap::curses_wrapper_input& in, std::string& s, const char& delim)
    {
        short x(stdscr->_curx), y(stdscr->_cury);
        bool backspace_hit(false);
        nodelay(stdscr, FALSE);
        cbreak();
        noecho();
        s.erase();
        do
        {
            s += char(getch());
            
            //erase if we backspace
            if(s.back() == char(KEY_BACKSPACE))
            {
                s.resize((s.size() - (((s.size() - 1) > 0) ? 2 : 1)));
                if(!backspace_hit)
                {
                    backspace_hit = true;
                }
            }
            
            //now re-display the string:
            move(y, x);
            for(std::string::const_iterator it = s.begin(); it != s.end(); ++it) addch(*it);
            
            //if backspace was hit, then the size of the string will be reduced, meaning there will be a character not refreshed.  refresh it:
            if(backspace_hit)
            {
                addch(' ');
                move(stdscr->_cury, ((stdscr->_curx > stdscr->_begx) ? (stdscr->_curx - 1) : stdscr->_curx));
            }
            refresh();
        }
        while(s.back() != delim);
        if(s.size() > 0)
        {
            if(s.back() == delim)
            {
                s.resize(s.size() - 1);
            }
        }
    }
    
    inline void getline(cwrap::curses_wrapper_input& in, std::string& s)
    {
        getline(in, s, '\n');
    }
    
    
#define endl '\n'
}

#endif