/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{

    double tests[4] = {0.0, 1.0, 1.96, -1.0};
    
    printf("Testing PHI(x):\n");
    for(int i = 0; i < 4; i++) {
        printf("x = %5.2f | Result = %8.5f\n", *(tests+i), PHI(*(tests+i)));
    }
    return 0;

}
