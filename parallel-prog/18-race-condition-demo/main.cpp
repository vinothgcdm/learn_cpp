/**
 * Deciding how many bags of chips to buy for the party
 */

/**
 * Data race and race condition are two different potential problems in
 * concurrent programs.
 * 
 * Data race can occur when two or more threads concurrently access the
 * same memory location.
 * 
 * A race condition is a flaw in the timing or ordering of a program's
 * execution that caused incorrect behaviour.
 * 
 * In practice, many race conditions are caused by data race and many
 * data race lead to race conditions. But those two problems are not
 * dependent on each other. it's possible to have data races without a
 * race condition, and race condition without a data race.
 */
#include <thread>
#include <mutex>

uint32_t bags_of_chips = 1; // starts with one on the list
std::mutex pencil;

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
    std::scoped_lock<std::mutex> lock(pencil);
    bags_of_chips *= 2;
    printf("Barron DOUBLE the bags of chips.\n");
}

void olivia_shopper()
{
    cpu_worker(1); // do a bit of work first
    std::scoped_lock<std::mutex> lock(pencil);
    bags_of_chips += 3;
    printf("Olivia ADDED 3 bags of chips.\n");
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