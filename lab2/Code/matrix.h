//
// Created by kodor on 10/21/21.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H


#define CREATE_ARRAY(SIZE, TYPE) (TYPE *) malloc(SIZE * sizeof(TYPE))

#define MATRIX_ALLOC(pointer, M, N, type) \
    pointer = (type **) malloc(M * sizeof(type *)); \
    for (int i = 0; i < M; i++) \
        pointer[i] = (type *) malloc(N * sizeof(type));

#define MAKE_MATRIX(_m, M, N, type) \
    _m = (matrix *) malloc(sizeof(matrix));\
    _m->m = M, _m->n = N; \
    MATRIX_ALLOC(_m->mat, M, N, type)

typedef struct vec2 {
    int x, y;
};

typedef struct vec3 {
    int x, y, z;
};

typedef struct matrix {
    int **mat;
    int m, n;
};

void multiply_matrices(const matrix *, const matrix *, const matrix *, const int N);

int *precompute_rows(const matrix *A);

int *precompute_cols(const matrix *A);

int *precompute_rows_improved(const matrix *A);

int *precompute_cols_improved(const matrix *A);


#endif //LAB2_MATRIX_H
