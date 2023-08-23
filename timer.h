#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <thread>
#include <chrono>


class Timer
{

    std::thread Thread;
    bool Alive = false; //will check if timer is running
    long CallNumber = -1L;
    long repeat_count = -1L;
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;


    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
        {
            funct();
        }
    }

    void ThreadFunc()
    {
        if(CallNumber == -1L)//-1 means we call the function infinite number of times
        {
            while(Alive)
            {
                SleepAndRun();
            }
        }
        else
        {
            while(repeat_count--)
            {
                SleepAndRun();
            }

        }
    }

public:

    //constructor
    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long repeat) : funct(f),
                               interval(std::chrono::milliseconds(i)),
                               CallNumber(repeat) {}

    //starts the timer
    void Start()
    {
        if(IsAlive())
        {
            return;
        }
        Alive = true;
        repeat_count = CallNumber;
        Thread = std::thread(ThreadFunc, this);
    }

    //manually stops the timer
    void Stop()
    {
        Alive = false;
        Thread.join();

    }

    //is the timer running or not?
    bool IsAlive() const {return Alive;}
};

#endif // TIMER_H_INCLUDED
