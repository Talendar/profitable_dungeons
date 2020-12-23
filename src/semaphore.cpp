#include "semaphore.h"


/**
 * Base constructor.
 * @param count: number of free resources initially available.
 */
Semaphore::Semaphore(int count) {
    this->count = count;
}


/**
 *  Implements the semaphore's "up" operation. Should be called when the thread
 * has finished using the resource. Notifies the waiting threads that the resource
 * is available.
 */
void Semaphore::signal() {
    std::unique_lock<std::mutex> lock(this->mtx);
    this->count++;  // +1 free resource
    this->cv.notify_one();  // notifying one of the threads waiting on cv
}


/**
 *  Implements the semaphore's "down" operation. Should be called when the thread
 * wants to use the resource. The calling thread will wait untill the resource
 * is available.
 */
void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(this->mtx);
    while(count == 0)
        cv.wait(lock);  // waiting for a resource

    count--;  // -1 free resource
}
