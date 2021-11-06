//
// Created by kodor on 10/13/21.
//

#include "levenstein.h"

#include <stdio.h>

#include "matrix.h"

#define BENCHMARK

#define d(i,j) dd[(i) * (lt+2) + (j) ]
#define min(x,y) ((x) < (y) ? (x) : (y))
#define min3(a,b,c) ((a)< (b) ? min((a),(c)) : min((b),(c)))
#define min4(a,b,c,d) ((a)< (b) ? min3((a),(c),(d)) : min3((b),(c),(d)))



int edit_distance(const char *s, int ls, const char *t, int lt) {
    int a, b, c;

    if (!ls) return lt;
    if (!lt) return ls;

    if (s[ls - 1] == t[lt - 1])
        return edit_distance(s, ls - 1, t, lt - 1);

    return 1
           + min3(edit_distance(s, ls ,t, lt - 1),
                  edit_distance(s, ls ,t - 1, lt), // Remove
                  edit_distance(s, ls - 1 ,t, lt - 1) // Replace
           );
}

int memoized_edit_distance(const char *s, int ls, const char *t, int lt, matrix *dp) {

    if (!ls) return lt;
    if (!lt) return ls;

    if (dp->mat[ls - 1][lt - 1] != -1) return dp->mat[ls - 1][lt - 1];

    if (s[ls - 1] == t[lt - 1])
        return dp->mat[ls - 1][lt - 1] = memoized_edit_distance(s, ls - 1, t, lt - 1, dp);

    return dp->mat[ls - 1][lt - 1] = 1 + min3(memoized_edit_distance(s, ls - 1, t, lt - 1, dp),
                                              memoized_edit_distance(s, ls, t, lt - 1, dp),
                                              memoized_edit_distance(s, ls - 1, t, lt - 1, dp));
}

result *iterative_levenshtein(const char *s, int32_t ls, const char *t, int32_t lt) {
    int x, y;

    matrix *mat;
    result *res = (result *) malloc(sizeof(res));
    MATRIX(mat, lt + 1, ls + 1, int32_t);

    mat->mat[0][0] = 0;

    for (x = 1; x <= lt; x++)
        mat->mat[x][0] = mat->mat[x - 1][0] + 1;
    for (y = 1; y <= ls; y++)
        mat->mat[0][y] = mat->mat[0][y - 1] + 1;
    for (x = 1; x <= lt; x++)
        for (y = 1; y <= ls; y++)
            mat->mat[x][y] = min3(
                    mat->mat[x - 1][y] + 1,
                    mat->mat[x][y - 1] + 1,
                    mat->mat[x - 1][y - 1] + (s[y - 1] == t[x - 1] ? 0 : 1)
            );

    res->mat = mat, res->distance = mat->mat[lt][ls];

    return res;
}

int damerau_levenstein(const char *s, int ls, const char *t, int lt) {
    int32_t *dd;
    int32_t i, j, cost, i1, j1, DB;
    int32_t INF = ls + lt;
    int32_t DA[256 * sizeof(int32_t)];

    memset(DA, 0, sizeof(DA));

    if (!(dd = (int32_t *) malloc((ls + 2) * (lt + 2) * sizeof(int32_t)))) {
        return -1;
    }

    d(0,0) = INF;

    for (i = 0; i < ls + 1; i++) {
        d(i + 1, 1) = i;
        d(i + 1, 0) = INF;
    }

    for (j = 0; j < lt + 1; j++) {
        d(1, j + 1) = j;
        d(0, j + 1) = INF;
    }

    for(i = 1; i < ls + 1; i++) {
        DB = 0;
        for(j = 1; j < lt + 1; j++) {
            i1 = DA[t[j - 1]];
            j1 = DB;
            cost = ((s[i - 1] == t[j - 1])? 0 : 1);
            if(cost == 0) DB = j;
            d(i + 1,j + 1) =
                    min4(d(i,j)+cost,
                         d(i + 1,j) + 1,
                         d(i,j + 1) + 1,
                         d(i1, j1) + (i - i1 - 1) + 1 + (j - j1 - 1));
        }
        DA[s[i-1]] = i;
    }
    cost = d(ls+1,lt+1);
    free(dd);
    return cost;
}

static int dist(int i, int j, matrix *d,
                const char *s, const char *t,
                int ls, int lt) {

    if (d->mat[i][j] >= 0) return d->mat[i][j];

    int x;
    if (i == ls)
        x = lt - j;
    else if(j == lt)
        x = ls - i;
    else if(s[i] == t[j])
        x = dist(i + 1, j + 1, d, s, t, ls, lt);
    else {
        x = dist(i + 1, j + 1, d, s, t, ls, lt);

        int y;
        if ((y = dist(i, j + 1, d, s, t, ls, lt)) < x) x = y;
        if ((y = dist(i + 1, j, d, s, t, ls, lt)) < x) x = y;
        x++;
    }

#ifdef BENCHMARK
    print_matrix(d);
#endif

    return d->mat[i][j] = x;

}

int cached_edit_distance(const char *s, int ls, const char *t, int lt) {

    matrix *d;

    MATRIX(d, ls + 1, lt + 1, int32_t);



    for (int i = 0; i <= ls; i++)
        for (int j = 0; j <= lt; j++)
            d->mat[i][j] = -1;


    return dist(0,0, d, s, t, ls, lt);
}
