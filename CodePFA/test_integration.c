/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods 
 * and show your numericzal results */

double aIntegral(double x);

double f(double x)
{
    //return sin(x);
    //return x*x*x;
    return aIntegral(x);
    //return exp(3 * pow(x, ln(2 * x)));
}

double aIntegral(double x) { // ~ 0.514 between 0 and 1
    double x2 = x * x;
    double s = sqrt(x2 + 2.0);
    return atan(s) / ((1.0 + x2) * s);
}

int test(double (*f)(double), double from, double to, int precision)
{
    double right  =    rightMethod(f, from, to, precision);
    double left   =     leftMethod(f, from, to, precision);
    double middle =   middleMethod(f, from, to, precision);
    double trap   = trapezesMethod(f, from, to, precision);


    printf("Precision: %d\n\tThe Right Method shows:       %f\n", precision, right);
    printf("\tThe Left Method shows:        %f\n", left);
    printf("\tThe Middle Method shows:      %f\n", middle);
    printf("\tThe Trapezoidal Method shows: %f\n", trap);

    return 0;
}

int main()
{
    test(&f, 0, 1, 1);
    test(&f, 0, 1, 5);
    test(&f, 0, 1, 10);
    test(&f, 0, 1, 50);
    test(&f, 0, 1, 100);
    test(&f, 0, 1, 500);
    test(&f, 0, 1, 1000);

    return 0;
}
