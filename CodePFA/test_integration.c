/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods 
 * and show your numericzal results */

double aIntegral(double x);
double target_function(double x);

double challenging_function(double x) {
    return exp(x) * cos(exp(x));
}


double f(double x)
{
    //return sin(x);
    //return x*x*x;
    //return aIntegral(x);
    //return target_function(x);
    return challenging_function(x); // -0.8414709848
    //return x*x;
    //return exp(3 * pow(x, ln(2 * x)));
}


//
//Lower Bound (a): 0.0
//Upper Bound (b): 2.0
//Exact Value: ~ 0.42116...
double target_function(double x) { 
    return exp(-x * x) * sin(x);
}

double aIntegral(double x) { // ~ 0.514 between 0 and 1
    double x2 = x * x;
    double s = sqrt(x2 + 2.0);
    return atan(s) / ((1.0 + x2) * s);
}

double precPercent(double found, double exact)
{
    double abs_error = fabs(found - exact);
    if (exact != 0)
    {
        return (abs_error / fabs(exact)) * (double)(100);
    }
    else
    {
        return 0;
    }
}

int test(double (*f)(double), double from, double to, int precision, double exact)
{
    double right  =    rightMethod(f, from, to, precision);
    double left   =     leftMethod(f, from, to, precision);
    double middle =   middleMethod(f, from, to, precision);
    double trap   = trapezesMethod(f, from, to, precision);
    double simp   = simpsonMethod(f, from, to, precision);
    double gtwo   = gaussTwoMethod(f, from, to, precision);
    double gtre   = gaussThreeMethod(f, from, to, precision);


    printf("Precision: %d\n\tThe Right Method shows:       %f\t| Error Percentage: %.10f%%\n", precision, right, precPercent(right, exact));
    printf("\tThe Left Method shows:        %f\t| Error Percentage: %.10f%%\n", left, precPercent(left, exact));
    printf("\tThe Middle Method shows:      %f\t| Error Percentage: %.10f%%\n", middle, precPercent(middle, exact));
    printf("\tThe Trapezoidal Method shows: %f\t| Error Percentage: %.10f%%\n", trap, precPercent(trap, exact));
    printf("\tThe Simpson Method shows:     %f\t| Error Percentage: %.10f%%\n", simp, precPercent(simp, exact));
    printf("\tThe Gauss2 Method shows:      %f\t| Error Percentage: %.10f%%\n", gtwo, precPercent(gtwo, exact));
    printf("\tThe Gauss3 Method shows:      %f\t| Error Percentage: %.10f%%\n\n", gtre, precPercent(gtre, exact));

    return 0;
}

int main()
{
    double from = 0;
    double to = log(2 * M_PI);
    double exact = -0.8414709848;

    printf("The exact value is: %f\n", exact);

    test(&f, from, to, 2, exact);
    test(&f, from, to, 5, exact);
    test(&f, from, to, 10, exact);
    test(&f, from, to, 50, exact);
    test(&f, from, to, 100, exact);
    test(&f, from, to, 500, exact);
    test(&f, from, to, 1000, exact);
    test(&f, from, to, 5000, exact);

    return 0;
}
