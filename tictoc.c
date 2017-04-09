#include "tictoc.h"

/* Portable timing routines for Linux and Mac OSX.  Example of use:

    #include "tictoc.h"
    double tic [2] ;
    my_tic (tic) ;          // start the timer 
    do_stuff ;
    t = my_toc (tic) ;      // end the timer
    printf ("time for do_stuff, in seconds: %g\n", t) ;
*/

/* my_tic: return the current time.  Time is returned as an integer number
   of seconds in tic [0], plus nanoseconds in tic [1] (the latter is in the
   range of 0 to (1e9)-1).  The total time in seconds is thus
   tic [0] + 1e-9 * tic [1]. */
void my_tic (double tic [2])
{
    #ifdef __MACH__
        /* Mac OSX: use mach_absolute_time */
        static double ratio = 0 ;
        uint64_t time  ;
        double nano ;
        /* get the conversion factor from time units to nanoseconds. */
        if (ratio == 0)
        {
            /* This is a bit slow, so do this only once and save the result in
             * the static ratio. */
            mach_timebase_info_data_t info ;
            mach_timebase_info (&info) ;
            ratio = ((double) info.numer) / ((double) info.denom) ;
        }
        /* get the total current time in nanoseconds since last reboot */
        time = mach_absolute_time ( ) ;
        nano = ((double) time) * ratio ;
        /* split the time into seconds and nanoseconds */
        tic [0] = floor (nano / 1e9) ;
        tic [1] = nano - tic [0] * 1e9 ;
    #else
        /* Linux: POSIX C 1993 timer, requires -librt */
        struct timespec t ;
        clock_gettime (CLOCK_MONOTONIC, &t) ;
        tic [0] = (double) (t.tv_sec) ;         /* seconds */
        tic [1] = (double) (t.tv_nsec) ;        /* plus nanoseconds */
    #endif
}

/* return the elapsed time since the last call to my_tic */
double my_toc (double tic [2])
{
    double toc [2] ;
    my_tic (toc) ;
    return ((toc [0] - tic [0]) + 1e-9 * (toc [1] - tic [1])) ;
}

