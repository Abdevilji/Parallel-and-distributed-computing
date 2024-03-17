#include <bits/stdc++.h>

#include <omp.h>

using namespace std;

void LUDecomposition(vector<vector<double> >& A, vector<int>& pivot, int n) {
    for (int i = 0; i < n; i++) {
        pivot[i] = i;
    }

    for (int k = 0; k < n - 1; k++) {
        int pivotRow = k;
        double maxVal = 0.0;

        for (int i = k; i < n; i++) {
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                pivotRow = i;
            }
        }
        swap(pivot[k], pivot[pivotRow]);

        // Swap rows  A
        for (int i = 0; i < n; i++) {
            swap(A[k][i], A[pivotRow][i]);
        }

        // Perform LU factorization
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            A[i][k] = factor;
        }
    }
}
void LUDecompositionParallel(vector<vector<double> >& A, vector<int>& pivot, int n) {
    for (int i = 0; i < n; i++) {
        pivot[i] = i;
    }

    for (int k = 0; k < n - 1; k++) {
        int pivotRow = k;
        double maxVal = 0.0;

        // Find the pivot row in parallel with reduction clause
        #pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            double maxValLocal = 0.0;
            int pivotRowLocal = k;

            #pragma omp parallel for reduction(max: maxVal)
            for (int i = k; i < n; i++) {
                if (abs(A[i][k]) > maxValLocal) {
                    maxValLocal = abs(A[i][k]);
                    pivotRowLocal = i;
                }
            }

            #pragma omp critical
            {
                if (maxValLocal > maxVal) {
                    maxVal = maxValLocal;
                    pivotRow = pivotRowLocal;
                }
            }
        }

        // Swap rows in the pivot vector
        swap(pivot[k], pivot[pivotRow]);

        // Swap rows in the matrix A in parallel
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            swap(A[k][i], A[pivotRow][i]);
        }

        // Perform LU factorization in parallel
        #pragma omp parallel for
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            A[i][k] = factor;
        }
    }
}

void BackwardSubstitution(vector<vector<double> >& A, vector<int>& pivot, vector<double>& b, vector<double>& x, int n) {
    // Forward substitution to solve Ly = b
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = b[pivot[i]];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    // Backward substitution to solve Ux = y
    
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    
}

int main() {
    ifstream infile("inputassign8.txt");
    int n;
    infile >> n;
    vector<vector<double> > A(n, vector<double>(n, 0.0));
    vector<int> pivot(n);
    vector<double> b(n);
    vector<double> x(n);
	cout<<"Omi Vaish 2021BCS0090"<<endl;
    // Read the input matrix A and vector b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile >> A[i][j];
        }
        infile >> b[i];
    }
    infile.close();

    double start_time = omp_get_wtime();

    // Perform LU decomposition with row pivoting
    LUDecomposition(A, pivot, n);

    // Solve the system of linear equations using backward substitution
    BackwardSubstitution(A, pivot, b, x, n);

    double end_time = omp_get_wtime();

    double execution_time = end_time - start_time;
    cout << "Execution Time:serial " << execution_time << " seconds" << endl;

    cout << "Solution Vector x:(Serial)" << endl;
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    
     start_time = omp_get_wtime();

    LUDecompositionParallel(A, pivot, n);

    BackwardSubstitution(A, pivot, b, x, n);

     end_time = omp_get_wtime();
    cout << "Execution Time:(Parallel) " << execution_time << " seconds" << endl;

    // Print the solution vector x
    cout << "Solution Vector x:(parallel)" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Thread " << omp_get_thread_num() << " calculated x[" << i << "] = " << x[i] << endl;
    }


    return 0;
}
