#include <stdio.h>

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
    
    int result = dotProduct(vector1, vector2);
    
    printf("Dot product: %d\n", result);
    
    return 0;
}
