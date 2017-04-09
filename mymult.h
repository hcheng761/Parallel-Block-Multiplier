#include "tictoc.h"
#include "matrix_util.h"
#include <omp.h>

#define BLK 64
#define NMAX (3072) // alternatively 2048

/* C = C+A*B where all matrices are stored in column-major format */
void mymultParallel
(
    double *A,      /* A is n-by-n, input */
    double *B,      /* B is n-by-n, input */
    double *C,      /* C is n-by-n, input/output */
    long m,
    long n,
    long k
) ;


/* C = C+A*B where all matrices are stored in column-major format */
void mymultCannon
(
    double *A,      /* A is n-by-n, input */
    double *B,      /* B is n-by-n, input */
    double *C,      /* C is n-by-n, input/output */
    long m,
    long n,
    long k
) ;


/* C = C+A*B where all matrices are stored in column-major format */
void mymultDNS
(
    double *A,      /* A is n-by-n, input */
    double *B,      /* B is n-by-n, input */
    double *C,      /* C is n-by-n, input/output */
    long m,
    long n,
    long k
) ;

/* C = C+A*B where all matrices are stored in column-major format */
void mymult
(
    double *A,      /* A is n-by-n, input */
    double *B,      /* B is n-by-n, input */
    double *C,      /* C is n-by-n, input/output */
    long m,
    long n,
    long k,
    long lds
) ;

/* load C (i:i+BLK-1, j:j+BLK-1) into Cblock, and transpose it
   if the transpose flag is true.  The C matrix is stored in
   column major order, and Cblock is in row major order */
void load_block
(
    double Cblock [BLK][BLK],
    double *C,      /* n by n with leading dimension n */
    long i,
    long j,
    long n,
    int transpose
) ;

/* save Cblock in to C (i:i+BLK-1, j:j+BLK-1), and transpose it
   if the transpose flag is true.  The C matrix is stored in
   column major order, and Cblock is in row major order */
void save_block
(
    double Cblock [BLK][BLK],
    double *C,      /* n by n with leading dimension n */
    long i,
    long j,
    long n,
    int transpose
) ;


/* C = C+A*B' where all matrices are square, with a fixed size of
 * BLK.  All matrices are stored in row major order.
 * All matrices are accessed in stride-1.
 *
 * Alternatively you can view this function as computing C=C+A*B
 * where C and A are in row-major order, and B is in column-major
 * order.
 */
void mymult_block
(
    double A [BLK][BLK],
    double B [BLK][BLK],
    double C [BLK][BLK]
) ;

