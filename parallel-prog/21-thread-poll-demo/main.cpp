/**
 * Chopping vegetables with a thread pool
 */
#include <chrono>
#include <boost/asio.hpp>

void vegeteble_chopper(int vegeteble_id)
{
    printf("Thread %d chopped vegeteble %d.\n", std::this_thread::get_id(), vegeteble_id);
}

int main()
{
    auto start_time = std::chrono::steady_clock::now();

    // std::thread choppers[10000];
    // for (int i = 0; i < 10000; i++) {
    //     choppers[i] = std::thread(vegeteble_chopper, i);
    // }
    // for (auto &c: choppers) {
    //     c.join();
    // }

    boost::asio::thread_pool pool(4); // 4 threads
    for (int i = 0; i < 10000; i++) {
        boost::asio::post(pool, [i](){vegeteble_chopper(i);});
    }
    pool.join();

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    printf("Elapsed time: %lu ms\n", elapsed_time);
}

/**
 * Create 10000 threads separately:
 * Elapsed time: 3637 ms
 * Elapsed time: 3702 ms
 * Elapsed time: 3606 ms
 * Elapsed time: 3628 ms
 * Elapsed time: 3628 ms
 *          Avg: 3640.2 ms
 * 
 * Use thread pool (only 4 threads has created):
 * Elapsed time: 1635 ms
 * Elapsed time: 1578 ms
 * Elapsed time: 1609 ms
 * Elapsed time: 1587 ms
 * Elapsed time: 1587 ms
 *          Avg: 1599.2 ms
 */
