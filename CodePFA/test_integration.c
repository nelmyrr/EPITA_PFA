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
    return sin(x);
    //return x*x*x;
    //return aIntegral(x);
    //return exp(3 * pow(x, ln(2 * x)));
}

double aIntegral(double x) {
    double x2 = x * x;
    double s = sqrt(x2 + 2.0);
    return atan(s) / ((1.0 + x2) * s);
}

int main()
{

    int precision = 1;
    double from = -10;
    double to   = 10;

    double right  =    rightMethod(&f, from, to, precision);
    double left   =     leftMethod(&f, from, to, precision);
    double middle =   middleMethod(&f, from, to, precision);
    double trap   = trapezesMethod(&f, from, to, precision);


    printf("Precision: %d\n The Right Method shows:       %f\n", precision, right);
    printf(" The Left Method shows:        %f\n", right);
    printf(" The Middle Method shows:      %f\n", right);
    printf(" The Trapezoidal Method shows: %f\n", right);

    return 0;
}
