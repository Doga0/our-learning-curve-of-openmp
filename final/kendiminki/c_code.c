#include <stdio.h>
#include <time.h>

#define VECTOR_SIZE 3

int dotProduct(const int vector1[], const int vector2[]) {
    int dotProduct = 0;
    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        dotProduct += vector1[i] * vector2[i];
    }
    
    return dotProduct;
}

int main() {
    int vector1[VECTOR_SIZE];
    int vector2[VECTOR_SIZE];
    
    printf("Enter the elements of vector1: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        scanf("%d", &vector1[i]);
    }
    
    printf("Enter the elements of vector2: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        scanf("%d", &vector2[i]);
    }
    clock_t t;
    t = clock();
    int result = dotProduct(vector1, vector2);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
    printf("Dot product: %d\n", result);
    printf("took %.10f seconds to execute \n", time_taken);

    return 0;
}
