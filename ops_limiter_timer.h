/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*  ZenTimer
 *  Copyright (C) 2001-2009 Jeffrey Stedfast
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 */


#ifndef OPS_LIMITER_TIMER_H__
#define OPS_LIMITER_TIMER_H__
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>



#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus */

#define OPS_ZTIME_USEC_PER_SEC 1000000

/* ops_ztime_t represents usec */
typedef uint64_t ops_ztime_t;



static void ops_ztime (ops_ztime_t *ztimep){

	struct timeval tv;

	gettimeofday (&tv, NULL);

	*ztimep = ((uint64_t) tv.tv_sec * OPS_ZTIME_USEC_PER_SEC) + tv.tv_usec;
}

enum {
	ops_ZTIMER_INACTIVE = 0,
	ops_ZTIMER_ACTIVE   = (1 << 0),
	ops_ZTIMER_PAUSED   = (1 << 1),
};

typedef uint32_t ops_zstat_t;

typedef struct {
	ops_ztime_t start;
	ops_ztime_t stop;
	ops_zstat_t state;
} ops_ztimer_t;

#define OPS_ZTIMER_INITIALIZER { 0, 0, 0 }

static void ops_ZenTimerStart (ops_ztimer_t *ztimer) {

	ztimer->state = ops_ZTIMER_ACTIVE;
	ops_ztime(&ztimer->start);

}

static void ops_ZenTimerStop (ops_ztimer_t *ztimer) {

	ops_ztime(&ztimer->stop);
	ztimer->state = ops_ZTIMER_INACTIVE;

}

static double ops_ZenTimerElapsed (ops_ztimer_t *ztimer, uint64_t *usec){

	#define freq OPS_ZTIME_USEC_PER_SEC
	ops_ztime_t delta, stop;

	if (ztimer->state != ops_ZTIMER_ACTIVE)
		stop = ztimer->stop;
	else
		ops_ztime(&stop);

	delta = stop - ztimer->start;

	if (usec != NULL)
		*usec = (uint64_t) (delta * ((double) OPS_ZTIME_USEC_PER_SEC / (double) freq));

	return (double) delta / (double) freq;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
