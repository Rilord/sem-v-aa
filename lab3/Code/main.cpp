#include <iostream>
#include "sorts.h"

#include <chrono>
#include <random>
#include <algorithm>

#define BENCHMARK

#define NOT_MEASURED "not measured"

enum class sort_type { ASCENDING = 1, DESCENDING };

static std::random_device r;

typedef void (*sort_func) (int [], unsigned int);

int *create_random_array(unsigned int size);

int *create_random_array(unsigned int size) {
    std::default_random_engine e1(r());
    int *arr = (int *) calloc(size, sizeof(int));

    for (int i = 0; i < size; i++) {
        std::uniform_int_distribution<int> uniform_dist(0, 1000);
        int mean = uniform_dist(e1);
        arr[i] = mean;
    }

    return arr;
}

static int *create_sorted_array(unsigned int size, sort_type type) {
    int *arr = create_random_array(size);

    if (type == sort_type::ASCENDING)
        std::sort(arr, arr + sizeof arr / sizeof arr[0], [](int a, int b) { return a < b; });
    else
        std::sort(arr, arr + sizeof arr / sizeof arr[0], [](int a, int b) { return a > b; });

    return arr;
}

static double measure_func_time_random(sort_func func, unsigned int size) {

    auto arr = create_random_array(size);

    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < 5; iter++) {
        func(arr, size);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    free(arr);

    return elapsed.count() / (double) 5;
}

static double measure_func_time_sorted(sort_func func, unsigned int size, sort_type dir) {

    auto arr = create_sorted_array(size, dir);

    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < 5; iter++) {
        func(arr, size);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    free(arr);

    return elapsed.count() / (double) 5;
}


static void print_array(int array[], unsigned int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


static void process_input(int argc, const char *argv[]) {
    if (argc < 2)
        return;

    if (strcmp(argv[2], "-r") == 0)
    {
        int *arr = create_random_array(atoi(argv[1]));
        printf("Old array\n\n\n");
        print_array(arr, atoi(argv[1]));
        radix_sort(arr, atoi(argv[1]));
        printf("New array\n");
        print_array(arr, atoi(argv[1]));
        free(arr);
    }
    else if(strcmp(argv[2], "-h") == 0) {


        int *arr = create_random_array(atoi(argv[1]));
        printf("Old array\n\n\n");
        print_array(arr, atoi(argv[1]));
        heap_sort(arr, atoi(argv[1]));
        printf("New array\n");
        print_array(arr, atoi(argv[1]));
        free(arr);
    }
    else if(strcmp(argv[2], "-b") == 0) {

        int *arr = create_random_array(atoi(argv[1]));
        printf("Old array\n\n\n");
        print_array(arr, atoi(argv[1]));
        heap_sort(arr, atoi(argv[1]));
        printf("New array\n");
        print_array(arr, atoi(argv[1]));
        free(arr);
    }

}


int main(const int argc, const char *argv[]) {

    auto dims = std::vector<int> {10, 51, 101, 1001, 10001, 100001};

    FILE *f = fopen("../times.txt", "a");

    for (auto size : dims) {


#ifdef BENCHMARK
        fprintf(f, "ASCENDING:\n");
        fprintf(f, "Radix sort for %d is %lf ns, heap sort for %d is %lf and bubble sort for %d is %lf\n",
               size, measure_func_time_sorted(radix_sort, size, sort_type::ASCENDING),
               size, measure_func_time_sorted(heap_sort, size, sort_type::ASCENDING),
               size, measure_func_time_sorted(bubble_sort, size, sort_type::ASCENDING));
        fprintf(f, "DESCENDING:\n");
        fprintf(f, "Radix sort for %d is %lf ns, heap sort for %d is %lf and bubble sort for %d is %lf\n",
               size, measure_func_time_sorted(radix_sort, size, sort_type::DESCENDING),
               size, measure_func_time_sorted(heap_sort, size, sort_type::DESCENDING),
               size, measure_func_time_sorted(bubble_sort, size, sort_type::DESCENDING));
#endif
    }

    fclose(f);

    return 0;
}
