/**
 * Recursively sum range of numbers
 */
#include <cstdio>
#include <chrono>
#include <future>

unsigned long long int recursive_sum(uint32_t lo, uint32_t hi)
{
    if ((hi - lo) <= 100) { // base case threshold
        unsigned long long int sum = 0;
        for (auto i = lo; i < hi; i++) {
            sum += i;
        }
        return sum;
    } else { // divide and conquer
        auto mid = (hi + lo) / 2; // middle index for spliting
        auto left = recursive_sum(lo, mid);
        auto right = recursive_sum(mid, hi);
        return left + right;
    }
}

unsigned long long int recursive_sum_parallel_execution(uint32_t lo, uint32_t hi, uint32_t depth)
{
    if (depth > 3) { // base case threshold
        unsigned long long int sum = 0;
        for (auto i = lo; i < hi; i++) {
            sum += i;
        }
        return sum;
    } else { // divide and conquer
        auto mid = (hi + lo) / 2; // middle index for spliting
        auto left = std::async(std::launch::async, recursive_sum_parallel_execution, lo, mid, depth + 1);
        auto right = recursive_sum_parallel_execution(mid, hi, depth + 1);
        return left.get() + right;
    }
}

int main()
{
    auto start_time = std::chrono::steady_clock::now();
    // unsigned long long int total = recursive_sum(0, 100000000);
    unsigned long long int total = recursive_sum_parallel_execution(0, 100000000, 0);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    printf("Total: %llu\n", total);
    printf("Elapse time: %lu ms\n", elapsed_time);
}

/**
 * Parallel execution:
 * Total: 4999999950000000
 * Elapse time: 41 ms
 * 
 * Sequential execution:
 * Total: 4999999950000000
 * Elapse time: 220 ms
 */
