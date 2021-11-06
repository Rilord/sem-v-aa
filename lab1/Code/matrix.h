//
// Created by kodor on 10/23/21.
//

#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <cstdint>

typedef struct {
    int32_t **mat, m, n;
} matrix;

typedef struct {
   int32_t *arr, len;
} array;



#define MATRIX(pointer, M, N, type) \
    pointer = (matrix *) malloc(sizeof(matrix));\
    pointer->m = M, pointer->n = N;\
    pointer->mat = (type **) calloc(M, sizeof(type *));\
    for (int i = 0; i < M; i++)\
        pointer->mat[i] = (type *) calloc(N, sizeof(type))\


void print_matrix(const matrix *mat);

#endif //LAB1_MATRIX_H
