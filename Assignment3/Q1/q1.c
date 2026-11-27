#include <stdio.h>
#include <stdlib.h>

int countNeighbours(int **grid, int N, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < N && c >= 0 && c < N) {
                count = count + grid[r][c];
            }
        }
    }
    return count;
}

int main() {
    int N, G;

    printf("Enter N: ");
    scanf("%d", &N);
    printf("Enter G: ");
    scanf("%d", &G);

    int **curr = (int **)malloc(N * sizeof(int *));
    int **next = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        curr[i] = (int *)malloc(N * sizeof(int));
        next[i] = (int *)malloc(N * sizeof(int));
    }

    printf("Enter grid %d x %d:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &curr[i][j]);
        }
    }

    for (int gen = 0; gen < G; gen++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int n = countNeighbours(curr, N, i, j);
                if (curr[i][j] == 1) {
                    if (n < 2)
                        next[i][j] = 0;
                    else if (n == 2 || n == 3)
                        next[i][j] = 1;
                    else
                        next[i][j] = 0;
                } else {
                    if (n == 3)
                        next[i][j] = 1;
                    else
                        next[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                curr[i][j] = next[i][j];
            }
        }
    }

    printf("Final Grid after %d generations:\n", G);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", curr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        free(curr[i]);
        free(next[i]);
    }
    free(curr);
    free(next);

    return 0;
}