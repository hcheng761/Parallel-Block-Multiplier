#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#undef  MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#if defined (__APPLE__)
/* Mac */
#include <Accelerate/Accelerate.h>
#else
/* assume Linux and Intel MKL */
#include <mkl.h>
#endif

/* index computation from 2D indices to 1D:  If A(i,j) is stored in
 * column-major form with a leading dimension (# of rows) of lda, then the
 * entry is located at A[INDEX(i,j,lda)]. Thus, in memory, A(0,0) appears
 * first, as A[0], followed by A(1,0), A(2,0), ... A(m-1,0), A(0,1), ... */ 
#define INDEX(i,j,lda)  ((i)+(j)*(lda))

/* Fill a matrix with random values in the range 0 to 1 */
void rand_matrix (double *A, long asize) ;

/* copy matrix C into D.  Both are m-by-n stored in in column major
 * order, with leading dimension lda. */
void copy_matrix
(
    double *D,      /* D is m-by-n, output */
    double *C,      /* C is m-by-n, input */
    long m,
    long n,
    long lda        /* leading dimension of C and D */
) ;

/* compare matrices and D2, returning norm(D1-D2,1) */
double diff_matrix (double *D1, double *D2, long dsize) ;

/* D = beta*C + alpha*A*B using cblas_dgemm.  All matrices are in column
 * major order, with a leading dimension equal to the number of rows in
 * the matrix */
void dgemm_wrapper
(
    double *A,      /* A is m-by-k, input (not modified) */
    double *B,      /* A is m-by-k, input (not modified) */
    double *C,      /* C is m-by-n, input (not modified) */
    double *D,      /* D is m-by-n, output */
    long m,
    long n,
    long k,
    double alpha,
    double beta
) ;

/* print a matrix A of size m-by-n with leading dimension lda */
/* only the first 8-by-8 part is printed. */
void print_matrix (double *A, long m, long n, long lda) ;

