#ifndef LM35_FILTER_H
#define LM35_FILTER_H
#define B0  9.25201134e-09
#define B1  1.85040227e-08
#define B2  9.25201134e-09
#define A1 -1.99972792
#define A2  0.99972796


typedef struct {
    double x1, x2;
    double y1, y2;
} Butter2State;

static void butter2_init(Butter2State* s) {
    s->x1 = s->x2 = s->y1 = s->y2 = 0.0;
}

static double butter2_apply(Butter2State* s, double x) {
    const double y = B0 * x + B1 * s->x1 + B2 * s->x2
        - A1 * s->y1 - A2 * s->y2;

    s->x2 = s->x1;
    s->x1 = x;
    s->y2 = s->y1;
    s->y1 = y;
    return y;
}
#endif
