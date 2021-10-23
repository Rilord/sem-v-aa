//
// Created by kodor on 10/13/21.
//

#include "levenstein.h"
#include <benchmark/benchmark.h>

#include <iostream>
#include <chrono>
#include <string>


static char **test_strings;

static int32_t **dp;


void create_test_strings() {
    test_strings = (char **) malloc(sizeof(char *) * 200);
    for (auto i = 0; i < 200; i++) {
        test_strings[i] = (char *) calloc(200, sizeof(char));
        auto tmp = std::string(i, '*');
        strcpy(test_strings[i], tmp.c_str());
    }

}



static void init_dp() {

    dp = (int32_t **) malloc(10 * sizeof(int32_t *));
    for (auto i = 0 ; i < 10; i++) {
        dp[i] = (int32_t *) calloc(10, sizeof(int32_t));
    }
}

int main(const int argc, const char *argv[]) {
    init_dp();

    create_test_strings();



    return 0;
}
