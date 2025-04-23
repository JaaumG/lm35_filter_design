#include <math.h>
#include "lm35_filter.h"
#include <stdio.h>

double adquirirAmostra(int i) {
    FILE* fp = fopen("../data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    char line[256];
    double first_column, second_column;

    for (int j = 0; j < i; j++) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            printf("Error reading line %d\n", i);
            fclose(fp);
            return -1;
        }
    }

    if (sscanf(line, "%lf %lf", &first_column, &second_column) != 2) {
        printf("Error parsing line\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return second_column;
}

int main(void) {
    Butter2State filt;
    butter2_init(&filt);

    for (int i = 0; i < 100; ++i) {
        const double raw = adquirirAmostra(1);
        const double clean = butter2_apply(&filt, raw);
        printf("%.32f\n", clean);
    }
    return 0;
}
