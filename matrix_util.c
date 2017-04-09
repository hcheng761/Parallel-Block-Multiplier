#include "matrix_util.h"

/* fill a matrix with random values in the range 0 to 1 */
void rand_matrix (double *A, long asize)
{
    long i ;
    for (i = 0 ; i < asize ; i++)
    {
        A [i] = ((double) rand ( )) / (double) RAND_MAX ;
    }
}

/* copy matrix C into D.  Both are m-by-n stored in in column major
 * order, with leading dimension lda. */
void copy_matrix
(
    double *D,      /* D is m-by-n, output */
    double *C,      /* C is m-by-n, input */
    long m,
    long n,
    long lda        /* leading dimension of C and D */
)
{
    long i, j ;
    for (j = 0 ; j < n ; j++)
    {
        for (i = 0 ; i < m ; i++)
        {
            /* D (i,j) = C (i,j) */
            D [INDEX (i,j,lda)] = C [INDEX (i,j,lda)] ;
        }
    }
}

/* compare matrices D1 and D2, returning norm(D1-D2,1) */
double diff_matrix (double *D1, double *D2, long dsize)
{
    long i ;
    double err, maxerr = 0 ;
    for (i = 0 ; i < dsize ; i++)
    {
        err = fabs (D1 [i] - D2 [i]) ;
        maxerr = fmax (maxerr, err) ;
    }
    return (maxerr) ;
}

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
)
{
    /* D = C */
    copy_matrix (D, C, m, n, m) ;

    /* D = alpha*D + beta*A*B */
    cblas_dgemm (CblasColMajor, CblasNoTrans, CblasNoTrans,
        (int) m, (int) n, (int) k, alpha, A, (int) m, B, (int) k,
        beta, D, (int) m) ;
}

/* print a matrix A of size m-by-n with leading dimension lda */
/* only the first 8-by-8 part is printed. */
void print_matrix (double *A, long m, long n, long lda)
{
    long i, j ;
    for (i = 0 ; i < MIN(m,8) ; i++)
    {
        for (j = 0 ; j < MIN(n,8) ; j++)
        {
            printf ("%g ", A [INDEX (i,j,lda)]) ;
        }
        printf ("\n") ;
    }
}

