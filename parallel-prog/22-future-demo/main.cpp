/**
 * Check how many vegetables are in the pantry
 */
#include <future>

int how_many_vegetebles()
{
    printf("Olivia is counting vegetebles...\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 10;
}

int main()
{
    printf("Barron ask Olivia how many vegetebles are in the pantry.\n");
    std::future<int> result = std::async(std::launch::async, how_many_vegetebles);
    printf("Barron can do other things while he waits for the result...\n");
    printf("Olivia responded with %d.\n", result.get());
}
