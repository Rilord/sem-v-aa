//
// Created by kodor on 10/21/21.
//

#include <cstdlib>
#include "test.h"
#include <algorithm>

static matrix * g_random_matrix;

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

static void extract_random_matrix(matrix *m) {

    MATRIX_ALLOC(m->mat, m->m, m->n, int)

    for (int i = 0; i < m->m; i++) {
        for (int j = 0; j < m->n; j++) {
            m->mat[i][j] = g_random_matrix->mat[i][j];
        }
    }
}

double get_elpased_function_time(matrix_mult_ptr mult, vec3 *dims, int iters) {

    matrix *A, *B, *C;

    MAKE_MATRIX(A, dims->x, dims->y, int)
    MAKE_MATRIX(B, dims->y, dims->z, int)
    MAKE_MATRIX(C, dims->x, dims->z, int)


    std::chrono::duration<double> elapsed;

    for (int i = 0; i < iters; i++) {
        auto start = std::chrono::steady_clock::now();
        mult(A, B, C);
        auto end = std::chrono::steady_clock::now();
        elapsed += end - start;
    }

    return elapsed.count();


}

static void make_random_matrix( matrix *A, const vec2 *dims, const vec2 *val_bound) {

    MAKE_MATRIX(g_random_matrix, dims->x, dims->y, int)

    std::srand(std::time(nullptr));

    for (int i = 0; i < dims->x; i++)
        for (int j = 0; j < dims->y; j++) {
            int val = std::rand();
            A->mat[i][j] = clip(val, val_bound->x, val_bound->y);
        }

}



int main(const int argc, const char *argv[]) {

    if (argc != 5)
        return -1;

    vec2 random_dims, random_val_bound;

    random_dims.x = atoi(argv[1]),
    random_dims.y = atoi(argv[2]),
    random_val_bound.x = atoi(argv[3]),
    random_val_bound.y = atoi(argv[4]);

    make_random_matrix(g_random_matrix, &random_dims, &random_val_bound);





    return 0;
}