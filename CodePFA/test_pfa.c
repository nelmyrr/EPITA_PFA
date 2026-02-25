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

    printf("--- Part 1: Testing PHI(x) (Standard Normal CDF) ---\n");
    double x_vals[] = {0.0, 1.0, 1.96, -1.0};
    double phi_expected[] = {0.5000, 0.8413, 0.9750, 0.1587};
    
    for(int i = 0; i < 4; i++) {
        double res = PHI(x_vals[i]);
        printf("x: %5.2f | Result: %8.5f | Expected: %8.5f\n", 
                x_vals[i], res, phi_expected[i]);
    }

    printf("\n--- Part 2: Testing Finance (Option Pricing) ---\n");
    Option call_opt = {
        .S0 = 100.0,
        .K = 100.0,
        .mu = 0.05,
        .sig = 0.2,
        .T = 1.0,
        .type = CALL
    };
    
    double price = optionPrice(&call_opt);
    printf("Call Option Price: %8.4f\n", price);

    printf("\n--- Part 3: Testing Insurance (Lognormal Claims) ---\n");
    double probabilities[] = {0.7, 0.2, 0.1}; 
    InsuredClient client = {
        .m = 2.0,       
        .s = 0.5,       
        .p = probabilities
    };

    double x_limit = 10.0;
    double cdf_x = clientCDF_X(&client, x_limit);
    double cdf_s = clientCDF_S(&client, x_limit);
    
    printf("Single Claim CDF at x=10.0: %8.5f | Expected: ~0.7271\n", cdf_x);
    
    printf("Total Portfolio CDF at x=10.0: %8.5f | Expected: >0.7000\n", cdf_s);

    return 0;
}

