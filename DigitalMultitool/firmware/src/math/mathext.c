#include <math.h>
#include <stdlib.h>
#include "mathext.h"

#define GAMMA_ITERS 12
double gammap1(double z)
{
    const int a = GAMMA_ITERS;
    static double c_space[GAMMA_ITERS];
    static double *c = NULL;
    int k;
    double accm;
    
    //nonnegative integers: simple factorial
    double trash;
    if (modf(z, &trash) == 0.0 && z >= 0.0) {
        accm = 1.0;
        int k;
        for (k  = (int)z; k > 1; k--) accm *= k;
        return accm;
    }

    if ( c == NULL ) {
      double k1_factrl = 1.0; /* (k - 1)!*(-1)^k with 0!==1*/
      c = c_space;
      c[0] = sqrt(2.0*M_PI);
      for(k=1; k < a; k++) {
        c[k] = exp(a-k) * pow(a-k, k-0.5) / k1_factrl;
        k1_factrl *= -k;
      }
    }
    accm = c[0];
    for(k=1; k < a; k++) {
      accm += c[k] / ( z + k );
    }
    accm *= exp(-(z+a)) * pow(z+a, z+0.5); /* Gamma(z+1) */
    return accm;
}