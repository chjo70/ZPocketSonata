/*	Definition module : synclib.h

	Copyright 1995 Diab Data AB, Sweden

	Description :
	Real-time Operating System stubs.

	History :
	When	Who	What
	951116  fb	initial
	991029	kc	new file name: synclib.h
*/

/**************	Exported data, types and macros	*********/

/**************	Exported functions **********************/

#ifdef	__cplusplus
extern "C" {
#endif

typedef unsigned long __diab_atomic_level;
typedef struct __diab_mutex_struct *__diab_mutex;
#ifndef _YVALS
typedef struct __diab_semaphore_struct *__diab_semaphore;
#endif

/* "atomic lock" stops task preemption by
 * disabling interrupts or turning off scheduler.
 * It should never re-schedule current task.
 * Important: atomic lock should NOT be implemented using mutex or semaphore!
 */
extern __diab_atomic_level __diab_atomic_enter(void);
extern void __diab_atomic_restore(__diab_atomic_level);

/* if "mutex" is locked __diab_lock_mutex() waits until it is unlocked.
 * "mutex" is not recursive, e.g. a task can not lock it multiple times without unlocking.
 */
extern __diab_mutex __diab_alloc_mutex(void);
extern void __diab_free_mutex(__diab_mutex);
extern void __diab_lock_mutex(__diab_mutex);
extern int __diab_trylock_mutex(__diab_mutex);
extern void __diab_unlock_mutex(__diab_mutex);

/* "semaphore" is similar to "mutex",
 * but allows multiple locking by same task before unlocking.
 * Locking calls are conuted and must be followed by same number of unlocking calls.
 */
extern __diab_semaphore __diab_alloc_semaphore(void);
extern void __diab_free_semaphore(__diab_semaphore);
extern void __diab_lock_semaphore(__diab_semaphore);
extern int __diab_trylock_semaphore(__diab_semaphore);
extern void __diab_unlock_semaphore(__diab_semaphore);

#ifdef	__cplusplus
}
#endif
