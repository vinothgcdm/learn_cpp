/**
 * Challenge: Sort an array of random integers with merge sort
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <cmath>

#define HW_CONCURRENCY 2
// #define HW_CONCURRENCY std::thread::hardware_concurrency()

void merge(int array[], size_t left, size_t middle, size_t right)
{
    size_t left_arr_size = middle - left + 1;
    size_t right_arr_size = right - middle;
    int left_arr[left_arr_size];
    int right_arr[right_arr_size];

    std::copy(array + left, array + middle + 1, left_arr);
    std::copy(array + middle + 1, array + right + 1, right_arr);

    // printf("[");
    // for (size_t i = 0; i < left_arr_size; i++) {
    //     printf("%d, ", left_arr[i]);
    // }
    // printf("] ");
    // printf(" [");
    // for (size_t i = 0; i < right_arr_size; i++) {
    //     printf("%d, ", right_arr[i]);
    // }
    // printf("] = ");

    size_t left_arr_pos = 0;
    size_t right_arr_pos = 0;
    size_t result_arr_pos = left;
    while ((left_arr_pos < left_arr_size) && (right_arr_pos < right_arr_size)) {
        if (left_arr[left_arr_pos] < right_arr[right_arr_pos]) {
            array[result_arr_pos] = left_arr[left_arr_pos];
            result_arr_pos++;
            left_arr_pos++;
        } else {
            array[result_arr_pos] = right_arr[right_arr_pos];
            result_arr_pos++;
            right_arr_pos++;
        }
    }

    while (left_arr_pos < left_arr_size) {
        array[result_arr_pos] = left_arr[left_arr_pos];
        result_arr_pos++;
        left_arr_pos++;
    }

    while (right_arr_pos < right_arr_size) {
        array[result_arr_pos] = right_arr[right_arr_pos];
        result_arr_pos++;
        right_arr_pos++;
    }

    // printf("[");
    // for (size_t i = left; i <= right; i++) {
    //     printf("%d, ", array[i]);
    // }
    // printf("]\n");
}

void sequential_merge_sort(int array[], size_t left, size_t right)
{
    size_t middle = 0;

    if (left < right) {
        middle = (left + right) / 2;
        // printf("%3lu %3lu %3lu\n", left, middle, right);
        sequential_merge_sort(array, left, middle);
        sequential_merge_sort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void parallel_merge_sort(int array[], size_t left, size_t right, size_t depth = 0)
{
    if (depth >= HW_CONCURRENCY) {
        sequential_merge_sort(array, left, right);
    } else {
        size_t mid = (left + right) / 2;
        std::thread left_thread = std::thread(parallel_merge_sort, array, left, mid, depth + 1);
        parallel_merge_sort(array, mid + 1, right, depth + 1);
        left_thread.join();
        merge(array, left, mid, right);
    }
}

int main()
{
    const uint32_t NUM_EVAL_RUNS = 100;
    const size_t N = 100000;
    int original_array[N];
    int sequential_result[N];
    int parallel_result[N];

    srand(time(NULL));
    for (size_t i = 0; i < N; i++) {
        original_array[i] = rand() % 100 + 1;
    }

    std::copy(original_array, &original_array[N], sequential_result);
    std::copy(original_array, &original_array[N], parallel_result);

    // // print the original array
    // for (size_t i = 0; i < N; i++) {
    //     printf("%d, ", original_array[i]);
    // }
    // printf("\n");

    std::chrono::duration<double> sequential_sort_elapsed_time(0);
    for (uint32_t i = 0; i < NUM_EVAL_RUNS; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        sequential_merge_sort(sequential_result, 0, N - 1);
        auto end_time = std::chrono::high_resolution_clock::now();
        sequential_sort_elapsed_time += end_time - start_time;
    }
    sequential_sort_elapsed_time /= NUM_EVAL_RUNS;

    std::chrono::duration<double> parallel_sort_elapsed_time(0);
    for (uint32_t i = 0; i < NUM_EVAL_RUNS; i++) {
        auto start_time = std::chrono::high_resolution_clock::now();
        parallel_merge_sort(parallel_result, 0, N - 1);
        auto end_time = std::chrono::high_resolution_clock::now();
        parallel_sort_elapsed_time += end_time - start_time;
    }
    parallel_sort_elapsed_time /= NUM_EVAL_RUNS;

    printf("Sequential sort elapsed time: %.2f ms\n", sequential_sort_elapsed_time.count() * 1000);
    printf("  Parallel sort elapsed time: %.2f ms\n", parallel_sort_elapsed_time.count() * 1000);
    printf("                     Speedup: %.2f\n", sequential_sort_elapsed_time.count() / parallel_sort_elapsed_time.count());
    printf("                  Efficiency: %.2f%%\n", 100 * (sequential_sort_elapsed_time.count() / parallel_sort_elapsed_time.count()) / HW_CONCURRENCY);
    printf("        Hardware concurrency: %d\n", HW_CONCURRENCY);
}

/**
 * Sequential sort elapsed time: 17.16 ms
 *   Parallel sort elapsed time: 8.44 ms
 *                      Speedup: 2.03
 *                   Efficiency: 101.71%
 *         Hardware concurrency: 2
 */
