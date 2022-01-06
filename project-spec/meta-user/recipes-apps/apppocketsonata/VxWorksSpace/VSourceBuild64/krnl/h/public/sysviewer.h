/* sysviewer.h - header of System Viewer TCF service */

/*
 * Copyright (c) 2012-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef SYSVIEWER_H
#define SYSVIEWER_H
#define SYSTEM_VIEWER "SystemViewer"
#include <tcf/framework/protocol.h>
extern void ini_sysviewer_service(Protocol *proto);
#endif
