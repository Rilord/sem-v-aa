//
// Created by kodor on 10/13/21.
//

//#include "levenstein.h"

#include <iostream>
#include <chrono>
#include <string>
#include "levenstein.h"

static char **test_strings;

static int32_t **dp;

static void print_helper() {
    printf("commands:\n"
           "arg 1 - first string, "
           "arg 2 - second string, "
           "arg 3 - edit distance algorithm\n"
           "algorithms:\n"
           "-r recursive\n"
           "-i iterative\n"
           "-c cached\n"
           "-d damerau-levenshtein\n");
}


static void process_input(int argc, const char *argv[]) {
    if (argc < 2)
        print_helper();

    if (strcmp(argv[3], "-r") == 0)
    {
        int distance = edit_distance(argv[2],
                                   strlen(argv[2]),
                                   argv[3],
                                   strlen(argv[3]));

        printf("result (with recursion): %d\n", distance);
    }
    else if(strcmp(argv[3], "-i") == 0) {

        auto res = iterative_levenshtein(argv[2],
                                            strlen(argv[2]),
                                            argv[3],
                                            strlen(argv[3]));

        printf("result (with iterative approach): %d\n", res->distance);
        print_matrix(res->mat);

    }
    else if(strcmp(argv[3], "-c") == 0) {

        int distance = cached_edit_distance(argv[2],
                                     strlen(argv[2]),
                                     argv[3],
                                     strlen(argv[3]));

        printf("result (with caching): %d\n", distance);
    }
    else if(strcmp(argv[3], "-d") == 0) {
    }

}


int main(const int argc, const char *argv[]) {

    process_input(argc, argv);

    return 0;
}
