//
// Created by kodor on 10/23/21.
//

#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <cstdint>
#include <pprint.hpp>

typedef struct {
    int32_t **mat, m, n;
} matrix;

typedef struct {
   int32_t *arr, len;
} array;


std::ostream &operator<<(std::ostream &os, const matrix &mat);

#define MATRIX(pointer, M, N, type) \
    pointer = (matrix *) malloc(sizeof(matrix));\
    pointer->m = M, pointer->n = N;\
    pointer->mat = (type **) calloc(M, sizeof(type *));\
    for (int i = 0; i < M; i++)\
        pointer->mat[i] = (type *) calloc(N, sizeof(type))\

#endif //LAB1_MATRIX_H
