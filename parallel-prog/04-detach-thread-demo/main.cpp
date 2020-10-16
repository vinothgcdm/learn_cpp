/**
 * Barron finishes cooking while Olivia cleans
 */
#include <thread>
#include <chrono>
#include <stdio.h>

void kitchen_cleaner()
{
    while (true) {
        printf("Olivia cleaned the kitchen.\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread olivia(kitchen_cleaner);
    olivia.detach();

    for (int i = 0; i < 30; i++) {
        printf("Barron is cokking...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    printf("Barron is done!\n");
    printf("Does olivia joinable: %s\n", olivia.joinable() ? "Yes" : "No");
}
