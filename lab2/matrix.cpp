//
// Created by kodor on 10/21/21.
//

#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>



void multiply_matrices(const matrix *A, const matrix *B, const matrix *C, const int N) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < B->n; j++) {
            for (int p = 0; p < A->n; p++)
                C->mat[i][j] += A->mat[i][p] * B->mat[p][j];
        }
    }
}



void winograd(const matrix *A, const matrix *B, const matrix *C) {
    int m = A->m, n = B->n, q = B->m;

    auto pre_A = precompute_rows(A), pre_B = precompute_cols(B);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C->mat[i][j] = -(pre_A[i] + pre_B[j]);
            for (int k = 0; k < q / 2; k++) {
                C->mat[i][j] =
                        C->mat[i][j] +
                        (A->mat[i][k * 2] + B->mat[k * 2 + 1][j]) *
                        (A->mat[i][k * 2 + 1] + B->mat[k * 2][j]);
            }
        }
    }
    if (q % 2 != 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                C->mat[i][j] = C->mat[i][j] = C->mat[i][j] +
                        A->mat[i][q - 1] * B->mat[q - 1][j];
            }
        }
    }


}

int *precompute_rows(const matrix *A) {
    auto res = CREATE_ARRAY(A->m, int);

    for (int i = 0; i < A->m; i++)
        for (int j = 0; j < A->n / 2; j++)
            res[i] = res[i] + A->mat[i][j * 2] * A->mat[i][j * 2 + 1];

    return res;
}

int *precompute_cols(const matrix *A) {
    auto res = CREATE_ARRAY(A->n, int);

    for (int i = 0; i < A->n; i++)
        for (int j = 0; j < A->m / 2; j++)
            res[i] = res[i] + A->mat[j * 2][i] * A->mat[j * 2 + 1][i];


    return res;
}

void improved_winograd(const matrix *A, const matrix *B, const matrix *C) {
    int m = A->m, n = B->n, q = B->m;

    auto pre_A = precompute_rows_improved(A),
         pre_B = precompute_cols_improved(B);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            auto temp = (-pre_A[i] + pre_B[j]);
            for (int k = 0; k < q; k += 2) {
                temp += (A->mat[i][k - 1] + B->mat[k][j]) *
                        (A->mat[i][k] + B->mat[k - 1][j]);
            }
            C->mat[i][j] = temp;
        }

    if (q & 1 != 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                C->mat[i][j] += A->mat[i][q - 1] * B->mat[q - 1][j];
            }
        }
    }
}

int *precompute_rows_improved(const matrix *A) {
    auto res = CREATE_ARRAY(A->m, int);

    for (int i = 0; i < A->m; i++)
        for (int j = 0; j < A->n; j++)
            res[i] += A->mat[i][j - 1] * A->mat[i][j];

    return res;
}
int *precompute_cols_improved(const matrix *A) {
    auto res = CREATE_ARRAY(A->n, int);

    for (int i = 0; i < A->n; i++)
        for (int j = 0; j < A->m; j++)
            res[i] += A->mat[j - 1][i] * A->mat[j][i];

    return res;
}

