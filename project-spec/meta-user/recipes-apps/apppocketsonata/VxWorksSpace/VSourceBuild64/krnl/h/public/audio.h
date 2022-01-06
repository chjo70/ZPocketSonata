/*
 * Header file for audio drivers
 */
#ifndef NTP_AUDIO_H
#define NTP_AUDIO_H
#include "ntp_types.h"

#define MAXGAIN		255	/* max codec gain */
#define	MONGAIN		127	/* codec monitor gain */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function prototypes
 */
int	audio_init		(const char *, int, int);
int	audio_gain		(int, int, int);
void	audio_show		(void);
#ifdef __cplusplus
}
#endif

#endif
