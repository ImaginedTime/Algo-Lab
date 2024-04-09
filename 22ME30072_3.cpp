/*************************************************
    Uday om srivastava 22ME30072 Assignment 3
*************************************************/

#include <iostream>
// to use the sqrt function
#include <time.h>
#include <math.h>

using namespace std;

// direct iterative method to calculate the values, O(n)
double compute_iterative(int n)
{
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;

    double current = 1, previous = 0, next;

    for(int i = 0; i < n - 1; i++)
    {
        next = 2 * current + previous;
        previous = current;
        current = next;
    }
    return next;
}

// recursive method, O(2^n), can be memoized
double compute_recursive(int n)
{
    // base cases
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    // recursive definition
    return 2 * compute_recursive(n - 1) + compute_recursive(n - 2);
}

// calculates x^n in O(logn)
double power(double x, int n)
{
    if(n == 0)
        return 1;

    double p = power(x, n / 2);

    return (n % 2 == 0 ? p * p : p * p * x);
}

// using the formula for the sequence ( (1 + root(2)) ^ n - (1 - root(2)) ^ n ) / (2*root(2))
double compute_formula(int n)
{
    double squareRootOf2 = sqrt(2);

    double p1 = power(1 + squareRootOf2, n);
    double p2 = power(1 - squareRootOf2, n);

    return (p1 + p2) / (2 * squareRootOf2);
}

// multiplying the matrices in O(1) time => assuming, it does take some time, but for our purposes, we assume it to be O(1)
void multiply_two_matrices(double f[2][2], double m[2][2])
{
    double x = f[0][0] * m[0][0] + f[0][1] * m[1][0];
    double y = f[0][0] * m[0][1] + f[0][1] * m[1][1];
    double z = f[1][0] * m[0][0] + f[1][1] * m[1][0];
    double w = f[1][0] * m[0][1] + f[1][1] * m[1][1];

    f[0][0] = x;
    f[0][1] = y;
    f[1][0] = z;
    f[1][1] = w;
}

// calculates some power of a matrix recursively in O(logn) time
void power_of_a_matrix(double f[2][2], int n)
{
    // base case
    if(n <= 1)
        return;
    
    double m[2][2] = {{2, 1}, {1, 0}};

    // recursive part
    power_of_a_matrix(f, n / 2);
    multiply_two_matrices(f, f);

    if(n % 2 == 1)
        multiply_two_matrices(f, m);
}

// calculating without division of sqrt int O(logn) time
double compute_fast_without_division(int n)
{
    if(n == 0)
        return 0;

    double f[2][2] = {{2, 1}, {1, 0}};

    power_of_a_matrix(f, n - 1);
    return (double)f[0][0];
}



int main()
{
    int n;
    cout << "Write n: ";
    cin >> n;

    // Iterative method, O(n) direct method
    double time_spent = 0.0;
    clock_t begin = clock();

    double ans = compute_iterative(n);
    printf("I_%d (computed using iterative method) = %f \n", n, ans);
    // cout << "I_" << n << " (computed using iterative method) = " << ans << endl;

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken in iterative method = %f seconds\n\n", time_spent);
    


    // recursive method, O(2^n) but can be memoized to reduce it down to O(n), but here it is O(logn)
    time_spent = 0.0;
    begin = clock();

    ans = compute_recursive(n);
    printf("I_%d (computed using recursive method) = %f \n", n, ans);
    // cout << "I_" << n << " (computed using recursive method) = " << ans << endl;
    
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken in recursive method = %f seconds\n\n", time_spent);
    

    // formula method, O(logn) but is less precise
    time_spent = 0.0;
    begin = clock();

    ans = compute_formula(n);
    printf("I_%d (computed using formula method) = %f \n", n, ans);
    // cout << "I_" << n << " (computed using formula method) = " << ans << endl;
    
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken in formula method = %f seconds\n\n", time_spent);



    // finding out the matrix, and calculating the powers of that matrix to get the ans in O(logn) time, which is precise as well
    time_spent = 0.0;
    begin = clock();

    ans = compute_fast_without_division(n);
    printf("I_%d (computed using fast method avoiding division) = %f \n", n, ans);
    // cout << "I_" << n << " (computed using iterative method) = " << ans << endl;
    
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken in matrix = %f seconds\n\n", time_spent);

    return 0;
}