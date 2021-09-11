#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define FEATURES 3

struct Weights {
    int w0;
    double w1;
    double w2;
};

struct Features {
    double x1;
    double x2;
};

void generatePlot(struct Features *f1, struct Features *f2, struct Weights *ws, uint8_t stage) {
    FILE *fp;
    uint8_t i;

    char filenameBase[] = "plot";
    char datExt[] = ".dat";
    char pExt[] = ".p";
    char _stage[2];
    char datFilename[30];
    char pFilename[30];

    sprintf(_stage, "%u", stage);

    strcpy(datFilename, filenameBase);
    strcat(datFilename, _stage);
    strcat(datFilename, datExt);

    strcpy(pFilename, filenameBase);
    strcat(pFilename, _stage);
    strcat(pFilename, pExt);

    fp = fopen(datFilename, "w+");
    fprintf(fp, "# A's\n");
    for (i = 0; i < FEATURES; i++) {
        fprintf(fp, "%f %f As[%d]\n", f1[i].x1, f1[i].x2, i);
    }
    fprintf(fp, "\n\n");
    fprintf(fp, "# B's\n");
    for (i = 0; i < FEATURES; i++) {
        fprintf(fp, "%f %f Bs[%d]\n", f2[i].x1, f2[i].x2, i);
    }
    fclose(fp);

    fp = fopen(pFilename, "w+");
    fprintf(fp, "m = %f\n", -1*ws->w1/ws->w2);
    fprintf(fp, "b = %f\n", -1*ws->w0/ws->w2);
    fprintf(fp, "f(x) = m * x + b\n");
    fprintf(fp, "plot f(x) with lines, '%s' index 0 with points ls 1, '' index 0 with labels offset char 1,1, '%s' index 1 with points ls 3, '' index 1 with labels offset char 1,1\n", datFilename, datFilename);
    fprintf(fp, "pause -1 \"Hit any key to continue\"\n");
    fclose(fp);
}

int check(struct Features *f, struct Weights *ws, uint8_t above) {
    double m = -1*ws->w1/ws->w2;
    double b = -1*ws->w0/ws->w2;
    int result = 0;

    if (f->x2 > (m*f->x1 + b)) {
        // it's above
        // should it be?
        if (!above) {
            result = -1;
        }
    } else {
        // it's below
        // should it be?
        if (above) {
            result = 1;
        }
    }

    return result;
}

void correct(struct Features *f, struct Weights *ws, int d, double rate) {
    ws->w0 = ws->w0 + rate*d;
    ws->w1 = ws->w1 + rate*d*f->x1;
    ws->w2 = ws->w2 + rate*d*f->x2;
}


int main () {
    //printf("HELLO!\n");

    struct Weights ws;
    double learningRate = 0.1;
    uint8_t i;
    uint16_t j;
    uint8_t stop = 0;
    int d;

    ws.w0 = 1;
    ws.w1 = 0.5;
    ws.w2 = -0.5;

    struct Features As[FEATURES];
    struct Features Bs[FEATURES];

    As[0].x1 = 1.45;
    As[0].x2 = 3.67;
    As[1].x1 = 1.98;
    As[1].x2 = 1.52;
    As[2].x1 = 4.70;
    As[2].x2 = 0.71;

    Bs[0].x1 = -1.21;
    Bs[0].x2 = 1.11;
    Bs[1].x1 = -2.20;
    Bs[1].x2 = -1.58;
    Bs[2].x1 = 0.55;
    Bs[2].x2 = -1.76;

    // generatePlot(As, Bs, &ws, 0);

    while (stop != 1) {
        stop = 1;
    // for (j = 0; j < 10; j++) {
        for (i = 0; i < FEATURES; i++) {
            d = check(&As[i], &ws, 1);
            //printf("A[%u] with d = %d\n", i, d);
            if (d != 0) {
                stop = 0;
                correct(&As[i], &ws, d, learningRate);
            }
            d = check(&Bs[i], &ws, 0);
            //printf("B[%u] with d = %d\n", i, d);
            if (d != 0) {
                stop = 0;
                correct(&Bs[i], &ws, d, learningRate);
            }
        }
    }

    // generatePlot(As, Bs, &ws, 1);

    return 0;
}
