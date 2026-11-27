#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void drawLine(char **grid, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int sx = 1;
    if (x0 > x1) sx = -1;
    int dy = -abs(y1 - y0);
    int sy = 1;
    if (y0 > y1) sy = -1;
    int err = dx + dy;

    while (1) {
        grid[y0][x0] = '*';
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int main() {
    int N;
    printf("Enter N (odd): ");
    scanf("%d", &N);

    int R = 2 * N;
    int W = 2 * R + 1;
    int H = 2 * R + 1;
    int cx = R;
    int cy = R;

    char **grid = (char **)malloc(H * sizeof(char *));
    for (int i = 0; i < H; i++) {
        grid[i] = (char *)malloc(W * sizeof(char));
        for (int j = 0; j < W; j++) {
            grid[i][j] = ' ';
        }
    }

    int px[10], py[10];
    for (int k = 0; k < 5; k++) {
        double outerAngle = (-90 + k * 72) * 3.14159265 / 180.0;
        px[2 * k] = (int)(cx + R * cos(outerAngle) + 0.5);
        py[2 * k] = (int)(cy + R * sin(outerAngle) + 0.5);

        double innerAngle = (-90 + 36 + k * 72) * 3.14159265 / 180.0;
        double r = R * 0.38;
        px[2 * k + 1] = (int)(cx + r * cos(innerAngle) + 0.5);
        py[2 * k + 1] = (int)(cy + r * sin(innerAngle) + 0.5);
    }

    for (int i = 0; i < 10; i++) {
        int next = (i + 1) % 10;
        drawLine(grid, px[i], py[i], px[next], py[next]);
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < H; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}