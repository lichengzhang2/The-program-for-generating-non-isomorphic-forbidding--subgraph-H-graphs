/* Plugin for geng: prune graphs containing a butterfly.
   This version counts ONLY the kept (valid) graphs.
   Valid = no butterfly AND size == maxn.
   The total is printed to stderr at exit.
*/
/*gcc -o nobutterfly -DMAXN=WORDSIZE -O3 -march=native -DPRUNE=nobutterfly \
    geng.c nobutterfly.c nauty1.a
*/
#include "gtools.h"

static long keep_count = 0;

static void print_stats(void)
{
    fprintf(stderr, "Kept %ld butterfly-free graphs.\n", keep_count);
}

int
nobutterfly(graph *g, int n, int maxn)
{
    static int first = 1;
    if (first)
    {
        first = 0;
        atexit(print_stats);
    }

    int v = n - 1;
    setword Nv = g[v], S, T, R, Q;
    int a, b, c, x, y;

    /* ----- Case 1: v is center ----- */
    S = Nv;
    while (S)
    {
        TAKEBIT(a, S);
        T = S & g[a];
        while (T)
        {
            TAKEBIT(b, T);

            R = Nv & ~bit[a] & ~bit[b];
            Q = R;
            while (Q)
            {
                TAKEBIT(c, Q);
                if (Q & g[c])
                    return 1;  /* prune */
            }
        }
    }

    /* ----- Case 2: c is center ----- */
    S = Nv;
    while (S)
    {
        TAKEBIT(c, S);
        R = Nv & g[c] & ~bit[c];
        while (R)
        {
            TAKEBIT(x, R);
            setword Nc = g[c] & ~bit[v] & ~bit[x];
            Q = Nc;
            while (Q)
            {
                TAKEBIT(y, Q);
                if (Q & g[y])
                    return 1;  /* prune */
            }
        }
    }

    /* If we reach maxn size, this graph is valid output */
    if (n == maxn)
        keep_count++;

    return 0;  /* keep graph */
}
