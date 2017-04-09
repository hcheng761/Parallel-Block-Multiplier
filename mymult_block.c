
#include "mymult.h"

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
)
{
    int i, j, t ;
    for (i = 0 ; i < BLK ; i++)
    {
        for (j = 0 ; j < BLK ; j++)
        {
            double c_ij = C [i][j] ;
            for (t = 0 ; t < BLK ; t++)
            {
                double a_it = A [i][t] ;
                double b_jt = B [j][t] ;
                c_ij += a_it * b_jt ;
            }
            C [i][j] = c_ij ;
        }
    }
}
