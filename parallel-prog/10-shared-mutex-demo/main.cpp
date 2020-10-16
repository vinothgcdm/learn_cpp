/**
 * Several users reading a calendar, but only a few users updating it
 */

/**
 * Result:
 *   Using mutex elapsed time is 15.46 seconds.
 *   Using shared_mutex elsapsed time is 3.68 seconds.
 */
#include <thread>
#include <mutex>
#include <chrono>
#include <shared_mutex>

char weekdays[][10] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
uint32_t today = 0;
std::shared_mutex marker;
// std::mutex marker;

void calender_reader(const int id)
{
    for (int i = 0; i < 7; i++) {
        marker.lock_shared();
        // marker.lock();
        printf("Reader-%d sees today is %s\n", id, weekdays[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        marker.unlock_shared();
        // marker.unlock();
    }
}

void calender_writer(const int id)
{
    for (int i = 0; i < 7; i++) {
        marker.lock();
        today = (today + 1) % 7;
        printf("Writer-%d updated date to %s\n", id, weekdays[today]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        marker.unlock();
    }
}

int main()
{
    /* create ten reader threads but only two writer threads */
    std::array<std::thread, 10> readers;
    for (uint32_t i = 0; i < readers.size(); i++) {
        readers[i] = std::thread(calender_reader, i);
    }

    std::array<std::thread, 2> writers;
    for (uint32_t i = 0; i < writers.size(); i++) {
        writers[i] = std::thread(calender_writer, i);
    }

    auto start_time = std::chrono::steady_clock::now();
    /* wait for readers and writers to finish */
    for (uint32_t i = 0; i < readers.size(); i++) {
        readers[i].join();
    }   
    for (uint32_t i = 0; i < writers.size(); i++) {
        writers[i].join();
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    printf("Elapsed time: %.2f seconds!\n", elapsed_time / 1000.0);
}
