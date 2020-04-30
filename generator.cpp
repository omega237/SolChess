#include "generator.h"

Generator::Generator()
{
    one = 1;
    b[16] = '\0';
    run = false;
    // perhaps randomize the set string
}

char* Generator::generate() {
    run = true;
    strcpy(b, "----------------");
    comb(32, 16, 0, 0);
    return b;
}

void Generator::comb(int pool, int need, marker chosen, int at)
{
    if (!run || (pool < need + at)) return; /* not enough bits left */

    if (!need && run) {
        /* got all we needed; print the thing.  if other actions are
         * desired, we could have passed in a callback function. */
        int k=0;
        for (at = 0; at < pool; at++) {
            if (chosen & (one << at)) {
                b[k] =  set[at];
                k++;
            }
        }
        if(strcmp(b, "----------------") != 0) {
            Solver s;
            if(s.initAndRun(b) > 0) {
                run = false;
            }
        }
        return;
    }
    /* if we choose the current item, "or" (|) the bit to mark it so. */
    if(run) {
        comb(pool, need - 1, chosen | (one << at), at + 1);
        comb(pool, need, chosen, at + 1);  /* or don't choose it, go to next */
    }
}
