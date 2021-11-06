//
// Created by kodor on 10/21/21.
//

#ifndef LAB2_TEST_H
#define LAB2_TEST_H

#include "matrix.h"
#include <chrono>


typedef void *matrix_mult_ptr(const matrix *, const matrix *, const matrix *);

double get_elpased_function_time(matrix_mult_ptr mult, vec3 *dims, int iters);


#endif //LAB2_TEST_H
