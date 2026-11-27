#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int type;
    double x;
    double y;
} Dot;

typedef struct {
    int type;
    double x1;
    double y1;
    double x2;
    double y2;
} Line;

float calculateProperty(void *shapePtr, int propertyType) {
    int type = *(int *)shapePtr;
    float result = 0;
    if (type == 0) {
        Dot *d = (Dot *)shapePtr;
        if (propertyType == 2) result = sqrt(d->x * d->x + d->y * d->y);
    }
    if (type == 1) {
        Line *l = (Line *)shapePtr;
        double dx = l->x2 - l->x1;
        double dy = l->y2 - l->y1;
        if (propertyType == 1) result = sqrt(dx * dx + dy * dy);
        if (propertyType == 2) result = sqrt(l->x1 * l->x1 + l->y1 * l->y1);
    }
    return result;
}

int cmpDot(const void *a, const void *b) {
    Dot *p1 = (Dot *)a;
    Dot *p2 = (Dot *)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

double cross(Dot a, Dot b, Dot c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Line *computeConvexHull(const Dot *points, int n, int *hullEdgeCount) {
    Dot *sorted = (Dot *)malloc(n * sizeof(Dot));
    for (int i = 0; i < n; i++) {
        sorted[i] = points[i];
    }
    qsort(sorted, n, sizeof(Dot), cmpDot);

    Dot *hull = (Dot *)malloc(2 * n * sizeof(Dot));
    int h = 0;

    for (int i = 0; i < n; i++) {
        while (h >= 2 && cross(hull[h - 2], hull[h - 1], sorted[i]) <= 0) {
            h--;
        }
        hull[h] = sorted[i];
        h++;
    }

    int lower = h;
    for (int i = n - 2; i >= 0; i--) {
        while (h > lower && cross(hull[h - 2], hull[h - 1], sorted[i]) <= 0) {
            h--;
        }
        hull[h] = sorted[i];
        h++;
    }

    h--;
    *hullEdgeCount = h;

    Line *edges = (Line *)malloc(h * sizeof(Line));
    for (int i = 0; i < h; i++) {
        int next = (i + 1) % h;
        edges[i].type = 1;
        edges[i].x1 = hull[i].x;
        edges[i].y1 = hull[i].y;
        edges[i].x2 = hull[next].x;
        edges[i].y2 = hull[next].y;
    }

    free(sorted);
    free(hull);
    return edges;
}

int main() {
    FILE *f = fopen("points.txt", "r");
    if (f == NULL) {
        printf("points.txt not found\n");
        return 1;
    }

    int n;
    fscanf(f, "%d", &n);

    Dot *points = (Dot *)malloc(n * sizeof(Dot));
    for (int i = 0; i < n; i++) {
        points[i].type = 0;
        fscanf(f, "%lf,%lf", &points[i].x, &points[i].y);
    }
    fclose(f);

    int edgeCount = 0;
    Line *edges = computeConvexHull(points, n, &edgeCount);

    float total = 0;
    for (int i = 0; i < edgeCount; i++) {
        float len = calculateProperty(&edges[i], 1);
        total = total + len;
        printf("Edge %d: (%.4f, %.4f) -> (%.4f, %.4f), Length = %.4f\n",
            i + 1, edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2, len);
    }
    printf("Total Perimeter = %.4f\n", total);

    free(points);
    free(edges);
    return 0;
}