/* usrSerial.c - serial device configuration file */

/*
 * Copyright (c) 1984-2004, 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15jul14,h_k  Got rid of the loop from usrSerialInit(). (V7COR-860)
04jun14,wap  Correct issues uncovered by static analysis (V7COR-1242)
03mar14,cww  check return values (US29395)
15jan14,cww  merged in support for non _WRS_CONFIG_VXBUS_LEGACY
06dec13,xms  fix STRING_OVERFLOW error. (WIND00414265)
30apr04,dat  fix itos code warnings, remove unnecessary casts (96786)
24feb99,pr   added control for PC_CONSOLE in IO initialization (SPR#23075)
11oct97,ms   use itos instead of sprintf to break dependecy on fioLib
09oct97,ms   taken from usrConfig.c
*/

/*
DESCRIPTION

User configurable serial device intialization.
*/

#define	TY_NAME_BASE	"/tyCo/"

/******************************************************************************
*
* itos - given an integer, return a string representing it.
*/

static char * itos (unsigned int val)
    {
    static char str [20];
    char * pChar;

    if (val == 0)
	return "0";

    pChar = & str[19];
    *pChar = '\0';

    while (val != 0)
	{
	*--pChar = '0' + (val % 10);
	val /= 10;
	}

    return pChar;
    }

/******************************************************************************
*
* usrSerialInit - initialize the serial ports
*/

STATUS usrSerialInit (void)
    {
    STATUS	 status = OK;
    char	 tyName [20];

#ifdef _WRS_CONFIG_VXBUS_LEGACY
    unsigned int ix;

    if ((NUM_TTY > 0))
	{
	for (ix = 0; ix < NUM_TTY; ix++)	/* create serial devices */
	    {
	    tyName[0] = '\0';
	    strncat (tyName, TY_NAME_BASE, sizeof (tyName) - 1);
	    strncat (tyName, itos (ix), (sizeof(tyName) - 1) - strlen (tyName));

	    if (ttyDevCreate (tyName, sysSerialChanGet(ix), 512, 512) != OK)
		status = ERROR;

#if  (!(defined(INCLUDE_PC_CONSOLE)))

	    if ((ix == CONSOLE_TTY))		/* init the tty console */
		{
		consoleFd = open (tyName, O_RDWR, 0);
		(void) ioctl (consoleFd, FIOBAUDRATE, CONSOLE_BAUD_RATE);
		(void) ioctl (consoleFd, FIOSETOPTIONS, OPT_TERMINAL);
		}
#endif /* INCLUDE_PC_CONSOLE */

	    }
	}
#elif !(defined(INCLUDE_PC_CONSOLE))
    tyName[0] = '\0';
    strncat (tyName, TY_NAME_BASE, sizeof (tyName) - 1);
    strncat (tyName, itos (CONSOLE_TTY),
	     (sizeof(tyName) - 1) - strlen (tyName));

    /* init the tty console */

    consoleFd = open (tyName, O_RDWR, 0);

    if (consoleFd < 0)
	return (ERROR);

    (void) ioctl (consoleFd, FIOBAUDRATE, CONSOLE_BAUD_RATE);
    (void) ioctl (consoleFd, FIOSETOPTIONS, OPT_TERMINAL);
#endif /* _WRS_CONFIG_VXBUS_LEGACY */

    ioGlobalStdSet (STD_IN,  consoleFd);
    ioGlobalStdSet (STD_OUT, consoleFd);
    ioGlobalStdSet (STD_ERR, consoleFd);

    return status;
    }
