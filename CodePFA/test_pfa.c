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

    Option option = {
        CALL,
        100.0,
        115.0,
        2.0,
        0.05,
        0.02
    };

    printf("######### Tests de la fonction optionPrice #########\n");
    printf("S0 = 100 | T = 2 | mu = 0.05 | sigma = 0.02\n");

    option.S0 = 100;
    option.T = 2;
    option.mu = 0.05;
    option.sig = 0.02;

    double Ks[5] = {99, 100, 101, 102, 103};

    for (int i = 0; i < 5; i++)
    {
        option.K = *(Ks+i);
        printf("K = %.0f | call price = %.5f\n", *(Ks+i), optionPrice(&option));
    }

    printf("S0 = 100 | K = 101 | mu = 0.05 | sigma = 0.02\n");
    option.S0 = 100;
    option.K = 101;
    option.mu = 0.05;
    option.sig = 0.02;
    double Ts[5] = {1.8, 1.9, 2, 2.1, 2.2};

    for (int i = 0; i < 5; i++)
    {
        option.T = *(Ts+i);
        printf("T = %.1f | call price = %.5f\n", *(Ts+i), optionPrice(&option));
    }


    printf("S0 = 100 | T = 2 | mu = 0.05 | sigma = 0.02\n");
    option.T = 2;
    *(Ks+0) = 113;
    *(Ks+1) = 114;
    *(Ks+2) = 115;
    *(Ks+3) = 116;
    *(Ks+4) = 117;
    option.type = PUT;

    for (int i = 0; i < 5; i++)
    {
        option.K = *(Ks + i);
        double price = optionPrice(&option);
        printf("K = %.0f | put price = %.5f\n", option.K, price);
    }

    printf("S0 = 100 | K = 115 | mu = 0.05 | sigma = 0.02\n");
    option.K = 115;
    *(Ts+0) = 1.8;
    *(Ts+1) = 1.9;
    *(Ts+2) = 2;
    *(Ts+3) = 2.1;
    *(Ts+4) = 2.2;

    for (int i = 0; i < 5; i++)
    {
        option.T = *(Ts + i);
        double price = optionPrice(&option);
        printf("T = %.1f | put price = %.5f\n", option.K, price);
    }


/*    double phi1 = PHI(-1);
    double phi2 = PHI(1);
    printf("######### PHI Testing #########\n\tPHI(-1) = %.4f\n\tPHI(1) = %.4f\n", phi1, phi2);
*/


    printf("\n######### Insurance functions tests #########\n");
    double *array = malloc(sizeof(double) * 3);
    *array = 0.9;
    *(array+1) = 0.05;
    *(array+2) = 0.05;

    InsuredClient client = {
        1,
        1,
        array
    };


/*

    m = s = 1
 15     p_0 = 0.9
 16     p_1 = p_2 = 0.05

*/
    printf("m = s = 1\np_0 = 0.9\np_1 = p_2 = 0.05\n");

    double x = 0;

    for (x = 1; x < 4; x++)
    {
        double pdfX1X2 = clientPDF_X1X2(&client, x);
        double cdfX1X2 = clientCDF_X1X2(&client, x);

        double cdfS = clientCDF_S(&client, x);

        printf("x = %.0f\n     PDF X1X2 = %.8f\n     CDF X1X2 = %.8f\n     CDF S    = %.8f\n", x, pdfX1X2, cdfX1X2, cdfS);
    }

    free(array);

    return 0;
}

