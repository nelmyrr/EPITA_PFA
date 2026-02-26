/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{
    if (!init_integration("gauss3", 0.1)) {
        printf("Failed to initialize integration.\n");
        return 1;
    }

    // ######### Put Your Tests Here #########

    /*Option option = {
        PUT,
        100.0,
        115.0,
        2.0,
        0.05,
        0.02
    };

    double put_price = optionPrice(&option);

    printf("Put price: %.5f\n", put_price);*/

    /*double phi1 = PHI(-1);
    double phi2 = PHI(1);
    printf("######### PHI Testing #########\n\tPHI(-1) = %.4f\n\tPHI(1) = %.4f\n", phi1, phi2);
*/
    double *array = malloc(sizeof(double) * 3);
    *array = 0.9;
    *(array+1) = 0.05;
    *(array+2) = 0.05;

    double *array2 = malloc(sizeof(double) * 3);
    *array2 = 0.9;
    *(array2+1) = 0.05;
    *(array2+2) = 0.05;

    InsuredClient client2 = {
        1,
        1,
        array
    };

    InsuredClient client = {
        1,
        1,
        array2
    };

    double x = 1;

    double pdfX1X2 = clientPDF_X1X2(&client, x);
    double cdfX1X2 = clientCDF_X1X2(&client2, x);

    double cdfS = clientCDF_S(&client, x);

    printf("######### Results #########\n     PDF X1X2 = %.4f\n     CDF X1X2 = %.4f\n     CDF S    = %.4f\n", pdfX1X2, cdfX1X2, cdfS);

    free(array);
    free(array2);

    return 0;
}

