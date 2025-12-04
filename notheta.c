/* Plugin for geng: prune graphs containing a theta (two triangles sharing an edge).
   This version counts ONLY the kept (valid) graphs.
   Valid = no such theta AND size == maxn.
   The total is printed to stderr at exit.
*/
/*gcc -o notheta -DMAXN=WORDSIZE -O3 -march=native -DPRUNE=notheta \
    geng.c notheta.c nauty1.a
*/
#include "gtools.h"

static long keep_count = 0;

static void print_stats(void)
{
    fprintf(stderr, "Kept %ld theta-free graphs.\n", keep_count);
}

/*
   A forbidden theta is detected when an edge has at least two distinct
   common neighbours (two triangles sharing that edge).
*/
int
notheta(graph *g, int n, int maxn)
{
    static int first = 1;
    if (first)
    {
        first = 0;
        atexit(print_stats);
    }

    int v = n - 1;
    setword Nv = g[v], S, T;
    int a, b;

    /*
       Check edges incident to the new vertex v. If any edge (v,a) has two
       or more common neighbours, then that edge lies in two triangles.
    */
    S = Nv;
    while (S)
    {
        TAKEBIT(a, S);
        setword common = Nv & g[a] & ~bit[v] & ~bit[a];
        if (common & (common - 1))
            return 1; /* prune */
    }

    /*
       For edges (a,b) that already existed, adding v as an extra common
       neighbour might create a second triangle sharing that edge.
       We only need to test edges where both endpoints are neighbours of v.
    */
    S = Nv;
    while (S)
    {
        TAKEBIT(a, S);
        T = S & g[a];
        while (T)
        {
            TAKEBIT(b, T);
            if (g[a] & g[b] & ~bit[v])
                return 1; /* prune */
        }
    }

    if (n == maxn)
        keep_count++;

    return 0; /* keep graph */
}
