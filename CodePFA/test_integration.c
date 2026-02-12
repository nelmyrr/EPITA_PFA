/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods 
 * and show your numericzal results */

double f(double x)
{
    return exp(3x);
}

int main()
{

    double right = rightMethod(&f, -5, 0, 10);

    printf("The result is: %d\n", right);

    return 0;
}
