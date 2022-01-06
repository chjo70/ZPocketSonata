Symbol .TOC. {
}
Symbol errnoSet {
}
Symbol malloc {
}
Symbol semCCreate {
}
Symbol strncpy {
}
Symbol erfEventTaskStackSize {
}
Symbol erfEventTaskOptions {
}
Symbol taskSpawn {
}
Symbol semDelete {
}
Symbol free {
}
Symbol erfLibInit {
}
Symbol erfLibInitialized {
}
Symbol erfMaxNumCat {
}
Symbol erfMaxNumUserType {
}
Symbol erfMaxNumType {
}
Symbol erfMaxNumUserCat {
}
Symbol erfNumUserCatDef {
}
Symbol spinLockIsrInit {
}
Symbol erfHandlerDb {
}
Symbol erfDbCatSem {
}
Symbol semMCreate {
}
Symbol erfCatDefSem {
}
Symbol erfNumUserTypeDef {
}
Symbol erfCatEventQueues {
}
Symbol erfEventTaskPriority {
}
Symbol erfEventQueueSize {
}
Symbol erfDefaultEventQueue {
}
Symbol erfHandlerRegister {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol erfHandlerUnregister {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol erfCategoryQueueCreate {
}
Symbol erfCategoriesAvailable {
}
Symbol erfTypesAvailable {
}
Symbol spinLockIsrTake {
}
Symbol memcpy {
}
Symbol spinLockIsrGive {
}
Symbol erfEventRaise {
}
Symbol erfShow {
}
Symbol printf {
}
Symbol erfMaxCategoriesGet {
}
Symbol erfMaxTypesGet {
}
Symbol erfDefaultQueueSizeGet {
}
ObjectFile liberfLib.a::erfLib.o {
	NAME Object file erfLib.o from archive liberfLib.a
	EXPORTS erfEventTaskStackSize erfEventTaskOptions erfLibInit erfLibInitialized erfEventTaskPriority erfEventQueueSize erfHandlerRegister erfHandlerUnregister erfCategoryAllocate erfTypeAllocate erfCategoryQueueCreate erfCategoriesAvailable erfTypesAvailable erfEventRaise
	IMPORTS .TOC. errnoSet malloc semCCreate strncpy taskSpawn semDelete free spinLockIsrInit semMCreate semTake semGive spinLockIsrTake memcpy spinLockIsrGive
	DECLARES erfMaxNumCat erfMaxNumUserType erfMaxNumType erfMaxNumUserCat erfNumUserCatDef erfHandlerDb erfDbCatSem erfCatDefSem erfNumUserTypeDef erfCatEventQueues erfDefaultEventQueue
	USES 
}
Module erfLib.o {
	OBJECT += liberfLib.a::erfLib.o
}
ObjectFile liberfLib.a::erfShow.o {
	NAME Object file erfShow.o from archive liberfLib.a
	EXPORTS erfShow erfMaxCategoriesGet erfMaxTypesGet erfDefaultQueueSizeGet
	IMPORTS .TOC. printf erfLibInitialized erfMaxNumCat erfMaxNumType erfMaxNumUserCat erfMaxNumUserType erfNumUserCatDef erfHandlerDb erfDefaultEventQueue erfEventQueueSize erfEventTaskPriority erfEventTaskOptions erfEventTaskStackSize erfCatEventQueues
	DECLARES 
	USES 
}
Module erfShow.o {
	OBJECT += liberfLib.a::erfShow.o
}
Library liberfLib.a {
	MODULES liberfLib.a::erfLib.o liberfLib.a::erfShow.o
}
Symbol .TOC. {
}
Symbol errnoSet {
}
Symbol malloc {
}
Symbol semCCreate {
}
Symbol strncpy {
}
Symbol erfEventTaskStackSize {
}
Symbol erfEventTaskOptions {
}
Symbol taskSpawn {
}
Symbol semDelete {
}
Symbol free {
}
Symbol erfLibInit {
}
Symbol erfLibInitialized {
}
Symbol erfMaxNumCat {
}
Symbol erfMaxNumUserType {
}
Symbol erfMaxNumType {
}
Symbol erfMaxNumUserCat {
}
Symbol erfNumUserCatDef {
}
Symbol spinLockIsrInit {
}
Symbol erfHandlerDb {
}
Symbol erfDbCatSem {
}
Symbol semMCreate {
}
Symbol erfCatDefSem {
}
Symbol erfNumUserTypeDef {
}
Symbol erfCatEventQueues {
}
Symbol erfEventTaskPriority {
}
Symbol erfEventQueueSize {
}
Symbol erfDefaultEventQueue {
}
Symbol erfHandlerRegister {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol erfHandlerUnregister {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol erfCategoryQueueCreate {
}
Symbol erfCategoriesAvailable {
}
Symbol erfTypesAvailable {
}
Symbol spinLockIsrTake {
}
Symbol memcpy {
}
Symbol spinLockIsrGive {
}
Symbol erfEventRaise {
}
Symbol erfShow {
}
Symbol printf {
}
Symbol erfMaxCategoriesGet {
}
Symbol erfMaxTypesGet {
}
Symbol erfDefaultQueueSizeGet {
}
ObjectFile liberfLib.a::erfLib.o {
	NAME Object file erfLib.o from archive liberfLib.a
	EXPORTS erfEventTaskStackSize erfEventTaskOptions erfLibInit erfLibInitialized erfEventTaskPriority erfEventQueueSize erfHandlerRegister erfHandlerUnregister erfCategoryAllocate erfTypeAllocate erfCategoryQueueCreate erfCategoriesAvailable erfTypesAvailable erfEventRaise
	IMPORTS .TOC. errnoSet malloc semCCreate strncpy taskSpawn semDelete free spinLockIsrInit semMCreate semTake semGive spinLockIsrTake memcpy spinLockIsrGive
	DECLARES erfMaxNumCat erfMaxNumUserType erfMaxNumType erfMaxNumUserCat erfNumUserCatDef erfHandlerDb erfDbCatSem erfCatDefSem erfNumUserTypeDef erfCatEventQueues erfDefaultEventQueue
	USES 
}
Module erfLib.o {
	OBJECT += liberfLib.a::erfLib.o
}
ObjectFile liberfLib.a::erfShow.o {
	NAME Object file erfShow.o from archive liberfLib.a
	EXPORTS erfShow erfMaxCategoriesGet erfMaxTypesGet erfDefaultQueueSizeGet
	IMPORTS .TOC. printf erfLibInitialized erfMaxNumCat erfMaxNumType erfMaxNumUserCat erfMaxNumUserType erfNumUserCatDef erfHandlerDb erfDefaultEventQueue erfEventQueueSize erfEventTaskPriority erfEventTaskOptions erfEventTaskStackSize erfCatEventQueues
	DECLARES 
	USES 
}
Module erfShow.o {
	OBJECT += liberfLib.a::erfShow.o
}
Library liberfLib.a {
	MODULES liberfLib.a::erfLib.o liberfLib.a::erfShow.o
}
Symbol .TOC. {
}
Symbol errnoSet {
}
Symbol malloc {
}
Symbol semCCreate {
}
Symbol strncpy {
}
Symbol erfEventTaskStackSize {
}
Symbol erfEventTaskOptions {
}
Symbol taskSpawn {
}
Symbol semDelete {
}
Symbol free {
}
Symbol erfLibInit {
}
Symbol erfLibInitialized {
}
Symbol erfMaxNumCat {
}
Symbol erfMaxNumUserType {
}
Symbol erfMaxNumType {
}
Symbol erfMaxNumUserCat {
}
Symbol erfNumUserCatDef {
}
Symbol spinLockIsrInit {
}
Symbol erfHandlerDb {
}
Symbol erfDbCatSem {
}
Symbol semMCreate {
}
Symbol erfCatDefSem {
}
Symbol erfNumUserTypeDef {
}
Symbol erfCatEventQueues {
}
Symbol erfEventTaskPriority {
}
Symbol erfEventQueueSize {
}
Symbol erfDefaultEventQueue {
}
Symbol erfHandlerRegister {
}
Symbol semTake {
}
Symbol semGive {
}
Symbol erfHandlerUnregister {
}
Symbol erfCategoryAllocate {
}
Symbol erfTypeAllocate {
}
Symbol erfCategoryQueueCreate {
}
Symbol erfCategoriesAvailable {
}
Symbol erfTypesAvailable {
}
Symbol spinLockIsrTake {
}
Symbol memcpy {
}
Symbol spinLockIsrGive {
}
Symbol erfEventRaise {
}
Symbol erfShow {
}
Symbol printf {
}
Symbol erfMaxCategoriesGet {
}
Symbol erfMaxTypesGet {
}
Symbol erfDefaultQueueSizeGet {
}
ObjectFile liberfLib.a::erfLib.o {
	NAME Object file erfLib.o from archive liberfLib.a
	EXPORTS erfEventTaskStackSize erfEventTaskOptions erfLibInit erfLibInitialized erfEventTaskPriority erfEventQueueSize erfHandlerRegister erfHandlerUnregister erfCategoryAllocate erfTypeAllocate erfCategoryQueueCreate erfCategoriesAvailable erfTypesAvailable erfEventRaise
	IMPORTS .TOC. errnoSet malloc semCCreate strncpy taskSpawn semDelete free spinLockIsrInit semMCreate semTake semGive spinLockIsrTake memcpy spinLockIsrGive
	DECLARES erfMaxNumCat erfMaxNumUserType erfMaxNumType erfMaxNumUserCat erfNumUserCatDef erfHandlerDb erfDbCatSem erfCatDefSem erfNumUserTypeDef erfCatEventQueues erfDefaultEventQueue
	USES 
}
Module erfLib.o {
	OBJECT += liberfLib.a::erfLib.o
}
ObjectFile liberfLib.a::erfShow.o {
	NAME Object file erfShow.o from archive liberfLib.a
	EXPORTS erfShow erfMaxCategoriesGet erfMaxTypesGet erfDefaultQueueSizeGet
	IMPORTS .TOC. printf erfLibInitialized erfMaxNumCat erfMaxNumType erfMaxNumUserCat erfMaxNumUserType erfNumUserCatDef erfHandlerDb erfDefaultEventQueue erfEventQueueSize erfEventTaskPriority erfEventTaskOptions erfEventTaskStackSize erfCatEventQueues
	DECLARES 
	USES 
}
Module erfShow.o {
	OBJECT += liberfLib.a::erfShow.o
}
Library liberfLib.a {
	MODULES liberfLib.a::erfLib.o liberfLib.a::erfShow.o
}
