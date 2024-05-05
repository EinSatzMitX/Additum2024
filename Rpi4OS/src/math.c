#include "../include/math.h"


// Function to calculate factorial
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate power
double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// Function to calculate sine using Taylor series expansion
double sine(double x) {
    double result = 0.0;
    int sign = 1;
    for (int n = 0; n < FACTORIAL_LIMIT; n++) {
        result += sign * power(x, 2 * n + 1) / factorial(2 * n + 1);
        sign *= -1;
    }
    return result;
}

// Function to calculate cosine using Taylor series expansion
double cosine(double x) {
    double result = 0.0;
    int sign = 1;
    for (int n = 0; n < FACTORIAL_LIMIT; n++) {
        result += sign * power(x, 2 * n) / factorial(2 * n);
        sign *= -1;
    }
    return result;
}

// This is pretty unnecessary but still nice to have
double tangent(double x) {
    return sine(x) / cosine(x);
}