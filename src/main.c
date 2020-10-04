#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LENGTH_OF_RESULT 25
#define array_length(x) (sizeof(x) / sizeof(x[0]))

struct interval_t {

    double border_left;
    double border_right;
};


void free_results(char **results, int count) {

    for (int i = 0; i < count; ++i) {
        free(results[i]);
    }
    free(results);
}

double calc_rectangulars(int step, double left_border, double right_border) {

    double res = 0;
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

        res += (right - left) / 6 * (sin(left) + 4 * sin((left + right) / 2) + sin(right));
        left = right;
        right += del;
    }
    return res;
}

char  **calc_final (const int *base, int count, struct interval_t interval) {

    char **results = (char **) malloc(sizeof(char *) * count);
    if(!results) {

        printf("%s\n", "Unable to allocate memory");
        return NULL;
    }
    for(int i = 0;i < count;i++) {

        results[i] = (char *)malloc(sizeof(char) * MAX_LENGTH_OF_RESULT);
        if(!results[i]) {

            printf("%s\n", "Unable to allocate memory");
            return NULL;
        }
        double sq = calc_rectangulars(base[i], interval.border_left, interval.border_right);
        double simpson = calc_simpson(base[i], interval.border_left, interval.border_right);
        if(!sprintf(results[i], "%d %.5f %.5f", base[i], sq, simpson)) {

            free_results(results, count);
            printf("%s\n", "Unable to save results of experiment №%d", i);
            return NULL;
        }
    }
    return results;
}


int main() {

    struct interval_t interval = {0.0, 0.0};
    printf("%s\n", "Input left and right border:");
    scanf("%lf%lf", &interval.border_left, &interval.border_right);
    while(!(interval.border_left >= 0 && interval.border_right <= M_PI && interval.border_left < interval.border_right)) {

        printf("%s\n", "Input interval is incorrect! Retry:");
        scanf("%lf %lf", &interval.border_left, &interval.border_right);
    }
    int experiments[] = {6,  10,  20,  100,  500,  1000};
    int count = array_length(experiments);
    char **results = calc_final(experiments, count, interval);
    if(!results) {

        printf("%s\n", "Fatal error occurred, restart the program");
        free_results(results, count);
        return -1;
    }
    for(int i = 0;i < count;i++) {

        if(!printf("%s\n", results[i])) {
            printf("%s\n", "Unable to output line №%d", i);
        }
    }
    free_results(results, count);
    return 0;
}
