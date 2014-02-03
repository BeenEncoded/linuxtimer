#ifndef CWRAPPER_HPP_INCLUDED
#define CWRAPPER_HPP_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "curses.h"


//defines
#define endl '\n'
#define cout cwrap::curses_objects::stat_cout
#define cin cwrap::curses_objects::stat_cin

namespace cwrap
{
    class curses_wrapper_class;
    class curses_wrapper_output;
    class curses_wrapper_input;
    class curses_objects;
    
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
    
}


namespace
{
    void getline(cwrap::curses_wrapper_input&, std::string&, const char&);
    void getline(cwrap::curses_wrapper_input&, std::string&);
    bool kbhit();
    int gkey();
    void cls();
}


/** Output and input objects: */
namespace cwrap
{
    
    /* Base for the wrapper: */
    class curses_wrapper_class
    {
    public:
        explicit curses_wrapper_class()
        {
            if(!this->initialized)
            {
                this->counter++;
                initscr();
                keypad(stdscr, TRUE);
                cbreak();
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
                this->initialized = true;
            }
        }
        
        virtual ~curses_wrapper_class()
        {
            endwin();
        }
        
        static short counter;
        
    private:
        static bool initialized;
    };
    
    /* output: */
    class curses_wrapper_output : public curses_wrapper_class
    {
    public:
        explicit curses_wrapper_output(){}
        ~curses_wrapper_output(){}
        
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
        explicit curses_wrapper_input(){}
        ~curses_wrapper_input(){}
        
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
    
    class curses_objects
    {
    public:
        static curses_wrapper_class curses_base;
        static curses_wrapper_output stat_cout;
        static curses_wrapper_input stat_cin;
    };
    
}

//in-file functions
namespace
{
    /* Equivilant of the STL version. */
    inline void getline(cwrap::curses_wrapper_input& in, std::string& s, const char& delim)
    {
        short x(stdscr->_curx), y(stdscr->_cury);
        bool backspace_hit(false);
        nodelay(stdscr, FALSE);
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
    
    inline bool kbhit()
    {
        nodelay(stdscr, TRUE);
        noecho();
        return (getch() != ERR);
    }
    
    /* equivilant of getch() */
    inline int gkey()
    {
        nodelay(stdscr, FALSE);
        noecho();
        return getch();
    }
    
    inline void cls()
    {
        clear();
    }
}

#endif