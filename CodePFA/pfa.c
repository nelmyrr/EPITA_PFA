

// #define GRAPHIC

#define PFA_C

#include "pfa.h"

/* Initialize the integration variables.
   Arguments :
   - quadrature : name of the quadrature formula that will be used. It can be "left", "right", 
     "middle", "trapezes", "simpson", "gauss2" or "gauss3".
   - dt : a positive value, which will be used to decide the number of subdivisions of an 
          interval [a,b], when computing the integration.
          The number of subdivisions will be N such that (b-a)/N ~ dt
*/
bool init_integration(char* quadrature, double dt)
{
    if(dt<0)
        return false;
    pfa_dt = dt;

    return setQuadFormula(&pfaQF, quadrature);
}



/* Density of the normal distribution */
double phi(double x)
{
    
  //return 0.398942280401433 * exp( -x*x/2 );
    return ( 1 / sqrt(2*pi) ) * exp( -x*x / 2 ); 
}

/* Cumulative distribution function of the normal distribution */
double PHI(double x)
{
  return 1/2 + integrate_dx( &phi, 0, x, pfa_dt, &pfaQF );
}


/* =====================================
   Finance function: price of an option 
*/
double optionPrice(Option* option)
{
    if(option->type == CALL)
        return price_call(option);
    return price_put(option);
}


double price_call(Option *option)
{
    double z0 = ( ln(option->K / option->S0) - (option->mu - ( pow(option->sig, 2) / 2))*option->T)
                / ( option->sig * sqrt(option->T) );

    return option->K * PHI(z0) - ( option->S0 * exp(option->mu * option->T) )
                                 *PHI(z0 - option->mu * sqrt(option->T));
}


double price_put(Option * opt)
{
    double z0 = ( ln(option->K / option->S0) - (option->mu - ( pow(option->sig, 2) / 2))*option->T)
                / ( option->sig * sqrt(option->T) );


    return opt->K * PHI(z0) - S0 * exp(opt->mu * opt->T) * ( z0 - opt->mu * sqrt(opt->T));
}





/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientPDF_X(InsuredClient* client, double x)
{
    if(x<=0)
        return 0;
    return (1 / ( client->s )) * phi( (log(x) - client->m) / client->s );
}


/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
    if(x<=0)
        return 0;
    return PHI( (log(x) - client->m) / client->s );
}


/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/

double f(double t)
{
    return clientPDF_X(pfaQF.client, t)* clientPDF_X(pfaQF.client, pfaQF.x - t)
}

double clientPDF_X1X2(InsuredClient* client, double x)
{
    pfaQF.client = client;
    pfaQF.x = x;
    return integrate_dx( &f, 0, x, pfa_dt, &pfaQF );
}


/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientCDF_X1X2(InsuredClient* client, double x)
{
    pfaQF.client = client;
    pfaQF.x = x;
    return integrate_dx( &clientPDF_X1X2, 0, x, &pfaQF );
}



/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
    if (x < 0)
        return 0.0;
    if (x == 0)
        return *(client->p + 0);

    return *(client->p)
            + *(client->p+1) * clientCDF_X(client, x)
            + *(client->+2) * clientCDF_X1X2(client, x);
}






