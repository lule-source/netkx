#include "Thread.h"
#include "CurrentThread.h"
#include <semaphore>

std::atomic_int Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string &name)
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(func))
    , name_(name)
{
    setDefaultName();
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        thread_->detach(); 
    }
}

void Thread::start()  // a Thread object，detail info of a new thread
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    // start thread
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();
        sem_post(&sem);
        // start a new thread，just execute the thread function
        func_(); 
    }));

    // here must wait until get the new created thread's id values that above
    sem_wait(&sem);
}

void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if (name_.empty())
    {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}