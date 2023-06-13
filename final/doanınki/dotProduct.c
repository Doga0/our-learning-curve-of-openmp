#include<stdio.h>


int main(){
    int i, n;
    int result = 0;

    printf("Enter the size of vectors: ");
    scanf("%d", &n);

    int vector1[n], vector2[n];

    printf("Enter the elements of vector1: ");
    for(i = 0; i < n; ++i)
    {
      scanf("%d", &vector1[i]);
    }

    printf("Enter the elements of vector2:");
    for(i = 0; i < n; ++i)
    {
      scanf("%d", &vector2[i]);
    }

    for ( i = 0; i < n; i++)
    {
        result += vector1[i]*vector2[i];
    }
        printf("Dot product: %d\n", result);
}
