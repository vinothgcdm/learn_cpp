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
            std::this_thread::yield();
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
    std::array<std::thread, 100000> guests;
    auto start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i < guests.size(); i++) {
        guests[i] = std::thread(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
    }
    for (size_t i = 0; i < guests.size(); i++) {
        guests[i].join();
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    printf("Elapsed time: %.2f\n", elapsed_time / 1000.0);
    printf("The philosophers are done eating.\n");
}
