/* file_stream_reader.h - configuration for firing events from a file */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__file_stream_reader_h)
#define __file_stream_reader_h

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_fstream_reader_cfg_register(void);
extern void cafe_fstream_reader_cfg_unregister(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif  /* if !defined(__file_stream_reader_h) */
