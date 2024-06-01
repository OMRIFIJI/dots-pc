#include <stdlib.h>
#include <stdio.h>


double f(double x){
    return x * x * x;
}


double f_der(double x){
    return 3 * x * x;
}


double divided_difference(double y2, double y1, double x2, double x1){
    return (y2 - y1) / (x2 - x1);
}


void make_first_layer(double *f_values, double *f_der_values, double *interp_knots, 
    int interp_knots_count){
    f_values[1] = f_der_values[0]; 
    for(int i = 1; i < interp_knots_count; i++){
        f_values[2 * i] = divided_difference(
            f(interp_knots[i]),
            f(interp_knots[i-1]),
            interp_knots[i],
            interp_knots[i-1]
        ); 
        f_values[2 * i + 1] = f_der_values[i]; 
    }
}


void all_differences(double *f_values, double *f_der_values, double *interp_knots, 
    int interp_knots_count){
    for(int i = 2; i < 2 * interp_knots_count; i++)
        for(int j = i + 1; j < 2 * interp_knots_count; j++){
            f_values[j] = divided_difference(
                f_values[j],
                f_values[j-1],
                interp_knots[(j / 2)],
                interp_knots[(j / 2) - 1]
            ); 
        }

}



double interp_in_point(double point_to_interp, double *f_values, double *interp_knots, 
    int interp_knots_count)){
    double interp_value = 0;
    double polynomial;
    for (int i = 1; i < 2 * interp_knots; i++)
         polynomial = 1;
        for(int j = 0; j < i; j++){
            polynomial
        }
}
// 4 аргумента:
// Количество узлов интерполяции,
// 2 значения: границы отрезка, 
// файл с точками, в которых надо интерполировать, первое значение - число точек.
int main(int argc, char **argv){
    int interp_knots_count, points_to_interp_count;
    double a, b;
    double interval_len;
    double *points_to_interp, *interp_knots;
    double *f_values, *f_der_values;
    char *filename;
    FILE *file;

    // Input...
    if (argc != 5){
        fprintf(stderr, "Wrong argc\n");
        exit(EXIT_FAILURE);
    }
    
    if (
        (sscanf(argv[1], "%d", &interp_knots_count) != 1) || 
        (sscanf(argv[2], "%lf", &a) != 1) ||
        (sscanf(argv[3], "%lf", &b) != 1)
    ){
        fprintf(stderr, "Wrong input\n");
        exit(EXIT_FAILURE);
    }

    filename = argv[4];
    file = fopen(filename, "r");
    if (!file){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    if(fscanf(file, "%d", &points_to_interp_count) != 1){
        fprintf(stderr, "File err\n");
        exit(EXIT_FAILURE);
    }
    
    points_to_interp = (double *) malloc(sizeof(double) * points_to_interp_count);
    for(int i = 0; i < points_to_interp_count; i++)
        if(fscanf(file, "%lf", &points_to_interp[i]) != 1){
            fprintf(stderr, "File err\n");
            free(points_to_interp);
            exit(EXIT_FAILURE);
        }
    fclose(file); 
    // Проверка ввода 
    printf("Input:\n");
    printf("%d (%lf, %lf) %s %d\n", interp_knots_count, a, b, filename, points_to_interp_count);

    printf("Points to interpolate:\n");
    for(int i = 0; i < points_to_interp_count; i++)
        printf("%lf\n", points_to_interp[i]);

    // Задаём узлы интерполяции равномерно
    interp_knots = (double *) malloc(sizeof(double) * interp_knots_count);
    interval_len = (b - a) / (interp_knots_count - 1);
    
    for(int i = 0; i < interp_knots_count; i++){
        interp_knots[i] = a + interval_len * i;
    }

    // Проверка узлов
    printf("Knots:\n");
    for(int i = 0; i < interp_knots_count; i++)
        printf("%lf\n", interp_knots[i]);

    // Вычисление функции и производных в узлах
    f_values = (double *) malloc(2 * sizeof(double) * interp_knots_count);
    f_der_values = (double *) malloc(sizeof(double) * interp_knots_count);
    
    for(int i = 0; i < interp_knots_count; i++){
        f_values[2 * i] = f(interp_knots[i]);
        f_values[2 * i + 1] = f(interp_knots[i]);
        f_der_values[i] = f_der(interp_knots[i]);
    }
    
    printf("Values in knots:\n");
    for(int i = 0; i < interp_knots_count; i++){
        printf("%lf\n", f_values[2 * i]);
        printf("%lf\n", f_values[2 * i + 1]);
    }

    make_first_layer(f_values, f_der_values, interp_knots, interp_knots_count);

    printf("First layer:\n");
    for(int i = 0; i < interp_knots_count; i++){
        printf("%lf\n", f_values[2 * i]);
        printf("%lf\n", f_values[2 * i + 1]);
    }
    
    all_differences(f_values, f_der_values, interp_knots, interp_knots_count);

    printf("Differences:\n");
    for(int i = 0; i < interp_knots_count; i++){
        printf("%lf\n", f_values[2 * i]);
        printf("%lf\n", f_values[2 * i + 1]);
    }

    for(int i = 0; i < points_to_interp_count; i++){
        printf("point: %lf, value: %lf\n", points_to_interp[i], 
               interp_in_point(points_to_interp[i], f_values, interp_knots, interp_knots_count))
    }

    free(interp_knots);
    free(points_to_interp);
    free(f_values);
    free(f_der_values);
    return 0;
}
