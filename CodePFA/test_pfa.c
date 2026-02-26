/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{
    if (!init_integration("gauss3", 0.001)) {
        printf("Failed to initialize integration.\n");
        return 1;
    }

    // ######### Put Your Tests Here #########

    return 0;
}

