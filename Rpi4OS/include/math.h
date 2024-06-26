#ifndef MATH_H
#define MATH_H

#define PI 3.14159265358979323846
#define FACTORIAL_LIMIT 10

int factorial(int n);
double power(double base, int exponent);
double sine(double x);
double cosine(double x);
double tangent(double x);
unsigned int lcg_rand();
void lcg_srand(unsigned int new_seed);

#endif // MATH_H