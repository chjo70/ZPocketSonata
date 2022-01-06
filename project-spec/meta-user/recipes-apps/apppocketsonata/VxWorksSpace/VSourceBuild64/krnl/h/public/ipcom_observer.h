/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_OBSERVER_H
#define IPCOM_OBSERVER_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Implementation of the observer pattern. Used to observe state change
 * of a subject. The subject must declare an instance of
 * Ipcom_observer_subject and anything that want to receive
 * notification about changed to that subject registers with
 * ipcom_observer_add()
 *
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_cstyle.h>
#include <ipcom_list.h>
#include <ipcom_type.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                     Ipcom_observer_action
 *===========================================================================
 * Description: This function will be called when a subject calls
 *              ipcom_observer_notify() on itself.
 * Parameters:  subject - the subject being observed
 *              subject_ctx - context specific data accociated with the
 *                            subject. Example is a hint as to why/how the
 *                            subject has changed
 *              observer_ctx - context specific data accociated with the
 *                             observer.
 * Returns:
 *
 */
typedef void (*Ipcom_observer_action) (void *subject,
                                       void *subject_ctx,
                                       void *observer_ctx);

typedef struct Ipcom_observer_struct
{
    /*
     * List of observers on a specific subject
     */
    Ipcom_list            list;
    /*
     * Function that will be called when the subject calls
     * ipcom_object_notify()
     */
    Ipcom_observer_action action;
    /*
     * Observer define data that will be passed to action().
     */
    void                 *ctx;
} Ipcom_observer;


/*
 * Each observable subject must have an instance of
 * Ipcom_observer_collection.
 */
typedef Ipcom_list Ipcom_observer_collection;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                     ipcom_observer_collection_init
 *===========================================================================
 * Description: Initializes the observer collection on the subject.
 * Parameters:  observers - observer collection
 * Returns:
 *
 */
IP_INLINE void
ipcom_observer_collection_init(Ipcom_observer_collection *observers)
{
    ipcom_list_init((Ipcom_list *) observers);
}


/*
 *===========================================================================
 *                           ipcom_observer_add
 *===========================================================================
 * Description: Adds a observer to the subject that owns the observer list.
 * Parameters:  observers -
 *              observer - pointer to where the observer information
 *                         can be stored
 *              action - function to call when the subject what to notify
 *                       its observer
 *              observer_ctx - observer defined context specific data
 * Returns:
 *
 */
IP_INLINE void
ipcom_observer_add(Ipcom_observer_collection *observers,
                   Ipcom_observer *observer,
                   void *observer_ctx,
                   Ipcom_observer_action action)
{
    observer->action = action;
    observer->ctx    = observer_ctx;
    ipcom_list_insert_last((Ipcom_list *)observers, &observer->list);
}


/*
 *===========================================================================
 *                         ipcom_observer_remove
 *===========================================================================
 * Description: Removes an observer from its subject
 * Parameters:  observers - collection of observers
 *              observer - the observer handle passed to ipcom_observer_add()
 * Returns:
 *
 */
IP_INLINE void
ipcom_observer_remove(Ipcom_observer_collection *observers,
                      Ipcom_observer *observer)
{
    IPCOM_UNUSED_ARG(observers);
    ipcom_list_remove(&observer->list);
}


IP_GLOBAL void ipcom_observer_notify(Ipcom_observer_collection *observers,
                                     void *subject,
                                     void *subject_ctx);

#ifdef __cplusplus
}
#endif

#endif /* !IPCOM_OBSERVER_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
