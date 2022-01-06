/* spec.h - public api for cafe configuration specifications */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCspec_h
#define INCspec_h

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*
* cafe_ep_spec_find - find a Cafe configuration specification by name
*
* This routine takes a name, and finds a matching Cafe configuration
* specification, if one exists.
*
* RETURNS: Pointer to cafe_ep_spec, or NULL
*
* ERRNO:
*/
extern struct cafe_ep_spec *cafe_ep_spec_find
	(
	const char *name	/* name to find */
	);

extern struct cafe_ep_spec *cafe_ep_spec_iter_first
	(
	struct cafe_ep_spec_iter *iter /* iterator instance */
	);

extern struct cafe_ep_spec *cafe_ep_spec_iter_next
	(
	struct cafe_ep_spec_iter *iter /* iterator instance */
	);

/*******************************************************************************
*
* cafe_ep_spec_register - register a configuration with the Cafe system
*
* This function registers a Cafe configuration specification with the Cafe
* system. Until this is done, a configuration will not be available to use.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_spec_register
	(
	struct cafe_ep_spec *spec /* specification to register */
	);

/*******************************************************************************
*
* cafe_ep_spec_unregister - unregister a configuration with the Cafe system
*
* This function unregisters a Cafe configuration specification with the Cafe
* system.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_spec_unregister
	(
	struct cafe_ep_spec *spec /* specification to unregister */
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCspec_h */
