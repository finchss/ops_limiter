#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ops_limiter.h"

struct ops_limiter_T *ops_limiter_new(uint64_t intervals, uint64_t ops) {
	struct ops_limiter_T *ret=malloc(  sizeof(struct ops_limiter_T));
	memset(ret,0,sizeof(struct  ops_limiter_T));
	ret->intervals = intervals;
	ret->ops = ops;
	ret->ppi = ret->ops / intervals;
	ZenTimerStart(&ret->zt);
	return ret;
}
