#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int type;
    float x, y;
} Dot;

typedef struct {
    int type;
    float x1, y1, x2, y2;
} Line;

typedef struct {
    int type;
    float x1, y1, x2, y2, x3, y3;
} Triangle;

typedef struct {
    int type;
    float x, y, side;
} Square;

typedef struct {
    int type;
    float x, y, width, height;
} Rectangle;

float calculateProperty(void *shapePtr, int propertyType) {
    int type = *(int *)shapePtr;
    float result = 0;

    switch (type) {
        case 0: {
            Dot *d = (Dot *)shapePtr;
            if (propertyType == 0) result = 0;
            if (propertyType == 1) result = 0;
            if (propertyType == 2) result = sqrt(d->x * d->x + d->y * d->y);
            break;
        }
        case 1: {
            Line *l = (Line *)shapePtr;
            float dx = l->x2 - l->x1;
            float dy = l->y2 - l->y1;
            if (propertyType == 0) result = 0;
            if (propertyType == 1) result = sqrt(dx * dx + dy * dy);
            if (propertyType == 2) result = sqrt(l->x1 * l->x1 + l->y1 * l->y1);
            break;
        }
        case 2: {
            Triangle *t = (Triangle *)shapePtr;
            float s1 = sqrt((t->x2 - t->x1) * (t->x2 - t->x1) + (t->y2 - t->y1) * (t->y2 - t->y1));
            float s2 = sqrt((t->x3 - t->x2) * (t->x3 - t->x2) + (t->y3 - t->y2) * (t->y3 - t->y2));
            float s3 = sqrt((t->x1 - t->x3) * (t->x1 - t->x3) + (t->y1 - t->y3) * (t->y1 - t->y3));
            if (propertyType == 0) {
                float a = t->x1 * (t->y2 - t->y3) + t->x2 * (t->y3 - t->y1) + t->x3 * (t->y1 - t->y2);
                if (a < 0) a = -a;
                result = a / 2;
            }
            if (propertyType == 1) result = s1 + s2 + s3;
            if (propertyType == 2) {
                float cx = (t->x1 + t->x2 + t->x3) / 3;
                float cy = (t->y1 + t->y2 + t->y3) / 3;
                result = sqrt(cx * cx + cy * cy);
            }
            break;
        }
        case 3: {
            Square *s = (Square *)shapePtr;
            if (propertyType == 0) result = s->side * s->side;
            if (propertyType == 1) result = 4 * s->side;
            if (propertyType == 2) result = sqrt(s->x * s->x + s->y * s->y);
            break;
        }
        case 4: {
            Rectangle *r = (Rectangle *)shapePtr;
            if (propertyType == 0) result = r->width * r->height;
            if (propertyType == 1) result = 2 * (r->width + r->height);
            if (propertyType == 2) result = sqrt(r->x * r->x + r->y * r->y);
            break;
        }
    }
    return result;
}

int main() {
    int n;
    printf("How many shapes: ");
    scanf("%d", &n);

    void **shapes = (void **)malloc(n * sizeof(void *));

    for (int i = 0; i < n; i++) {
        int type;
        printf("Enter type for shape %d (0=Dot 1=Line 2=Triangle 3=Square 4=Rectangle): ", i + 1);
        scanf("%d", &type);

        if (type == 0) {
            Dot *d = (Dot *)malloc(sizeof(Dot));
            d->type = 0;
            printf("Enter x y: ");
            scanf("%f %f", &d->x, &d->y);
            shapes[i] = d;
        } else if (type == 1) {
            Line *l = (Line *)malloc(sizeof(Line));
            l->type = 1;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%f %f %f %f", &l->x1, &l->y1, &l->x2, &l->y2);
            shapes[i] = l;
        } else if (type == 2) {
            Triangle *t = (Triangle *)malloc(sizeof(Triangle));
            t->type = 2;
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%f %f %f %f %f %f", &t->x1, &t->y1, &t->x2, &t->y2, &t->x3, &t->y3);
            shapes[i] = t;
        } else if (type == 3) {
            Square *s = (Square *)malloc(sizeof(Square));
            s->type = 3;
            printf("Enter x y side: ");
            scanf("%f %f %f", &s->x, &s->y, &s->side);
            shapes[i] = s;
        } else if (type == 4) {
            Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));
            r->type = 4;
            printf("Enter x y width height: ");
            scanf("%f %f %f %f", &r->x, &r->y, &r->width, &r->height);
            shapes[i] = r;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Shape %d: Area = %.2f, Perimeter/Length = %.2f, Distance = %.2f\n", i + 1,
            calculateProperty(shapes[i], 0),
            calculateProperty(shapes[i], 1),
            calculateProperty(shapes[i], 2));
    }

    for (int i = 0; i < n; i++) {
        free(shapes[i]);
    }
    free(shapes);

    return 0;
}