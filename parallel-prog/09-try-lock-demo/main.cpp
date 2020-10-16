/**
 * Two shoppers adding items to a shared notepad
 */
#include <thread>
#include <mutex>
#include <chrono>

uint32_t items_on_notepad = 0;
std::mutex pencil;

void shopper(const char* name)
{
    int item_to_add = 0;

    while (items_on_notepad <= 20) {
        /* add item(s) to shared items_on_notepad */
        if (item_to_add && pencil.try_lock()) {
            items_on_notepad += item_to_add;
            printf("%s added %u item(s) to notpad.\n", name, item_to_add);
            item_to_add = 0;
            /* time spent writing */
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            pencil.unlock();
        }
        /* look for other things to buy */
        else {
            /* time spent searching */
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            item_to_add++;
            printf("%s found something else to buy.\n", name);
        }
    }
}

int main()
{
    std::thread barron(shopper, "Barron");
    std::thread olivia(shopper, "Olivia");
    auto start_time = std::chrono::steady_clock::now();
    barron.join();
    olivia.join();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
    printf("Elapsed time: %.2f seconds\n", elapsed_time / 1000.0);
}
