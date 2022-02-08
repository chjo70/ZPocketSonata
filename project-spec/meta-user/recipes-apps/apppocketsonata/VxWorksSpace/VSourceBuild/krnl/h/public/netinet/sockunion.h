/* sockunion.h -File Transfer Protocol library header */

/*
modification history
--------------------
01g,09jan12,h_x  Move extern "C" after last header file include.
01f,24apr07,tkf  Add IPv6-Only build support.
01e,07jan05,syy  Port to RTP
01d,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01c,04nov03,rlm  Ran batch header path update for header re-org.
01b,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01a,15sep02,ant  written

*/

#ifndef __INCsockunionh
#define __INCsockunionh

/* includes */

#include <netinet/in.h> 

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

union sockunion {
	struct sockinet {
		u_char	si_len;
		u_char	si_family;
		u_short	si_port;
	} su_si;
#ifdef INET
	struct	sockaddr_in  su_sin;
#endif
#ifdef INET6
	struct	sockaddr_in6 su_sin6;
#endif
};
#define	su_len		su_si.si_len
#define	su_family	su_si.si_family
#define	su_port		su_si.si_port

#ifdef __cplusplus
}
#endif

#endif /* __INCsockunionh */
