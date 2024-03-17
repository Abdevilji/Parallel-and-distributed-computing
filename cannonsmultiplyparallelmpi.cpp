#include <stdio.h> 
#include <stdlib.h> 
#include <me.h> 
#include <mpi.h> 
#define N 500 
 
void matrixMul ply(int A[N][N], int B[N][N], int C[N][N]) { 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            C[i][j] = 0; 
            for (int k = 0; k < N; k++) { 
                C[i][j] += A[i][k] * B[k][j]; 
            } 
        } 
    } 
} 
int main(int argc, char *argv[]) { 
    int A[N][N], B[N][N], C[N][N]; 
    double execu onTime = 0.0,start,end; 
 
    // Ini alize MPI 
    MPI_Init(&argc, &argv); 
    int rank, size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
 
    if (rank == 0) { 
        clock_t start = clock(); 
        for (int i = 0; i < N; i++) { 
            for (int j = 0; j < N; j++) { 
                A[i][j] = rand() % 100; 
                B[i][j] = rand() % 100; 
            } 
        } 
    } 
    
    MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD); 
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD); 
    matrixMul ply(A, B, C); 
 
    MPI_Gather(C, N * N, MPI_INT, C, N * N, MPI_INT, 0, MPI_COMM_WORLD); 
    if (rank == 0) { 
  clock_t end = clock(); 
        execu onTime = (double)(end - start) / CLOCKS_PER_SEC; 
        prin ("Matrix mul plica on of Size %d completed%.6f seconds.\n",N,execu onTime); 
 prin ("Abhishek Harsh 2021BCS0036"); 
    } 
    MPI_Finalize(); 
    return 0;     
} 
