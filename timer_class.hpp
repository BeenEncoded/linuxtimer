#ifndef TIMER_CLASS_HPP_INCLUDED
#define TIMER_CLASS_HPP_INCLUDED
#include <string>
#include <unistd.h>
#include <time.h>
#include <fstream>

namespace timerObj
{
    class clock_class;
    class timer_class;
    
    struct time_info_data;
    
    struct time_info_data
    {
        unsigned int hours, minutes, seconds, miliseconds;
    };
    
    std::ifstream& operator>>(std::ifstream&, clock_class&);
    std::ofstream& operator<<(std::ofstream&, clock_class&);
    
    class clock_class
    {
    public:
        friend std::ifstream& operator>>(std::ifstream&, clock_class&);
        friend std::ofstream& operator<<(std::ofstream&, clock_class&);
        
        explicit clock_class() : t(), delim(2) {}
        explicit clock_class(const time_info_data& tid) : t(), delim(2)
        {
            t.tv_nsec = (((unsigned long)1000000000 / 100) * tid.miliseconds);
            t.tv_sec = ((tid.hours * 60 * 60) + (tid.minutes * 60) + tid.seconds);
        }
        
        explicit clock_class(const long& ct) : t(), delim(2)
        {
            this->t.tv_nsec = ct;
        }
        
        ~clock_class(){}
        
        clock_class operator=(const clock_class& cc)
        {
            if(this != &cc)
            {
                this->t.tv_nsec = cc.t.tv_nsec;
                this->t.tv_sec = cc.t.tv_sec;
            }
            return *this;
        }
        
        bool operator==(const clock_class& cc) const
        {
            return ((this->t.tv_nsec == cc.t.tv_nsec) && (this->t.tv_sec == cc.t.tv_sec));
        }
        
        bool operator<(const clock_class& cc) const
        {
            return (this->t.tv_nsec < cc.t.tv_nsec);
        }
        
        bool operator<=(const clock_class& cc) const
        {
            return (this->t.tv_nsec <= cc.t.tv_nsec);
        }
        
        bool operator>(const clock_class& cc) const
        {
            return (this->t.tv_nsec > cc.t.tv_nsec);
        }
        
        bool operator>=(const clock_class& cc) const
        {
            return (this->t.tv_nsec >= cc.t.tv_nsec);
        }
        
        /* Returns the clock_t that the class is set to */
        const long& raw() const
        {
            return this->t.tv_nsec;
        }
        
        /* Returns the raw information calculated into
         hours, minutes, seconds, and miliseconds. */
        time_info_data gtime() const
        {
            unsigned long temp(this->t.tv_nsec), persec(1000000000);
            time_info_data time_info;
            
            time_info.hours = (temp / persec / 60 / 60);
            temp %= (persec * 60 * 60);
            
            time_info.minutes = (temp / persec / 60);
            temp %= (persec * 60);
            
            time_info.seconds = (temp / persec);
            temp %= persec;
            
            time_info.miliseconds = (temp / (persec / 100));
            return time_info;
        }
        
    private:
        timespec t;
        char delim;
        
    };
    
    
    class timer_class
    {
    public:
        explicit timer_class() : beg(0), 
                seconds_set(0) {}
        
        ~timer_class(){}
        
        /* Starts the timer, by setting the beginning time. */
        void start()
        {
            timespec tempt;
            clock_gettime(CLOCK_REALTIME, &tempt);
            this->beg = clock_class((tempt.tv_nsec + (tempt.tv_sec * (unsigned long)1000000000)));
        }
        
        /* Sets the timer, in seconds. */
        void set(const unsigned int& sec)
        {
            this->seconds_set = clock_class((sec * (unsigned long)1000000000));
        }
        
        /* Allows the user to set the timer using clock_class, which
         can be initialized with time_info_data to make it easy to
         set the hours, minutes, and seconds the timer is to run.*/
        void set(const clock_class& cc)
        {
            this->seconds_set = cc;
        }
        
        /* Returns the amount of time left on the clock.  If the end_time
         has been passed, then it will start counting up.*/
        time_info_data time_left() const
        {
            timespec tempt;
            clock_gettime(CLOCK_REALTIME, &tempt);
            unsigned long now((tempt.tv_nsec + (tempt.tv_sec * (unsigned long)1000000000))), end(this->end_time());
            if(end < now)
            {
                std::swap(end, now);
            }
            return clock_class(end - now).gtime();
        }
        
        /* Returns true if the timer has passed the end time.  This
         allows it to count up from zero, once the end_time has been
         reached, acting as an "overtime" clock.*/
        bool finished() const
        {
            timespec tempt;
            clock_gettime(CLOCK_REALTIME, &tempt);
            return ((unsigned long)this->end_time() <= (tempt.tv_nsec + (tempt.tv_sec * (unsigned long)1000000000)));
        }
        
    private:
        clock_class beg, seconds_set;
        
        long end_time() const
        {
            return clock_t((this->beg.raw() + this->seconds_set.raw()));
        }
        
    };
}

#endif