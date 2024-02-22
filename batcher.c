#include "stats.h"

#include <math.h>

void comparator(Stats *stats, uint32_t *A, int x, int y) {
    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }

    int x = n;
    int t = 0;
    while (x != 0) {
        x >>= 1;
        t += 1;
    }

    int p = 1 << (t - 1);

    while (p > 0) {
        int q = 1 << (t - 1);
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
