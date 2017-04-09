#include "mymult.h"

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
)
{
    long iblk, jblk ;

    if (transpose)
    {
        for (jblk = 0 ; jblk < BLK ; jblk++)
        {
            for (iblk = 0 ; iblk < BLK ; iblk++)
            {
                Cblock [jblk][iblk] = C [INDEX (i + iblk, j + jblk, n)] ;
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
                Cblock [iblk][jblk] = C [INDEX (i + iblk, j + jblk, n)] ;
            }
        }
    }
}

