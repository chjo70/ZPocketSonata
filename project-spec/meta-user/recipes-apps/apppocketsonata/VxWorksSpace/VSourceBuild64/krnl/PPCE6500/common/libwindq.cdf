Symbol qFifoInit {
}
Symbol .TOC. {
}
Symbol qFifoPut {
}
Symbol qFifoRestore {
}
Symbol qFifoGet {
}
Symbol qFifoRemove {
}
Symbol qFifoResort {
}
Symbol qFifoInfo {
}
Symbol dllCount {
}
Symbol qFifoEach {
}
Symbol qFifoNext {
}
Symbol qFifoClass {
}
Symbol qFifoClassId {
}
Symbol qPriBMapInit {
}
Symbol dllInit {
}
Symbol bzero {
}
Symbol qTradPriBMapSetCompatible {
}
Symbol qTradPriBMapClassId {
}
Symbol qPriBMapResort {
}
Symbol _func_qPriBMapNativeResort {
}
Symbol qPriBMapPut {
}
Symbol dllAdd {
}
Symbol qPriBMapRemove {
}
Symbol qPriBMapGet {
}
Symbol qPriBMapRestore {
}
Symbol dllInsert {
}
Symbol qPriBMapNext {
}
Symbol qPriBMapKey {
}
Symbol qPriBMapInfo {
}
Symbol qPriBMapEach {
}
Symbol qPriBMapSet {
}
Symbol qPriBMapClassId {
}
Symbol qPriDeltaInit {
}
Symbol qPriDeltaPut {
}
Symbol qPriDeltaGet {
}
Symbol qPriDeltaRemove {
}
Symbol qPriDeltaResort {
}
Symbol qPriDeltaAdvance {
}
Symbol qPriDeltaGetExpired {
}
Symbol qPriDeltaKey {
}
Symbol qPriDeltaInfo {
}
Symbol qPriDeltaEach {
}
Symbol qPriDeltaNext {
}
Symbol qPriDeltaClassId {
}
Symbol qPriListInit {
}
Symbol qTradPriListSetCompatible {
}
Symbol qTradPriListClassId {
}
Symbol qPriListResort {
}
Symbol qPriListPut {
}
Symbol qPriListPutFromTail {
}
Symbol qPriListGet {
}
Symbol dllGet {
}
Symbol qPriListRemove {
}
Symbol dllRemove {
}
Symbol qPriListKey {
}
Symbol qPriListInfo {
}
Symbol qPriListEach {
}
Symbol qPriListNext {
}
Symbol qPriListClassId {
}
Symbol qPriListFromTailClassId {
}
Symbol readyQNodeToTcb {
}
Symbol qPxPriBMapClassId {
}
Symbol pxSSThreadStateActive {
}
Symbol pxSSThreadStateBlock {
}
Symbol qPxSSPriBMapClassId {
}
ObjectFile libwindq.a::qFifoLib.o {
	NAME Object file qFifoLib.o from archive libwindq.a
	EXPORTS qFifoInit qFifoPut qFifoRestore qFifoGet qFifoRemove qFifoResort qFifoInfo qFifoEach qFifoNext qFifoClass qFifoClassId
	IMPORTS .TOC. dllCount
	DECLARES 
	USES 
}
Module qFifoLib.o {
	OBJECT += libwindq.a::qFifoLib.o
}
ObjectFile libwindq.a::qPriBMapLib.o {
	NAME Object file qPriBMapLib.o from archive libwindq.a
	EXPORTS qPriBMapInit qTradPriBMapSetCompatible qTradPriBMapClassId qPriBMapResort _func_qPriBMapNativeResort qPriBMapPut qPriBMapRemove qPriBMapGet qPriBMapRestore qPriBMapNext qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapSet qPriBMapClassId
	IMPORTS .TOC. dllInit bzero dllAdd dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriBMapLib.o {
	OBJECT += libwindq.a::qPriBMapLib.o
}
ObjectFile libwindq.a::qPriDeltaLib.o {
	NAME Object file qPriDeltaLib.o from archive libwindq.a
	EXPORTS qPriDeltaInit qPriDeltaPut qPriDeltaGet qPriDeltaRemove qPriDeltaResort qPriDeltaAdvance qPriDeltaGetExpired qPriDeltaKey qPriDeltaInfo qPriDeltaEach qPriDeltaNext qPriDeltaClassId
	IMPORTS .TOC. dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriDeltaLib.o {
	OBJECT += libwindq.a::qPriDeltaLib.o
}
ObjectFile libwindq.a::qPriListLib.o {
	NAME Object file qPriListLib.o from archive libwindq.a
	EXPORTS qPriListInit qTradPriListSetCompatible qTradPriListClassId qPriListResort qPriListPut qPriListPutFromTail qPriListGet qPriListRemove qPriListKey qPriListInfo qPriListEach qPriListNext qPriListClassId qPriListFromTailClassId
	IMPORTS .TOC. dllInsert dllGet dllRemove dllCount
	DECLARES 
	USES 
}
Module qPriListLib.o {
	OBJECT += libwindq.a::qPriListLib.o
}
ObjectFile libwindq.a::qPxPriBMapLib.o {
	NAME Object file qPxPriBMapLib.o from archive libwindq.a
	EXPORTS qPxPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut qPriBMapSet dllAdd dllInsert _func_qPriBMapNativeResort qPriBMapRemove qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxPriBMapLib.o {
	OBJECT += libwindq.a::qPxPriBMapLib.o
}
ObjectFile libwindq.a::qPxSSPriBMapLib.o {
	NAME Object file qPxSSPriBMapLib.o from archive libwindq.a
	EXPORTS qPxSSPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut pxSSThreadStateActive qPriBMapSet dllAdd dllInsert qPriBMapRemove pxSSThreadStateBlock _func_qPriBMapNativeResort qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxSSPriBMapLib.o {
	OBJECT += libwindq.a::qPxSSPriBMapLib.o
}
Library libwindq.a {
	MODULES libwindq.a::qFifoLib.o libwindq.a::qPriBMapLib.o libwindq.a::qPriDeltaLib.o libwindq.a::qPriListLib.o libwindq.a::qPxPriBMapLib.o libwindq.a::qPxSSPriBMapLib.o
}
Symbol qFifoInit {
}
Symbol .TOC. {
}
Symbol qFifoPut {
}
Symbol qFifoRestore {
}
Symbol qFifoGet {
}
Symbol qFifoRemove {
}
Symbol qFifoResort {
}
Symbol qFifoInfo {
}
Symbol dllCount {
}
Symbol qFifoEach {
}
Symbol qFifoNext {
}
Symbol qFifoClass {
}
Symbol qFifoClassId {
}
Symbol qPriBMapInit {
}
Symbol dllInit {
}
Symbol bzero {
}
Symbol qTradPriBMapSetCompatible {
}
Symbol qTradPriBMapClassId {
}
Symbol qPriBMapResort {
}
Symbol _func_qPriBMapNativeResort {
}
Symbol qPriBMapPut {
}
Symbol dllAdd {
}
Symbol qPriBMapRemove {
}
Symbol qPriBMapGet {
}
Symbol qPriBMapRestore {
}
Symbol dllInsert {
}
Symbol qPriBMapNext {
}
Symbol qPriBMapKey {
}
Symbol qPriBMapInfo {
}
Symbol qPriBMapEach {
}
Symbol qPriBMapSet {
}
Symbol qPriBMapClassId {
}
Symbol qPriDeltaInit {
}
Symbol qPriDeltaPut {
}
Symbol qPriDeltaGet {
}
Symbol qPriDeltaRemove {
}
Symbol qPriDeltaResort {
}
Symbol qPriDeltaAdvance {
}
Symbol qPriDeltaGetExpired {
}
Symbol qPriDeltaKey {
}
Symbol qPriDeltaInfo {
}
Symbol qPriDeltaEach {
}
Symbol qPriDeltaNext {
}
Symbol qPriDeltaClassId {
}
Symbol qPriListInit {
}
Symbol qTradPriListSetCompatible {
}
Symbol qTradPriListClassId {
}
Symbol qPriListResort {
}
Symbol qPriListPut {
}
Symbol qPriListPutFromTail {
}
Symbol qPriListGet {
}
Symbol dllGet {
}
Symbol qPriListRemove {
}
Symbol dllRemove {
}
Symbol qPriListKey {
}
Symbol qPriListInfo {
}
Symbol qPriListEach {
}
Symbol qPriListNext {
}
Symbol qPriListClassId {
}
Symbol qPriListFromTailClassId {
}
Symbol readyQNodeToTcb {
}
Symbol qPxPriBMapClassId {
}
Symbol pxSSThreadStateActive {
}
Symbol pxSSThreadStateBlock {
}
Symbol qPxSSPriBMapClassId {
}
ObjectFile libwindq.a::qFifoLib.o {
	NAME Object file qFifoLib.o from archive libwindq.a
	EXPORTS qFifoInit qFifoPut qFifoRestore qFifoGet qFifoRemove qFifoResort qFifoInfo qFifoEach qFifoNext qFifoClass qFifoClassId
	IMPORTS .TOC. dllCount
	DECLARES 
	USES 
}
Module qFifoLib.o {
	OBJECT += libwindq.a::qFifoLib.o
}
ObjectFile libwindq.a::qPriBMapLib.o {
	NAME Object file qPriBMapLib.o from archive libwindq.a
	EXPORTS qPriBMapInit qTradPriBMapSetCompatible qTradPriBMapClassId qPriBMapResort _func_qPriBMapNativeResort qPriBMapPut qPriBMapRemove qPriBMapGet qPriBMapRestore qPriBMapNext qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapSet qPriBMapClassId
	IMPORTS .TOC. dllInit bzero dllAdd dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriBMapLib.o {
	OBJECT += libwindq.a::qPriBMapLib.o
}
ObjectFile libwindq.a::qPriDeltaLib.o {
	NAME Object file qPriDeltaLib.o from archive libwindq.a
	EXPORTS qPriDeltaInit qPriDeltaPut qPriDeltaGet qPriDeltaRemove qPriDeltaResort qPriDeltaAdvance qPriDeltaGetExpired qPriDeltaKey qPriDeltaInfo qPriDeltaEach qPriDeltaNext qPriDeltaClassId
	IMPORTS .TOC. dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriDeltaLib.o {
	OBJECT += libwindq.a::qPriDeltaLib.o
}
ObjectFile libwindq.a::qPriListLib.o {
	NAME Object file qPriListLib.o from archive libwindq.a
	EXPORTS qPriListInit qTradPriListSetCompatible qTradPriListClassId qPriListResort qPriListPut qPriListPutFromTail qPriListGet qPriListRemove qPriListKey qPriListInfo qPriListEach qPriListNext qPriListClassId qPriListFromTailClassId
	IMPORTS .TOC. dllInsert dllGet dllRemove dllCount
	DECLARES 
	USES 
}
Module qPriListLib.o {
	OBJECT += libwindq.a::qPriListLib.o
}
ObjectFile libwindq.a::qPxPriBMapLib.o {
	NAME Object file qPxPriBMapLib.o from archive libwindq.a
	EXPORTS qPxPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut qPriBMapSet dllAdd dllInsert _func_qPriBMapNativeResort qPriBMapRemove qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxPriBMapLib.o {
	OBJECT += libwindq.a::qPxPriBMapLib.o
}
ObjectFile libwindq.a::qPxSSPriBMapLib.o {
	NAME Object file qPxSSPriBMapLib.o from archive libwindq.a
	EXPORTS qPxSSPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut pxSSThreadStateActive qPriBMapSet dllAdd dllInsert qPriBMapRemove pxSSThreadStateBlock _func_qPriBMapNativeResort qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxSSPriBMapLib.o {
	OBJECT += libwindq.a::qPxSSPriBMapLib.o
}
Library libwindq.a {
	MODULES libwindq.a::qFifoLib.o libwindq.a::qPriBMapLib.o libwindq.a::qPriDeltaLib.o libwindq.a::qPriListLib.o libwindq.a::qPxPriBMapLib.o libwindq.a::qPxSSPriBMapLib.o
}
Symbol qFifoInit {
}
Symbol .TOC. {
}
Symbol qFifoPut {
}
Symbol qFifoRestore {
}
Symbol qFifoGet {
}
Symbol qFifoRemove {
}
Symbol qFifoResort {
}
Symbol qFifoInfo {
}
Symbol dllCount {
}
Symbol qFifoEach {
}
Symbol qFifoNext {
}
Symbol qFifoClass {
}
Symbol qFifoClassId {
}
Symbol qPriBMapInit {
}
Symbol dllInit {
}
Symbol bzero {
}
Symbol qTradPriBMapSetCompatible {
}
Symbol qTradPriBMapClassId {
}
Symbol qPriBMapResort {
}
Symbol _func_qPriBMapNativeResort {
}
Symbol qPriBMapPut {
}
Symbol dllAdd {
}
Symbol qPriBMapRemove {
}
Symbol qPriBMapGet {
}
Symbol qPriBMapRestore {
}
Symbol dllInsert {
}
Symbol qPriBMapNext {
}
Symbol qPriBMapKey {
}
Symbol qPriBMapInfo {
}
Symbol qPriBMapEach {
}
Symbol qPriBMapSet {
}
Symbol qPriBMapClassId {
}
Symbol qPriDeltaInit {
}
Symbol qPriDeltaPut {
}
Symbol qPriDeltaGet {
}
Symbol qPriDeltaRemove {
}
Symbol qPriDeltaResort {
}
Symbol qPriDeltaAdvance {
}
Symbol qPriDeltaGetExpired {
}
Symbol qPriDeltaKey {
}
Symbol qPriDeltaInfo {
}
Symbol qPriDeltaEach {
}
Symbol qPriDeltaNext {
}
Symbol qPriDeltaClassId {
}
Symbol qPriListInit {
}
Symbol qTradPriListSetCompatible {
}
Symbol qTradPriListClassId {
}
Symbol qPriListResort {
}
Symbol qPriListPut {
}
Symbol qPriListPutFromTail {
}
Symbol qPriListGet {
}
Symbol dllGet {
}
Symbol qPriListRemove {
}
Symbol dllRemove {
}
Symbol qPriListKey {
}
Symbol qPriListInfo {
}
Symbol qPriListEach {
}
Symbol qPriListNext {
}
Symbol qPriListClassId {
}
Symbol qPriListFromTailClassId {
}
Symbol readyQNodeToTcb {
}
Symbol qPxPriBMapClassId {
}
Symbol pxSSThreadStateActive {
}
Symbol pxSSThreadStateBlock {
}
Symbol qPxSSPriBMapClassId {
}
ObjectFile libwindq.a::qFifoLib.o {
	NAME Object file qFifoLib.o from archive libwindq.a
	EXPORTS qFifoInit qFifoPut qFifoRestore qFifoGet qFifoRemove qFifoResort qFifoInfo qFifoEach qFifoNext qFifoClass qFifoClassId
	IMPORTS .TOC. dllCount
	DECLARES 
	USES 
}
Module qFifoLib.o {
	OBJECT += libwindq.a::qFifoLib.o
}
ObjectFile libwindq.a::qPriBMapLib.o {
	NAME Object file qPriBMapLib.o from archive libwindq.a
	EXPORTS qPriBMapInit qTradPriBMapSetCompatible qTradPriBMapClassId qPriBMapResort _func_qPriBMapNativeResort qPriBMapPut qPriBMapRemove qPriBMapGet qPriBMapRestore qPriBMapNext qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapSet qPriBMapClassId
	IMPORTS .TOC. dllInit bzero dllAdd dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriBMapLib.o {
	OBJECT += libwindq.a::qPriBMapLib.o
}
ObjectFile libwindq.a::qPriDeltaLib.o {
	NAME Object file qPriDeltaLib.o from archive libwindq.a
	EXPORTS qPriDeltaInit qPriDeltaPut qPriDeltaGet qPriDeltaRemove qPriDeltaResort qPriDeltaAdvance qPriDeltaGetExpired qPriDeltaKey qPriDeltaInfo qPriDeltaEach qPriDeltaNext qPriDeltaClassId
	IMPORTS .TOC. dllInsert dllCount
	DECLARES 
	USES 
}
Module qPriDeltaLib.o {
	OBJECT += libwindq.a::qPriDeltaLib.o
}
ObjectFile libwindq.a::qPriListLib.o {
	NAME Object file qPriListLib.o from archive libwindq.a
	EXPORTS qPriListInit qTradPriListSetCompatible qTradPriListClassId qPriListResort qPriListPut qPriListPutFromTail qPriListGet qPriListRemove qPriListKey qPriListInfo qPriListEach qPriListNext qPriListClassId qPriListFromTailClassId
	IMPORTS .TOC. dllInsert dllGet dllRemove dllCount
	DECLARES 
	USES 
}
Module qPriListLib.o {
	OBJECT += libwindq.a::qPriListLib.o
}
ObjectFile libwindq.a::qPxPriBMapLib.o {
	NAME Object file qPxPriBMapLib.o from archive libwindq.a
	EXPORTS qPxPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut qPriBMapSet dllAdd dllInsert _func_qPriBMapNativeResort qPriBMapRemove qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxPriBMapLib.o {
	OBJECT += libwindq.a::qPxPriBMapLib.o
}
ObjectFile libwindq.a::qPxSSPriBMapLib.o {
	NAME Object file qPxSSPriBMapLib.o from archive libwindq.a
	EXPORTS qPxSSPriBMapClassId
	IMPORTS .TOC. readyQNodeToTcb qPriBMapPut pxSSThreadStateActive qPriBMapSet dllAdd dllInsert qPriBMapRemove pxSSThreadStateBlock _func_qPriBMapNativeResort qPriBMapGet qPriBMapKey qPriBMapInfo qPriBMapEach qPriBMapRestore qPriBMapNext
	DECLARES 
	USES 
}
Module qPxSSPriBMapLib.o {
	OBJECT += libwindq.a::qPxSSPriBMapLib.o
}
Library libwindq.a {
	MODULES libwindq.a::qFifoLib.o libwindq.a::qPriBMapLib.o libwindq.a::qPriDeltaLib.o libwindq.a::qPriListLib.o libwindq.a::qPxPriBMapLib.o libwindq.a::qPxSSPriBMapLib.o
}
