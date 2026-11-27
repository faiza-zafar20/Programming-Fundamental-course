#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fft1D(float *real, float *imag, int N) {
    float *r = (float *)malloc(N * sizeof(float));
    float *im = (float *)malloc(N * sizeof(float));
    for (int k = 0; k < N; k++) {
        r[k] = 0;
        im[k] = 0;
        for (int n = 0; n < N; n++) {
            float angle = -2 * 3.14159265 * k * n / N;
            r[k] = r[k] + real[n] * cos(angle) - imag[n] * sin(angle);
            im[k] = im[k] + real[n] * sin(angle) + imag[n] * cos(angle);
        }
    }
    for (int i = 0; i < N; i++) {
        real[i] = r[i];
        imag[i] = im[i];
    }
    free(r);
    free(im);
}

void fft2D(float **real_sheet, float **imag_sheet, int N) {
    for (int i = 0; i < N; i++) {
        fft1D(real_sheet[i], imag_sheet[i], N);
    }
    float *tr = (float *)malloc(N * sizeof(float));
    float *ti = (float *)malloc(N * sizeof(float));
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            tr[i] = real_sheet[i][j];
            ti[i] = imag_sheet[i][j];
        }
        fft1D(tr, ti, N);
        for (int i = 0; i < N; i++) {
            real_sheet[i][j] = tr[i];
            imag_sheet[i][j] = ti[i];
        }
    }
    free(tr);
    free(ti);
}

int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);

    int total = N * N * N;

    float *real = (float *)malloc(total * sizeof(float));
    float *imag = (float *)malloc(total * sizeof(float));

    float ***real_sheets = (float ***)malloc(N * sizeof(float **));
    float ***imag_sheets = (float ***)malloc(N * sizeof(float **));
    for (int s = 0; s < N; s++) {
        real_sheets[s] = (float **)malloc(N * sizeof(float *));
        imag_sheets[s] = (float **)malloc(N * sizeof(float *));
        for (int i = 0; i < N; i++) {
            real_sheets[s][i] = &real[(s * N + i) * N];
            imag_sheets[s][i] = &imag[(s * N + i) * N];
        }
    }

    printf("Enter %d values:\n", total);
    for (int i = 0; i < total; i++) {
        scanf("%f", &real[i]);
        imag[i] = 0;
    }

    for (int z = 0; z < N; z++) {
        fft2D(real_sheets[z], imag_sheets[z], N);
    }

    float *t_real = (float *)malloc(total * sizeof(float));
    float *t_imag = (float *)malloc(total * sizeof(float));
    float ***t_real_sheets = (float ***)malloc(N * sizeof(float **));
    float ***t_imag_sheets = (float ***)malloc(N * sizeof(float **));
    for (int s = 0; s < N; s++) {
        t_real_sheets[s] = (float **)malloc(N * sizeof(float *));
        t_imag_sheets[s] = (float **)malloc(N * sizeof(float *));
        for (int i = 0; i < N; i++) {
            t_real_sheets[s][i] = &t_real[(s * N + i) * N];
            t_imag_sheets[s][i] = &t_imag[(s * N + i) * N];
        }
    }

    for (int z = 0; z < N; z++) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                int old_index = (x * N + y) * N + z;
                int new_index = (z * N + y) * N + x;
                t_real[new_index] = real[old_index];
                t_imag[new_index] = imag[old_index];
            }
        }
    }

    for (int z = 0; z < N; z++) {
        fft2D(t_real_sheets[z], t_imag_sheets[z], N);
    }

    printf("Magnitude slice at z = 0:\n");
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            int index = (0 * N + y) * N + x;
            float mag = sqrt(t_real[index] * t_real[index] + t_imag[index] * t_imag[index]);
            printf("%.2f ", mag);
        }
        printf("\n");
    }

    free(real);
    free(imag);
    free(t_real);
    free(t_imag);
    for (int s = 0; s < N; s++) {
        free(real_sheets[s]);
        free(imag_sheets[s]);
        free(t_real_sheets[s]);
        free(t_imag_sheets[s]);
    }
    free(real_sheets);
    free(imag_sheets);
    free(t_real_sheets);
    free(t_imag_sheets);

    return 0;
}