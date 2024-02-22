#include "gaps.h"
#include "stats.h"

#include <math.h>

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (int i = 0; i < GAPS; i++) {
        for (int j = gaps[i]; j < length; j++) {
            int k = move(stats, j);
            int temp = move(stats, arr[j]);
            while (k >= gaps[i] && cmp(stats, temp, arr[k - gaps[i]]) == -1) {
                arr[k] = arr[k - gaps[i]];
                k -= move(stats, gaps[i]);
            }
            arr[k] = temp;
        }
    }
}
