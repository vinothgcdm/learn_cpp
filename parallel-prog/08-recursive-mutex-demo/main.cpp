/**
 * Two shoppers adding garlic and potatoes to a shared notepad
 */

/**
 * 1. can be locked multiple times by the same thread
 * 2. must be unlocked as many times as it was locked
 */
#include <thread>
#include <mutex>
#include <stdio.h>

std::recursive_mutex pencil;
uint32_t garlic_count = 0;
uint32_t potato_count = 0;

void add_garlic()
{
    pencil.lock();
    garlic_count++;
    pencil.unlock();
}

void add_potato()
{
    pencil.lock();
    potato_count++;
    add_garlic();
    pencil.unlock();
}

void shopper()
{
    for (int i = 0; i < 10000; i++) {
        add_garlic();
        add_potato();
    }
}

int main()
{
    std::thread barron(shopper);
    std::thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic.\n", garlic_count);
    printf("We should buy %u potatoes.\n", potato_count);
}