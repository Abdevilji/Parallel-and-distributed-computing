#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void generate_random_matrix(vector<vector<int> >& matrix, int rows, int cols) {
//    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100; // Generate random values between 0 and 99
        }
    }
}
void parallel_matrix_add(const vector<vector<int> >& A,
                         const vector<vector<int> >& B,
                         vector<vector<int> >& C,
                         int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
void parallel_matrix_multiply(const vector<vector<int> >& A,
                              const vector<vector<int> >& B,
                              vector<vector<int> >& C,
                              int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols;++j) {
            C[i][j] = 0;
            for (int k = 0; k < cols; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int rows, cols;

    cout << "Enter the number of rows for matrix : ";
    cin >> rows;
    cout << "Enter the number of columns for matrix : ";
    cin >> cols;
  

    vector<vector<int> > A(rows, vector<int>(cols));
    vector<vector<int> > B(cols, vector<int>(cols));

    generate_random_matrix(A, rows, cols);
    generate_random_matrix(B, rows, cols);

    vector<vector<int> > C(rows, vector<int>(cols, 0));
	 vector<vector<int> > D(rows, vector<int>(cols, 0));
   

    cout << "Matrix A:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
	 parallel_matrix_multiply(A, B, C, rows, cols);
	 parallel_matrix_add(A, B, D, rows, cols);
    cout << "Resultant matrix C:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Resultant matrix D:" << endl;
     for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << D[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
