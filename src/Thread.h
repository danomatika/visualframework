#ifndef THREAD_H
#define THREAD_H

#include "Common.h"
#include "SDL/SDL_thread.h"

class Thread
{
    public:

        enum Type {
            NORMAL, // run run() once
            LOOP    // loop run() and wait for stopThread()
        };

        Thread(std::string name, Type type=NORMAL);

        virtual ~Thread();

        void startThread();

        void stopThread();

        void waitThread();

        void killThread();

        bool isThreadRunning() {return !_bRun;}

        int getThreadID();

        std::string getThreadName() {return _name;}

    protected:

        virtual void run() = 0;

    private:

        void _run();

        static int threadFunc(void* data);

        SDL_Thread* _thread;
        bool _bRun;
        Type _type;
        std::string _name;
};

#endif // THREAD_H
