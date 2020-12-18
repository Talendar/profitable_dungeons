#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <mutex>
#include <condition_variable>


class Semaphore {
public:
    Semaphore(int count = 1);
    void wait();    // "down" operation
    void signal();  // "up" operation

private:
    int count;                   // number of free resources currently available
    std::mutex mtx;              // mutually exclusive (mutex) flag
    std::condition_variable cv;  // handles the blocking of one or more threads
};

#endif // SEMAPHORE_H
