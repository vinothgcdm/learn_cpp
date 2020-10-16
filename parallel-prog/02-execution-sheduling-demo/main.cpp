/**
 * Two threads chopping vegetables
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>

using namespace std;

bool chopping = true;

void vegetable_chopper(const char *name)
{
    uint32_t vegetable_count = 0;

    while (chopping) {
        vegetable_count++;
    }

    /*  "cout" gives mixed output on screen in multithread environment.
     *  Ex: BarronOlivia chopped  chopped 747683860752112619 vegetables vegetables */
    // cout << name << " chopped " << vegetable_count << " vegetables" << endl;

    printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main()
{
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    cout << "Barron and Olivia are chopping vegetables..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;
    barron.join();
    olivia.join();
}
