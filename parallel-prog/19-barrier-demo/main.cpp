/**
 * Deciding how many bags of chips to buy for the party
 */

/**
 * a barrier is a stopping point for a group of threads that prevents them
 * from proceeding until all, or enough threads, have reached the barrier.
 */
#include <thread>
#include <mutex>
#include <boost/thread/barrier.hpp>

uint32_t bags_of_chips = 1; // starts with one on the list
std::mutex pencil;
boost::barrier first_bump(10);

void cpu_worker(uint32_t workUnits)
{
    uint32_t x = 0;
    for (uint32_t i = 0; i < workUnits * 10000000; i++) {
        x++;
    }
}

void barron_shopper()
{
    cpu_worker(1); // do a bit of work first
    first_bump.wait();
    std::scoped_lock<std::mutex> lock(pencil);
    bags_of_chips *= 2;
    printf("Barron DOUBLE the bags of chips.\n");
}

void olivia_shopper()
{
    cpu_worker(1); // do a bit of work first
    {
        std::scoped_lock<std::mutex> lock(pencil);
        bags_of_chips += 3;
    }
    printf("Olivia ADDED 3 bags of chips.\n");
    first_bump.wait();
}

int main()
{
    std::thread shopper[10];

    for (int i = 0; i < 10; i += 2) {
        shopper[i] = std::thread(barron_shopper);
        shopper[i + 1] = std::thread(olivia_shopper);
    }

    for (auto &s : shopper) {
        s.join();
    }
    printf("We need to buy %u bags_of_chips.\n", bags_of_chips);
}