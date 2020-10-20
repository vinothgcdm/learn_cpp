/**
 * Connecting cell phones to a charger
 */

/**
 * Mutex: Can only be acquired/released by the same thread
 * Semaphore: Can be acquired/released by different thread
 */
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(uint32_t init_count) {
        _count = init_count;
    }

    void acquire() { // decrement the internal counter
        std::unique_lock<std::mutex> lck(_m);
        while (!_count) {
            _cv.wait(lck);
        }
        _count--;
    }

    void release() { // increment the internal counter
        std::unique_lock<std::mutex> lck(_m);
        _count++;
        lck.unlock();
        _cv.notify_one();
    }

private:
    std::mutex _m;
    std::condition_variable _cv;
    uint32_t _count;
};

Semaphore charger(4);

void cell_phone(int id)
{
    charger.acquire();
    printf("Phone %d is charging...\n", id);
    srand(id); // charge for "random" amount between 1-3 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000 + 1000));
    printf("Phone %d is DONE charging!\n", id);
    charger.release();
}

int main()
{
    std::thread phones[10];

    for (int i = 0; i < 10; i++) {
        phones[i] = std::thread(cell_phone, i);
    }

    for (auto &p : phones) {
        p.join();
    }
}