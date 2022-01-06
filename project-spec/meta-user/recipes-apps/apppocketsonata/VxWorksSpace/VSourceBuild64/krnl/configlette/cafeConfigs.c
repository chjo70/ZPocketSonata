/* Copyright (c) 2010-2012, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
13jan15,tle  Add vxworks_polling event processor (US11628)
11mar14,sdt  Fix 'Checked Return' warning
*/

/*
DESCRIPTION

*/

#include <vxWorks.h>
#include <hpc/hpc_ep.h>
#include <vxworks/cafe_vx_types.h>


#define CAFE_CHECK_EP_REGISTER_ERROR(epName, rc)			\
	if (rc != CAFE_OK) {						\
		logMsg("Registration of %s EP failed: %s: %s\n",	\
		       (_Vx_usr_arg_t) epName,				\
		       (_Vx_usr_arg_t) __func__,			\
		       (_Vx_usr_arg_t) cafe_strerror(rc),		\
		       0,0,0);						\
	}

#ifdef INCLUDE_CAFE_EP_REALTIME
void realTimeCfgRegister(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_realtime_ep_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Realtime", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_TIMESTAMP_NORMALIZER
void timestampNormalizerCfgRegister(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_timestamp_normalizer_ep_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Timestamp Normalizer", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_TIMER
void cafeTimerRegister(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_timer_ep_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Timer", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_PRINT
void cafePrintRegister(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_print_configuration_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Print", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_STREAM_WRITER
void cafeFstreamWriterInit(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_fstream_writer_cfg_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Stream Writer", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_AGGREGATOR
void cafeAggregatorInit(void)
{
	int rc;
	
	CAFE_LOCK();
	symresolve_aggregator_ini();
	rc = cafe_aggregator_ep_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Aggregator", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_STREAM_READER
void cafeFstreamReaderInit(void)
{
	int rc;
	
	CAFE_LOCK();
	rc = cafe_fstream_reader_cfg_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Stream Reader", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_SYSINFO
void cafeSysinfoInit(void)
{
	int rc;

	CAFE_LOCK();
	rc = sysinfo_cfg_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("System Info", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_TCF_UPLOAD
void cafeTcfUploadInit(void)
{
	int rc;

	CAFE_LOCK();
	rc = cafe_tcf_upload_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("Tcf Upload", rc);
}
#endif

#ifdef INCLUDE_CAFE_EP_VXWORKS_POLLING
void cafeVxWorksPollingInit(void)
{
	int rc;

	CAFE_LOCK();
	rc = cafe_vxworks_polling_register();
	CAFE_UNLOCK();
	CAFE_CHECK_EP_REGISTER_ERROR("VxWorks Polling", rc);
}
#endif
