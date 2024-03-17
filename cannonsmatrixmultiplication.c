#include <stdio.h> 
#include <stdlib.h> 
#include <me.h> 
 
int** allocateMatrix(int N) { 
    int** matrix = (int**)malloc(N * sizeof(int*)); 
    for (int i = 0; i < N; i++) { 
        matrix[i] = (int*)malloc(N * sizeof(int)); 
    } 
    return matrix; 
} 
void deallocateMatrix(int** matrix, int N) { 
    for (int i = 0; i < N; i++) { 
        free(matrix[i]); 
    } 
    free(matrix); 
} 
void mul plyMatrices(int** A, int** B, int** C, int N) { 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            C[i][j] = 0; 
            for (int k = 0; k < N; k++) { 
                C[i][j] += A[i][k] * B[k][j]; 
            } 
        } 
    } 
} 
int main() { 
    //int N; 
    //prin ("Enter the size of matrices (N x N): "); 
    //scanf("%d", &N); 
    int myArray[8] = {3, 4, 10 , 50 ,100,300,500,1000};  
 prin ("Abhishek Harsh 2021BCS0036"); 
    for (int i=0;i<8;i++){ 
    int N = myArray[i]; 
    int** A = allocateMatrix(N); 
    int** B = allocateMatrix(N); 
    int** C = allocateMatrix(N); 
 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            A[i][j] = i + j; 
            B[i][j] = i - j; 
        } 
    } 
    clock_t start = clock(); 
     
    mul plyMatrices(A, B, C, N); 
 
    clock_t end = clock(); 
    double execu onTime = (double)(end - start) / CLOCKS_PER_SEC; 
    prin ("Matrix mul plica on for %dx%d matrices took %.6f seconds\n", N, N, execu onTime); 
    deallocateMatrix(A, N); 
    deallocateMatrix(B, N); 
    deallocateMatrix(C, N); 
    } 
    return 0; 
}
