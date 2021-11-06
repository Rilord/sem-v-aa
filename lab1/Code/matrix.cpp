//
// Created by kodor on 10/23/21.
//

#include "matrix.h"
#include <stdio.h>

void print_matrix(const matrix *mat) {
   printf("Matrix:\n");
   for (int i = 0; i < mat->m; i++) {
       for (int j = 0; j < mat->n; j++)
           printf("%d ", mat->mat[i][j]);
       printf("\n");
   }
}