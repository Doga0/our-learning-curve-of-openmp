#include <stdio.h>
#include <mpi.h>

#define VECTOR_SIZE 3

int dotProduct(int vector1[], int vector2[], int start, int end) {
    int dotProduct = 0;
    
    for (int i = start; i < end; i++) {
        dotProduct += vector1[i] * vector2[i];
    }
    
    return dotProduct;
}

int main(int argc, char** argv) {
    int rank, size;
    int vector1[VECTOR_SIZE];
    int vector2[VECTOR_SIZE];
    int localDotProduct = 0;
    int globalDotProduct = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        printf("Enter the elements of vector1: ");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            scanf("%d", &vector1[i]);
        }
        
        printf("Enter the elements of vector2: ");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            scanf("%d", &vector2[i]);
        }
    }
    
    MPI_Bcast(vector1, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector2, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    
    int localStart = rank * VECTOR_SIZE / size;
    int localEnd = (rank + 1) * VECTOR_SIZE / size;
    
    localDotProduct = dotProduct(vector1, vector2, localStart, localEnd);
    
    MPI_Reduce(&localDotProduct, &globalDotProduct, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Dot product: %d\n", globalDotProduct);
    }
    
    MPI_Finalize();
    
    return 0;
}
