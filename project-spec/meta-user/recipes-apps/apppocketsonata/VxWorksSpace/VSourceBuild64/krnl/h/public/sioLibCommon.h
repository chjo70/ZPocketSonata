/* Header file for SIO serial drivers ioctl control, used by
   both kernel and RTP user side. */

/*
 * Copyright 2005-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,13apr09,h_k  added SIO_DEV_LOCK and SIO_DEV_UNLOCK commands. (CQ:158523)
01a,22mar05,hya  created from target/h/sioLib.h.
*/

#ifndef __INCsioLibCommonh
#define __INCsioLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

/* serial device I/O controls */

#define SIO_BAUD_SET		0x1003
#define SIO_BAUD_GET		0x1004

#define SIO_HW_OPTS_SET		0x1005
#define SIO_HW_OPTS_GET		0x1006

#define SIO_MODE_SET		0x1007
#define SIO_MODE_GET		0x1008
#define SIO_AVAIL_MODES_GET	0x1009

/* These are used to communicate open/close between layers */

#define SIO_OPEN		0x100A 
#define SIO_HUP			0x100B

/*
 * The ioctl commands listed below provide a way for reading and
 * setting the modem lines. 
 * 
 * SIO_MSTAT_GET: returns status of all input and output modem signals.
 * SIO_MCTRL_BITS_SET: sets modem signals specified in argument.
 * SIO_MCTRL_BITS_CLR: clears modem signal(s) specified in argument.
 * SIO_MCTRL_ISIG_MASK: returns mask of all input modem signals.
 * SIO_MCTRL_OSIG_MASK: returns mask of all output(writable) modem signals.
 */

#define SIO_MSTAT_GET           0x100C  /* get modem status lines */
#define SIO_MCTRL_BITS_SET      0x100D  /* set selected modem lines */
#define SIO_MCTRL_BITS_CLR      0x100E  /* clear selected modem lines  */
#define SIO_MCTRL_ISIG_MASK     0x100F  /* mask of lines that can be read */
#define SIO_MCTRL_OSIG_MASK     0x1010  /* mask of lines that can be set */

/* Ioctl cmds for reading/setting keyboard mode */

#define SIO_KYBD_MODE_SET       0x1011
#define SIO_KYBD_MODE_GET       0x1012


/* Ioctl cmds for reading/setting keyboard led state */

#define SIO_KYBD_LED_SET       0x1013
#define SIO_KYBD_LED_GET       0x1014

/*
 * Ioctl cmds for taking/giving local ISR spinlock.
 * The cmds are available only in SMP mode.
 */

#define SIO_DEV_LOCK           0x1015
#define SIO_DEV_UNLOCK         0x1016

/* options to SIO_MODE_SET */

#define	SIO_MODE_POLL	1
#define	SIO_MODE_INT	2

/* options to SIO_HW_OPTS_SET (ala POSIX), bitwise or'ed together */

#define CLOCAL		0x1	/* ignore modem status lines */
#define CREAD		0x2	/* enable device reciever */

#define CSIZE		0xc	/* bits 3 and 4 encode the character size */
#define CS5		0x0	/* 5 bits */
#define CS6		0x4	/* 6 bits */
#define CS7		0x8	/* 7 bits */
#define CS8		0xc	/* 8 bits */

#define HUPCL		0x10	/* hang up on last close */
#define STOPB		0x20	/* send two stop bits (else one) */
#define PARENB		0x40	/* parity detection enabled (else disabled) */
#define PARODD		0x80	/* odd parity  (else even) */

/* 
 * Modem signals definitions 
 *
 * The following six macros define the different modem signals. They
 * are used as arguments to the modem ioctls commands to specify 
 * the signals to read(set) and also to parse the returned value. They
 * provide hardware independence, as modem signals bits vary from one 
 * chip to another.      
 */

#define SIO_MODEM_DTR   0x01    /* data terminal ready */
#define SIO_MODEM_RTS   0x02    /* request to send */
#define SIO_MODEM_CTS   0x04    /* clear to send */
#define SIO_MODEM_CD    0x08    /* carrier detect */
#define SIO_MODEM_RI    0x10    /* ring */
#define SIO_MODEM_DSR   0x20    /* data set ready */

/*
 * options to SIO_KYBD_MODE_SET 
 *
 * These macros are used as arguments by the keyboard ioctl comands.
 * When used with SIO_KYBD_MODE_SET they mean the following:
 * 
 * SIO_KYBD_MODE_RAW:
 *    Requests the keyboard driver to return raw key values as read
 *    by the keyboard controller.
 * 
 * SIO_KYBD_MODE_ASCII:
 *    Requests the keyboard driver to return ASCII codes read from a
 *    known table that maps raw key values to ASCII.
 *
 * SIO_KYBD_MODE_UNICODE:
 *    Requests the keyboard driver to return 16 bit UNICODE values for
 *    multiple languages support.
 */

#define SIO_KYBD_MODE_RAW     1
#define SIO_KYBD_MODE_ASCII   2
#define SIO_KYBD_MODE_UNICODE 3

/*
 * options to SIO_KYBD_LED_SET 
 *
 * These macros are used as arguments by the keyboard ioctl comands.
 * When used with SIO_KYBD_LED_SET they mean the following:
 * 
 * SIO_KYBD_LED_NUM:
 *    Sets the Num Lock LED on the keyboard - bit 1
 * 
 * SIO_KYBD_LED_CAP:
 *    Sets the Caps Lock LED on the keyboard - bit 2
 *
 * SIO_KYBD_LED_SRC:
 *    Sets the Scroll Lock LED on the keyboard - bit 4
 */

#define SIO_KYBD_LED_NUM	1
#define SIO_KYBD_LED_CAP	2
#define SIO_KYBD_LED_SCR	4

#ifdef __cplusplus
}
#endif

#endif  /* __INCsioLibCommonh */
