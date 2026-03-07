#include "pfa.h"
#include <stdio.h>
#include <string.h>

void purge()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    char method[20];
    double step;
    int menu_choice = 0;

    printf("--- PFA: Finance & Insurance System ---\n");
    
    printf("Enter quadrature formula name: ");
    scanf("%19s", method);
    printf("Enter subdivision length (dt): ");
    scanf("%lf", &step);

    if (!init_integration(method, step))
    {
        printf("Error: init_integration failed.\n");
        return 1;
    }

    while (menu_choice != 3)
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Financial Client: Calculate Option Price\n");
        printf("2. Insurance Client: Calculate Cumulative Distribution Function S\n");
        printf("3. Quit Program\n");
        printf("Choice: ");
        
        if (scanf("%d", &menu_choice) != 1) 
        {
            purge();
            continue;
        }

        if (menu_choice == 1) 
        {
            Option opt;
            int type_input;
            printf("\n[Financial Calculation]\n");
            printf("Option Type (0 for CALL, 1 for PUT): ");
            scanf("%d", &type_input);
            opt.type = (OptionType)type_input;
            printf("S0: "); scanf("%lf", &opt.S0);
            printf("K: ");  scanf("%lf", &opt.K);
            printf("T: ");  scanf("%lf", &opt.T);
            printf("Mu: "); scanf("%lf", &opt.mu);
            printf("Volatility: "); scanf("%lf", &opt.sig);

            double price = optionPrice(&opt);
            printf("\n>> Result -> Option Price: %.6f\n", price);

        }
        else if (menu_choice == 2) 
        {
            InsuredClient client;
            double probs[3];
            double x_val;
            printf("\n[Insurance Calculation]\n");
            printf("m: "); scanf("%lf", &client.m);
            printf("s: "); scanf("%lf", &client.s);
            printf("Probabilities p[0], p[1], p[2]: ");
            scanf("%lf %lf %lf", &probs[0], &probs[1], &probs[2]);
            client.p = probs;
            printf("Threshold x: ");
            scanf("%lf", &x_val);

            double result = clientCDF_S(&client, x_val);
            printf("\n>> Result -> clientCDF_S: %.6f\n", result);

        } 
        else if (menu_choice == 3) 
        {
            printf("Exiting system...\n");
        }
        else
        {
            printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
