



#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
    if(name && qf)
    {
        if(name == "left" || name == "right" || name == "middle" ||
                name == "trapezes" || name == "simpson" || name == "gauss2"||
                name == "gauss3")
        {
            qf->name = name;
            return true;
        }
    }
    return false;
}

double *partition(double a, double b, int N)
{
    double *arr = malloc(sizeof(double)*N*2); 
    for(int i = 0; i < N*2; i+=2)
    {
        *(arr+i) = a + i * ( (b-a)/N ); // ai
        *(arr+i+1) = a + (i+1) * ( (b-a)/N ); // bi
    }
    //a are on even indexes, b odd ones.
    return arr;
}


double leftMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    for(double i = 0; i < N*2; i+=2)
    {
        res += (*f)(*(partition_array+i)) * (*(partition_array+i+1) - *(partition_array + i));
    }
    
    free(partition_array);
    return res;
}



double rightMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    for(double i = 0; i < N*2; i+=2)
    {
        res += (*f)(*(partition_array+i+1)) * (*(partition_array+i+1) - *(partition_array + i + 1));
    }
    
    free(partition_array);
    return res;
}



double middleMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    
    for(double i = 0; i < N*2; i+=2)
    {
        double mid = ( *(partition_array+i) + *(partition_array + i + 1) ) / 2;
        res += (*f)(*(partition_array+i+1)) * (*(partition_array+i+1) - *(partition_array + i + 1));
    }
    
    free(partition_array);
    return res;
}



double trapezesMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    for(double i = 0; i < N*2; i+=2)
    {
        double fact = 0.5 * ( (*f)(*(partition_array+ i ) + 
                      0.5 * ( (*f)(*(partition_array+i+1));
        res += fact * (*(partition_array+i+1) - *(partition_array + i + 1));
    }
    
    free(partition_array);
    return res;
}












/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
  return 0.0;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


