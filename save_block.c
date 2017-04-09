#include "mymult.h"

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
)
{
    long iblk, jblk ;

    if (transpose)
    {
        for (iblk = 0 ; iblk < BLK ; iblk++)
        {
            for (jblk = 0 ; jblk < BLK ; jblk++)
            {
                C [INDEX (j + jblk, i + iblk, n)] = Cblock [iblk][jblk] ;
            }
        }
    }
    else
    {
        /* i is the innermost loop so C is accessed with stride-1 */
        for (jblk = 0 ; jblk < BLK ; jblk++)
        {
            for (iblk = 0 ; iblk < BLK ; iblk++)
            {
                C [INDEX (i + iblk, j + jblk, n)] = Cblock [iblk][jblk] ;
            }
        }
    }
}

