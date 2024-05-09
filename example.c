#include "ops_limiter.h"

int main(){
	struct ops_limiter_T *o=ops_limiter_new(10,10);
	for (int i=1;i<1000;i++) {
		printf("%d\n",i);
		ops_limiter_run(o);
	}
}