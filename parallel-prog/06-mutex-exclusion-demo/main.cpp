/**
 * Two shoppers adding items to a shared notepad
 */
#include <thread>
#include <mutex>
#include <stdio.h>

uint32_t garlic_count = 0;
std::mutex pencil;

void shopper()
{
    for (int i = 0; i < 10; i++) {
        pencil.lock();
        garlic_count++;
        pencil.unlock();
    }
}

int main()
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic.\n", garlic_count);
}
