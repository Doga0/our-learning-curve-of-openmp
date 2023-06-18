#include <stdio.h>
#include <omp.h>
#define VECTOR_SIZE 3

int dotProduct(int vector1[], int vector2[]) {
    int dotProduct = 0;
#pragma omp parallel for reduction(+:dotProduct)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        dotProduct += vector1[i] * vector2[i];
    }

    return dotProduct;
}

int main() {
    int vector1[VECTOR_SIZE];
    int vector2[VECTOR_SIZE];
    double start_time , end_time;
    printf("Enter the elements of vector1: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        scanf("%d", &vector1[i]);
    }

    printf("Enter the elements of vector2: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        scanf("%d", &vector2[i]);
    }
start_time = omp_get_wtime();
    int result = dotProduct(vector1, vector2);
end_time = omp_get_wtime();

    printf("Dot product: %d\n", result);
    printf("Work took %.10f seconds\n", end_time - start_time);
    
    return 0;
}
