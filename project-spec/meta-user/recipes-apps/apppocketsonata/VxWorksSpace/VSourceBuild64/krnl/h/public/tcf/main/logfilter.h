/*******************************************************************************
 * Copyright (c) 2014 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

#ifndef D_filter
#define D_filter

#include <tcf/framework/channel.h>

extern int filter_add_message_filter(const char * filter);
extern int filter_is_log_filtered(Channel * src, Channel * dst, int argc,
        char ** argv, int *limit) ;

#endif /* D_filter */
