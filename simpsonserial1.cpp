#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x) {
    return 4.0 / (1.0 + x * x);
}
int thread;

int main() {
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;

    double a = 0.0; // Lower limit of integration
    double b = 1.0; // Upper limit of integration
    double h = (b - a) / n; // Step size

    double sum = 0.0;

    double start_time = omp_get_wtime(); // Start timing

//    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        double fx = f(x);

        if (i == 0 || i == n - 1) {
            sum += fx;
        } else if (i % 2 == 1) {
            sum += 4 * fx;
        } else {
            sum += 2 * fx;
        }
         thread=omp_get_thread_num();
    }
    
	cout << " Thread number is: "<< thread<< endl;
  
    double result = (h / 3.0) * sum;

    double end_time = omp_get_wtime(); // End timing

    cout << "Estimated value of pi: " << result << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000<< " milliseconds" << endl;

    return 0;
}

