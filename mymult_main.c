#include "mymult.h"

int main (int argc, char **argv)
{
    double *A, *B, *C, *D, one = (double) 1.0, err, *D3, tic [2], t ;
    double t2 [2], tt ;
    double flops ;
    long n, i ;

    n = BLK ;
    flops = 2 * ((double) n) * ((double) n) * ((double) n) ;

    A  = (double *) malloc (NMAX*NMAX*sizeof (double)) ;
    B  = (double *) malloc (NMAX*NMAX*sizeof (double)) ;
    C  = (double *) malloc (NMAX*NMAX*sizeof (double)) ;
    D  = (double *) malloc (NMAX*NMAX*sizeof (double)) ;
    D3 = (double *) malloc (NMAX*NMAX*sizeof (double)) ;

#if 0

    /* fill A, B, and C with random values */
    rand_matrix (A, n*n) ;
    rand_matrix (B, n*n) ;
    rand_matrix (C, n*n) ;

    /* D = C */
    copy_matrix (D, C, n, n, n) ;

    printf ("\nD = [\n") ; print_matrix (D, n, n, n) ; printf ("] ;\n") ;
    printf ("\nA = [\n") ; print_matrix (A, n, n, n) ; printf ("] ;\n") ;
    printf ("\nB = [\n") ; print_matrix (B, n, n, n) ; printf ("] ;\n") ;

    /* D = C + A*B using mymult */
    my_tic (tic) ;
    mymult (A, B, D, n) ;
    t = my_toc (tic) ;
    printf ("%% time %g  gflops %g\n", t, 1e-9 * flops / t) ;

    printf ("D2 = D + A*B ;\n") ;
    printf ("\nD2 = [\n") ; print_matrix (D, n, n, n) ; printf ("] ;\n") ;

    /* warmup, D3 = C + A*B using dgemm */
    printf ("\nD3 = D + A*B ;   %% using dgemm:\n") ;
    dgemm_wrapper (A, B, C, D3, n, n, n, one, one) ;

    /* D3 = C + A*B using dgemm, for timing */
    my_tic (tic) ;
    dgemm_wrapper (A, B, C, D3, n, n, n, one, one) ;
    t = my_toc (tic) ;
    printf ("%% time %g  gflops %g\n", t, 1e-9 * flops / t) ;

    err = diff_matrix (D3, D, n*n) ;
    printf ("err = %g\n", err) ;

    printf ("\nD3 = [\n") ; print_matrix (D3, n, n, n) ; printf ("] ;\n") ;
#endif

#if 1

    /* Extensive test */
    printf ("\n\n%% Extensive test:\n%% n  time(sec)   Gflops  DGEMM-Gflops\nResults = [\n") ;
    for (n = BLK*4 ; n <= NMAX ; n += BLK*4)
    {
        long trial, ntrials ;

        // if (n != 181) continue ;

#if 0
        /* for n > 200, do only every 10th dimension */
        if (n > 200  && (10  * (n/ 10) != n)) continue ;
        /* for n > 1000, do only every 100th dimension */
        if (n > 300 && (100 * (n/100) != n)) continue ;
#endif

        flops = 2 * ((double) n) * ((double) n) * ((double) n) ;

        if (n < 10)
        {
            ntrials = 1000 ;
        }
        else if (n < 100)
        {
            ntrials = 100 ;
        }
        else if (n < 300)
        {
            ntrials = 10 ;
        }
        else
        {
            ntrials = 1 ;
        }

        /* fill A, B, and C with random values */
        rand_matrix (A, n*n) ;
        rand_matrix (B, n*n) ;
        rand_matrix (C, n*n) ;

        /* D = C */
        copy_matrix (D, C, n, n, n) ;

        /* D = C + ntrials*A*B using mymult */
        my_tic (tic) ;
        for (trial = 0 ; trial < ntrials ; trial++)
        {
            mymultParallel (A, B, D, n, n, n) ;
	   
			/*mymultCannon (A, B, D, n, n, n) ;
			
			mymultDNS (A, B, D, n, n, n) ; */
			
			/*the algorithms are run separately */
        }
        t = my_toc (tic) ;
        t = t / ((double) ntrials) ;

        /* check: */
        err = 0 ;
        my_tic (tic) ;
        dgemm_wrapper (A, B, C, D3, n, n, n, (double) (ntrials), one) ;
        tt = my_toc (tic) ;
        err = diff_matrix (D3, D, n*n) ;

        printf ("%4ld %.10g  %.2f %.4e    %.2f\n", n, t, 1e-9 * flops / t, err,
         1e-9 * flops / tt) ;
        
	fflush (stdout) ;
    }
    printf ("] ;\n") ;
    printf ("nmax = %d\n", NMAX) ;
    printf ("plot (Results(:,1), Results(:,3), 'o') ;  %% to plot in MATLAB\n") ;

#endif

    free (A) ;
    free (B) ;
    free (C) ;
    free (D) ;
    free (D3) ;
    return (0) ;
}
