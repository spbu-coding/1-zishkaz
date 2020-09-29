#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LENGTH 25
#define array_length(x) (sizeof(x) / sizeof(x[0]))

struct interval_t {

    double border_left;
    double border_right;
};

size_t size;

double calc_rectangulars(int, double, double);

double calc_simpson(int, double, double);

char  **calc_final (const int *, struct interval_t);

int main() {

    struct interval_t interval = {0.0, 0.0};
    printf("%s\n", "Input left and right border:");
    scanf("%lf%lf", &interval.border_left, &interval.border_right);
    while(!(interval.border_left >= 0 && interval.border_right <= M_PI && interval.border_left < interval.border_right)) {
        printf("%s\n", "Input interval is incorrect! Retry:");
        scanf("%lf%lf", &interval.border_left, &interval.border_right);
    }
    int experiments[] = {5,  10,  20,  100,  500,  1000};
    size = array_length(experiments);
    char **results = calc_final(experiments, interval);
    for(int i = 0;i < size;i++) {
        if(!printf("%s\n", results[i])) {
            printf("%s\n", "Unable to output line №%d", i);
        }
    }

    return 0;
}

double calc_rectangulars(int step, double left_border, double right_border) {

    double res=0;
    double del = (double) (right_border - left_border) / (double) step;
    double left = left_border;
    double right = left + del;
    for (int j = 0;j < step;j++) {

        res += sin((left + right) / 2) * del;
        left = right;
        right += del;
    }
    return res;
}

double calc_simpson(int step, double left_border, double right_border) {

    double res = 0;
    double del = (double) (right_border - left_border) / (double) step;
    double left = left_border;
    double right = left + del;
    for(int j = 0;j < step;j++) {

        res +=(right - left) / 6 * (sin(left) + 4 * sin((left + right) / 2) + sin(right));
        left = right;
        right += del;
    }
    return res;
}

char  **calc_final (const int *base, struct interval_t interval) {

    char **results = (char **) malloc(sizeof(char *) * size);
    for(int i = 0;i < size;i++) {

        results[i] = (char *)malloc(sizeof(char) * MAX_LENGTH);
        double sq = calc_rectangulars(base[i], interval.border_left, interval.border_right);
        double simpson = calc_simpson(base[i], interval.border_left, interval.border_right);
        if(!sprintf(results[i], "%d %.5f %.5f", base[i], sq, simpson)) {

            printf("%s\n", "Unable to save results of experiment №%d", i);
        }
    }

    return results;
}
