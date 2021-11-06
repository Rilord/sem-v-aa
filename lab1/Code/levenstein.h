//
// Created by kodor on 10/13/21.
//

#ifndef CODE_LEVENSTEIN_H
#define CODE_LEVENSTEIN_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct {
    int distance;
    matrix *mat;
} result;


int edit_distance(const char *s, int ls, const char *t, int lt);

int memoized_edit_distance(const char *s, int ls, const char *t, int lt, int32_t **dp);

result *iterative_levenshtein(const char *s, int ls, const char *t, int lt);

int damerau_levenstein(const char *s, int ls, const char *t, int lt);


int cached_edit_distance(const char *s, int ls, const char *t, int lt);

#endif //CODE_LEVENSTEIN_H
