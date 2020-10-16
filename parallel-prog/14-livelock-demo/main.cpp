/**
 * Exceptionally polite philosophers, thinking and eating sushi
 */
#include <thread>
#include <mutex>

int sushi_count = 5000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
    while (sushi_count > 0) {
        first_chopstick.lock();
        if (!second_chopstick.try_lock())
        {
            first_chopstick.unlock();
        } else {
            if (sushi_count) {
                sushi_count--;
            }
            second_chopstick.unlock();
            first_chopstick.unlock();
        }
    }
    // printf("Philosopher %d done eating.\n", std::this_thread::get_id());
}

int main()
{
    std::mutex chopstick_a;
    std::mutex chopstick_b;
    std::array<std::thread, 10000> guests;
    for (size_t i = 0; i < guests.size(); i++) {
        guests[i] = std::thread(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    }
    for (size_t i = 0; i < guests.size(); i++) {
        guests[i].join();
    }
   printf("The philosophers are done eating.\n");
}