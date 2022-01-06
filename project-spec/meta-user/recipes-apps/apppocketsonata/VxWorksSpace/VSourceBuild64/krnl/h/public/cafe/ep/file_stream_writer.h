/* file_stream_writer.h - configuration used to tee events to a file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__file_stream_writer_h)
#define __file_stream_writer_h

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_fstream_writer_cfg_register(void);
extern void cafe_fstream_writer_cfg_unregister(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif  /* if !defined(__file_stream_writer_h) */
