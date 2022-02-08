/* time.h - header file for time definitions/functions */

/*
* Copyright (c) 2011 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01a,15oct11,jpb  written
*/

#ifndef __INCsys_timeh
#define __INCsys_timeh

#ifdef __cplusplus
extern "C" {
#endif

struct timeval
    {
    long tv_sec;        /* seconds */
    long tv_usec;       /* microseconds */
    };

struct timezone
    {
    int tz_minuteswest; /* minutes west of Greenwich */
    int tz_dsttime;     /* type of dst correction */
    };

struct itimerval 
    {
    struct timeval it_interval;
    struct timeval it_value;
    };

/* function declarations */

int gettimeofday (struct timeval * timep, void * tmz);
int settimeofday (struct timeval * timep, void * tmz);

#ifdef __cplusplus
}
#endif

#endif /* __INCsys_timeh */
