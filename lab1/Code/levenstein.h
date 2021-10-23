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


int edit_distance(char *s, uint32_t ls, char *t, uint32_t lt);

int memoized_edit_distance(char *s, uint32_t ls, char *t, uint32_t lt, int32_t **dp);

result *iterative_levenshtein(char *s, uint32_t ls, char *t, uint32_t lt);

int damerau_levenstein(char *s, uint32_t ls, char *t, uint32_t lt);


int cached_edit_distance(char *s, uint32_t ls, char *t, uint32_t lt);

#endif //CODE_LEVENSTEIN_H
