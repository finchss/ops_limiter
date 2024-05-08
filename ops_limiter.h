#ifndef OPS_LIMITER_OPS_LIMITER_H

#include <stdint.h>
#include <unistd.h>
#include "zentimer.h"
struct ops_limiter_T {

	uint64_t ops;
	uint64_t total_ops;
	uint64_t ppi;
	uint64_t intervals;
	ztimer_t  zt;
};
struct ops_limiter_T *ops_limiter_new(uint64_t intervals, uint64_t pps);

#define ops_limiter_run(pplt) do { \
    (pplt)->total_ops++; \
    if ((pplt)->total_ops == (pplt)->ppi) { \
        uint64_t elapsed; \
        ZenTimerElapsed(&(pplt)->zt, &elapsed); \
        if (elapsed < (uint64_t) 1000000 / (uint64_t) (pplt)->intervals) { \
            uint64_t slt = (((uint64_t) 1000000 / (pplt)->intervals) - elapsed); \
            usleep(slt); \
        } \
        ZenTimerStart(&(pplt)->zt); \
        (pplt)->total_ops = 0; \
    } \
} while(0)


#endif //OPS_LIMITER_OPS_LIMITER_H
