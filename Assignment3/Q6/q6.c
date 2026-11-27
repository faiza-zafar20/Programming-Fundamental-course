#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long sum;
    int a;
    int b;
} Pair;

int cmp(const void *x, const void *y) {
    unsigned long long s1 = ((Pair *)x)->sum;
    unsigned long long s2 = ((Pair *)y)->sum;
    if (s1 < s2) return -1;
    if (s1 > s2) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N < 1) {
        printf("N must be >= 1\n");
        return 1;
    }

    int found = 0;
    int B = 20;
    unsigned long long *answers = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    int *a1 = (int *)malloc(N * sizeof(int));
    int *b1 = (int *)malloc(N * sizeof(int));
    int *a2 = (int *)malloc(N * sizeof(int));
    int *b2 = (int *)malloc(N * sizeof(int));

    while (1) {
        int totalPairs = B * (B + 1) / 2;
        Pair *pairs = (Pair *)malloc(totalPairs * sizeof(Pair));
        int idx = 0;
        for (int a = 1; a <= B; a++) {
            for (int b = a; b <= B; b++) {
                unsigned long long ca = (unsigned long long)a * a * a;
                unsigned long long cb = (unsigned long long)b * b * b;
                pairs[idx].sum = ca + cb;
                pairs[idx].a = a;
                pairs[idx].b = b;
                idx++;
            }
        }

        qsort(pairs, totalPairs, sizeof(Pair), cmp);

        found = 0;
        for (int i = 0; i < totalPairs - 1 && found < N; i++) {
            if (pairs[i].sum == pairs[i + 1].sum) {
                if (pairs[i].a == pairs[i + 1].a && pairs[i].b == pairs[i + 1].b) {
                    continue;
                }
                if (found > 0 && answers[found - 1] == pairs[i].sum) {
                    continue;
                }
                answers[found] = pairs[i].sum;
                a1[found] = pairs[i].a;
                b1[found] = pairs[i].b;
                a2[found] = pairs[i + 1].a;
                b2[found] = pairs[i + 1].b;
                found++;
            }
        }
        free(pairs);

        if (found >= N) {
            unsigned long long nextSum = 1 + (unsigned long long)(B + 1) * (B + 1) * (B + 1);
            if (answers[N - 1] < nextSum) {
                break;
            }
        }
        B = B + 20;
    }

    for (int i = 0; i < N; i++) {
        printf("%d. %llu = %d^3 + %d^3 = %d^3 + %d^3\n", i + 1, answers[i], a1[i], b1[i], a2[i], b2[i]);
    }

    free(answers);
    free(a1);
    free(b1);
    free(a2);
    free(b2);

    return 0;
}