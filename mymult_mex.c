/* D = mymult (C,A,B) computes D=C+A*B.  With a 4th argument,
   D = mymult (C,A,B,ntrials) computes D=C+ntrials*A*B, by
   repeating the matrix multiplication ntrials times (for more
   accurate run times and to test cache performance).
 */

#include "mex.h"
#include "mymult.h"

void mexFunction
(
    int nargout,
    mxArray *pargout [ ],
    int nargin,
    const mxArray *pargin [ ]
)
{
    double *A, *B, *C, *D ;
    long m, n, k, ntrials, trial, mn, i ;

    /* check inputs */
    if (nargin < 3 || nargin > 4 || nargout > 2)
    {
        mexErrMsgTxt ("Usage: D = mymult (C,A,B, ntrials)") ;
    }

    /* get inputs */

    /* C is m-by-n, A is m-by-k, and B is k-by-n */
    m = mxGetM (pargin [0]) ;
    n = mxGetN (pargin [0]) ;
    k = mxGetN (pargin [1]) ;

    if (m != mxGetM (pargin [1]) ||
        k != mxGetM (pargin [2]) ||
        n != mxGetN (pargin [2]))
    {
        mexErrMsgTxt ("invalid dimensions") ;
    }

    if (nargin == 4)
    {
        ntrials = (long) mxGetScalar (pargin [3]) ;
    }
    else
    {
        ntrials = 1 ;
    }

    if (mxIsSparse (pargin [0]) || mxIsComplex (pargin [0]) ||
        mxIsSparse (pargin [1]) || mxIsComplex (pargin [1]) ||
        mxIsSparse (pargin [2]) || mxIsComplex (pargin [2]))
    {
        mexErrMsgTxt ("inputs must be real, and not sparse") ;
    }

    C = mxGetPr (pargin [0]) ;
    A = mxGetPr (pargin [1]) ;
    B = mxGetPr (pargin [2]) ;
    mn = m*n ;

    /* create output: D is m-by-n */
    pargout [0] = mxCreateDoubleMatrix (m, n, mxREAL) ;
    D = mxGetPr (pargout [0]) ;

    if (ntrials < 1) ntrials = 1 ;

    /* D = C */
    for (i = 0 ; i < mn ; i++) D [i] = C [i] ;

    for (trial = 0 ; trial < ntrials ; trial++)
    {
        /* D = D + A*B */
        mymult (A, B, D, m, n, k) ;
    }
}
