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
            
            int i = 0;
            for (i = 0; i < 19 && *(name+i) != 0; i++)
            {
                *(qf->name + i) = *(name +i);
            }
            for (i = i; i < 20; i++)
            {
                *(qf->name +i) = 0;
            }
            //return true; // You are returning before doing the whole work? ;-;

            qf->client = NULL;
            qf->x = 0.0;

            if (!strcmp(name, "simpson"))
            {
                qf->weights[0] = 1.0 / 6.0;
                qf->weights[1] = 2.0 / 3.0;
                qf->weights[2] = 1.0 / 6.0;
            }
            else if (!strcmp(name, "gauss2"))
            {
                qf->nodes[0] = ( 1.0 - ( 1.0 / sqrt(3.0) ) ) / 2.0;
                qf->nodes[1] = ( 1.0 + ( 1.0 / sqrt(3.0) ) ) / 2.0;

                qf->weights[0] = 0.5;
                qf->weights[1] = 0.5;
            }
            else if (!strcmp(name, "gauss3"))
            {
                qf->nodes[0] = ( 1.0 - sqrt(3.0 / 5.0) ) / 2.0;
                qf->nodes[1] = 0.5;
                qf->nodes[2] = ( 1.0 + sqrt(3.0 / 5.0) ) / 2.0;

                qf->weights[0] = 5.0 / 18.0;
                qf->weights[1] = 4.0 / 9.0;
                qf->weights[2] = 5.0 / 18.0;
            }

            return true; // Now it's "normal" to return...
        }
    }
    return false;
}


double leftMethod(double (*f)(double), double a, double b, int N)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;
    
    const double dx = ( b - a ) / (double)(N);

    for(int i = 0; i < N; i++)
    {
        res += (*f)(a + i * dx) * (dx);
    }
    
    //free(partition_array);
    return res;
}



double rightMethod(double (*f)(double), double a, double b, int N)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;

    const double dx = (b - a) / (double)(N);
    
    for(int i = 0; i < N; i++)
    {
        res += (*f)(a + (i + 1) * dx) * (dx);
    }
    
    //free(partition_array);
    return res;
}



double middleMethod(double (*f)(double), double a, double b, int N)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;
    
    const double dx = (b - a) / (double)(N);
    
    for(int i = 0; i < N; i++)
    {
        double a_i = a + i * dx;
        double mid = a_i + dx / 2.0;
        res += (*f)(mid) * (dx);
    }
    
    //free(partition_array);
    return res;
}



double trapezesMethod(double (*f)(double), double a, double b, int N)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;
    
    const double dx = (b - a) / (double)(N);

    for(int i = 0; i < N; i++)
    {
        double a_i = a + i * dx;
        double b_i = a_i + dx;
        double fact = 0.5 * ( (*f)(a_i))
                    + 0.5 * ( (*f)(b_i));
        res += fact * (dx);
    }
    
    //free(partition_array);
    return res;
}

// simpson
double simpsonMethod(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;

    const double dx = (b - a) / (double)(N);
    
    for(int i = 0; i < N; i++)
    {
        double a_i = a + i * dx;
        double mid = a_i + dx / 2.0;
        double b_i = a_i + dx;

        double fact = qf->weights[0] * ( (*f)(a_i) )
                    + qf->weights[1] * ( (*f)(mid) )
                    + qf->weights[2] * ( (*f)(b_i) );
        res += fact * (dx);
    }
    
    //free(partition_array);
    return res;
}



// gauss2
double gaussTwoMethod(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;

    const double dx = (b - a) / (double)(N);

    for(int i = 0; i < N; i++)
    {
        double a_i = a + i * dx;

        double plus_part = a_i + qf->nodes[0] * dx;
        double minus_part = a_i + qf->nodes[1] * dx;

        double fact = qf->weights[0] * ( (*f)(plus_part) )
                    + qf->weights[1] * ( (*f)(minus_part) );
        res += fact * (dx);
    }

    //free(partition_array);
    return res;
}


// gauss3
double gaussThreeMethod(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
    //double *partition_array = partition(a,b,N);
    double res = 0;

    const double dx = (b - a) / (double)(N);

    for(int i = 0; i < N; i++)
    {
        double a_i = a + i * dx;

        double node1 = a_i + qf->nodes[0] * dx;
        double node2 = a_i + qf->nodes[1] * dx;
        double node3 = a_i + qf->nodes[2] * dx;

        double fact = qf->weights[0] * ( (*f)(node1) )
                    + qf->weights[1] * ( (*f)(node2) )
                    + qf->weights[2] * ( (*f)(node3) );
        res += fact * (dx);
    }
    
    //free(partition_array);
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
    if (b-a < 0)
        return -1 * integrate(f, b, a, N, qf);

    if(!strcmp(qf->name,"left"))
        return leftMethod(f, a, b, N);

    if(!strcmp(qf->name,"right"))
        return rightMethod(f, a, b, N);

    if(!strcmp(qf->name,"middle"))
        return middleMethod(f, a, b, N);

    if(!strcmp(qf->name,"trapezes"))
        return trapezesMethod(f, a, b, N);

    if(!strcmp(qf->name,"simpson"))
        return simpsonMethod(f, a, b, N, qf);

    if(!strcmp(qf->name,"gauss2"))
        return gaussTwoMethod(f, a, b, N, qf);

    if(!strcmp(qf->name,"gauss3"))
        return gaussThreeMethod(f, a, b, N, qf);

    return 0.0;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
    double numerator = b - a;
    if (numerator < 0)
        numerator *= -1;
    int N = (int)(numerator / dx);
    if(N==0) //in case of a too small interval 
        N = 1;

    if(!strcmp(qf->name,"left"))
        return leftMethod(f, a, b, N);

    if(!strcmp(qf->name,"right"))
        return rightMethod(f, a, b, N);

    if(!strcmp(qf->name,"middle"))
        return middleMethod(f, a, b, N);

    if(!strcmp(qf->name,"trapezes"))
        return trapezesMethod(f, a, b, N);

    if(!strcmp(qf->name,"simpson"))
        return simpsonMethod(f, a, b, N, qf);

    if(!strcmp(qf->name,"gauss2"))
        return gaussTwoMethod(f, a, b, N, qf);

    if(!strcmp(qf->name,"gauss3"))
        return gaussThreeMethod(f, a, b, N, qf);

    return 0.0;
}


