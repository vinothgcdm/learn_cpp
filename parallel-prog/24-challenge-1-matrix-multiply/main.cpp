/**
 * Challenge: Multiply two matrices
 */
#include <cmath>
#include <stdio.h>
#include <chrono>
#include <thread>

void print_matrix(uint32_t **array, size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            printf("%5u ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void sequential_matrix_multiply(uint32_t **A, size_t row_a, size_t col_a,
                                uint32_t **B, size_t row_b, size_t col_b,
                                uint32_t **C)
{
    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < col_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parallel_worker(uint32_t **A, size_t row_a, size_t col_a,
                     uint32_t **B, size_t row_b, size_t col_b,
                     uint32_t **C, size_t start_row_c, size_t end_row_c)
{
    for (size_t i = start_row_c; i < end_row_c; i++) {
        for (size_t j = 0; j < col_b; j++) {
            C[i][j] = 0;
            for (size_t k = 0; k < col_a; k++) {
                C[i][j] = A[i][k] * B[k][j];
            }
        }
    }
}

void parallel_matrix_multiply(uint32_t **A, size_t row_a, size_t col_a,
                              uint32_t **B, size_t row_b, size_t col_b,
                              uint32_t **C)
{
    size_t num_workers = std::thread::hardware_concurrency(); // get number of available processor in this computer
    size_t chunk_size = ceil((float)row_a / num_workers); // divid the rows of the output marrix into equel sized chunk for workers

    std::thread workers[num_workers];
    for (size_t i = 0; i < num_workers; i++) {
        size_t start_row_c = std::min(i * chunk_size, row_a);
        size_t end_row_c = std::min((i + 1) * chunk_size, row_a) - 1;
        // printf("%lu, %lu\n", start_row_c, end_row_c);
        workers[i] = std::thread(parallel_worker, A, row_a, col_a,
                                                  B, row_b, col_b,
                                                  C, start_row_c, end_row_c);
    }
    for (auto &w : workers) {
        w.join();
    }
    // printf("Workers: %lu, chunksize: %lu\n", num_workers, chunk_size);
}

int main()
{
    const uint32_t NUM_EVAL_RUNS = 3;
    const size_t NUM_ROWS_A = 1000;
    const size_t NUM_COLS_A = 1000;
    const size_t NUM_ROWS_B = NUM_COLS_A;
    const size_t NUM_COLS_B = 1000;

    // initialize A and B with values in range 1 to 100
    uint32_t **A = (uint32_t **)malloc(NUM_ROWS_A * sizeof(uint32_t *));
    uint32_t **B = (uint32_t **)malloc(NUM_ROWS_B * sizeof(uint32_t *));
    if ((A == NULL) || (B == NULL)) {
        exit(2);
    }

    for (size_t i = 0; i < NUM_ROWS_A; i++) {
        A[i] = (uint32_t *)malloc(NUM_COLS_A * sizeof(uint32_t));
        if (A[i] == NULL) {
            exit(2);
        }
        for (size_t j = 0; j < NUM_COLS_A; j++) {
            A[i][j] = rand() % 100 + 1;
        }
    }

    for (size_t i = 0; i < NUM_ROWS_B; i++) {
        B[i] = (uint32_t *)malloc(NUM_COLS_B * sizeof(uint32_t));
        if (B[i] == NULL) {
            exit(2);
        }
        for (size_t j = 0; j < NUM_COLS_B; j++) {
            B[i][j] = rand() % 100 + 1;
        }
    }

    // allocate array for sequential result and parallel result
    uint32_t **sequential_result = (uint32_t **)malloc(NUM_ROWS_A * sizeof(uint32_t *));
    uint32_t **parallel_result = (uint32_t **)malloc(NUM_ROWS_A * sizeof(uint32_t *));
    if ((sequential_result == NULL) || (parallel_result == NULL)) {
        exit(2);
    }
    for (size_t i = 0; i < NUM_ROWS_A; i++) {
        sequential_result[i] = (uint32_t *)malloc(NUM_COLS_B * sizeof(uint32_t));
        parallel_result[i] = (uint32_t *)malloc(NUM_COLS_B * sizeof(uint32_t));
        if ((sequential_result[i] == NULL) || (parallel_result[i] == NULL)) {
            exit(2);
        }
    }

    // Evaluating sequential implementation
    std::chrono::duration<double> sequential_time(0);
    for (uint32_t i = 0; i < NUM_EVAL_RUNS; i++)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A,
                                B, NUM_ROWS_B, NUM_COLS_B,
                                sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    sequential_time /= NUM_EVAL_RUNS;

    // print_matrix(A, NUM_ROWS_A, NUM_COLS_A);
    // print_matrix(B, NUM_ROWS_B, NUM_COLS_B);

    // Evaluate parallel implementation
    std::chrono::duration<double> parallel_time(0);
    for (uint32_t i = 0; i < NUM_EVAL_RUNS; i++)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A,
                                B, NUM_ROWS_B, NUM_COLS_B,
                                parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    parallel_time /= NUM_EVAL_RUNS;

    printf("Sequential multiply result: %.2f ms\n", sequential_time.count() * 1000);
    printf("  Parallel multiply result: %.2f ms\n", parallel_time.count() * 1000);
    printf("                   Speadup: %.2f\n", sequential_time / parallel_time);
    printf("                Efficiency: %.2f%%\n", 100 * ((sequential_time / parallel_time) / std::thread::hardware_concurrency()));
}

/**
 * Sequential multiply result: 4565.51 ms
 *   Parallel multiply result: 1157.99 ms
 *                    Speadup: 3.94
 *                 Efficiency: 49.28%
 */
