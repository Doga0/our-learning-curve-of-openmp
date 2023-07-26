
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int i, n, rank, size;
    int local_result = 0;
    int result = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the size of vectors: ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_n = n / size;
    int remainder = n % size; // Elements remaining after division among processes

    int vector1[n], vector2[n];
    int local_vector1[local_n + (rank < remainder ? 1 : 0)];
    int local_vector2[local_n + (rank < remainder ? 1 : 0)];

    if (rank == 0) {
        printf("Enter the elements of vector1: ");
        for (i = 0; i < n; ++i) {
            scanf("%d", &vector1[i]);
        }

        printf("Enter the elements of vector2: ");
        for (i = 0; i < n; ++i) {
            scanf("%d", &vector2[i]);
        }
    }

    MPI_Scatter(vector1, local_n + (rank < remainder ? 1 : 0), MPI_INT, local_vector1, local_n + (rank < remainder ? 1 : 0), MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector2, local_n + (rank < remainder ? 1 : 0), MPI_INT, local_vector2, local_n + (rank < remainder ? 1 : 0), MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < local_n + (rank < remainder ? 1 : 0); i++) {
        local_result += local_vector1[i] * local_vector2[i];
    }

    MPI_Reduce(&local_result, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Dot product: %d\n", result);
    }

    MPI_Finalize();

    return 0;
}

