#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
    if(name && qf)
    {
        if(!strcmp(name, "left") || !strcmp(name, "right") || !strcmp(name, "middle") ||
                !strcmp(name, "trapezes") || !strcmp(name, "simpson") || !strcmp(name, "gauss2")||
                !strcmp(name, "gauss3"))
        {
            //qf->name = name; // this doesn't work, it's an array type left and a pointer type right
            
            for (int i = 0; i < 20 && *(name+i) != 0; i++)
            {
                *(qf->name + i) = *(name +i);
            }
            return true;
        }
    }
    return false;
}

double *partition(double a, double b, int N)
{
    double *arr = malloc(sizeof(double)*(N+1)); 
    for(int i = 0; i <= N; i++)
    {
        *(arr+i) = a + i * ( (b-a)/N ); // a_(i) or b_(i-1)
    }
    // Now, there is only N+1 elements, you'll need to use
    // the same number as a and as b
    return arr;
}


double leftMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    for(int i = 0; i < N; i++)
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
    
    for(int i = 0; i < N; i++)
    {
        res += (*f)(*(partition_array+i+1)) * (*(partition_array+i+1) - *(partition_array + i));
    }
    
    free(partition_array);
    return res;
}



double middleMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    
    for(int i = 0; i < N; i++)
    {
        double mid = ( *(partition_array+i) + *(partition_array + i+1) ) / 2;
        res += (*f)(mid) * (*(partition_array+i+1) - *(partition_array+i));
    }
    
    free(partition_array);
    return res;
}



double trapezesMethod(double (*f)(double), double a, double b, int N)
{
    double *partition_array = partition(a,b,N);
    double res = 0;
    
    for(int i = 0; i < N; i++)
    {
        double fact = 0.5 * ( (*f)(*(partition_array+ i )))
                    + 0.5 * ( (*f)(*(partition_array+i+1)));
        res += fact * (*(partition_array+i+1) - *(partition_array + i));
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


