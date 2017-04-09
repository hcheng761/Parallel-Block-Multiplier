/* tictoc.h: Portable timing routines for Linux and Mac OSX. */

#include <math.h>

#ifdef __MACH__
/* Mac OSX */
#include <mach/mach_time.h>
#else
/* Linux */
#include <time.h>
#endif

void   my_tic (double tic [2]) ;
double my_toc (double tic [2]) ;

