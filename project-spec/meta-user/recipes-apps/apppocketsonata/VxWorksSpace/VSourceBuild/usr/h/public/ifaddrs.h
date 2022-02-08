/* Copyright 2011 Wind River Systems, Inc. */

/*
 * <ifaddrs.h> the proper location for ifaddrs.h according to
 * POSIX.1-2001. VxWorks has historically defined getifaddrs() and
 * freeifaddrs() in <net/ifaddrs.h>. Both locations is available to
 * ensure backwards compatibility.
 */
#include "net/ifaddrs.h"
