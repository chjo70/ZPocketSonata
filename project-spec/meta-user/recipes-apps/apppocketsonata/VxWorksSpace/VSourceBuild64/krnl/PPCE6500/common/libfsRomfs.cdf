Symbol rfsread {
}
Symbol .TOC. {
}
Symbol semTake {
}
Symbol vxBlkIO {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol rfs_open {
}
Symbol malloc {
}
Symbol memcpy {
}
Symbol printf {
}
Symbol strncmp {
}
Symbol free {
}
Symbol rfs_read {
}
Symbol rfs_seek {
}
Symbol rfs_close {
}
Symbol rfs_write {
}
Symbol rfs_stat {
}
Symbol bzero {
}
Symbol rfs_ls {
}
Symbol romfs_ntoh {
}
Symbol romfsBlkDevCreate {
}
Symbol poolItemGet {
}
Symbol errnoSet {
}
Symbol poolItemReturn {
}
Symbol romfsFsInit {
}
Symbol romfsFsDrvNum {
}
Symbol iosDrvInstall {
}
Symbol printErr {
}
Symbol iosDevFind {
}
Symbol iosDevDelete {
}
Symbol poolDelete {
}
Symbol romfsFsDevCreate {
}
Symbol poolCreate {
}
Symbol semMCreate {
}
Symbol iosDevAdd {
}
Symbol fsPathAddedEventRaise {
}
Symbol romfsVolumeCreate {
}
ObjectFile libfsRomfs.a::romfs.o {
	NAME Object file romfs.o from archive libfsRomfs.a
	EXPORTS rfsread rfs_open rfs_read rfs_seek rfs_close rfs_write rfs_stat rfs_ls romfs_ntoh
	IMPORTS .TOC. semTake vxBlkIO semGive bcopy malloc memcpy printf strncmp free bzero
	DECLARES 
	USES 
}
Module romfs.o {
	OBJECT += libfsRomfs.a::romfs.o
}
ObjectFile libfsRomfs.a::romfsDrv.o {
	NAME Object file romfsDrv.o from archive libfsRomfs.a
	EXPORTS romfsBlkDevCreate
	IMPORTS .TOC. malloc bzero bcopy
	DECLARES 
	USES 
}
Module romfsDrv.o {
	OBJECT += libfsRomfs.a::romfsDrv.o
}
ObjectFile libfsRomfs.a::romfsLib.o {
	NAME Object file romfsLib.o from archive libfsRomfs.a
	EXPORTS romfsFsInit romfsFsDrvNum romfsFsDevCreate vxBlkIO romfsVolumeCreate
	IMPORTS .TOC. poolItemGet errnoSet rfs_open poolItemReturn rfs_close rfs_read rfsread memcpy rfs_seek rfs_stat bzero iosDrvInstall printErr iosDevFind iosDevDelete poolDelete free malloc poolCreate semMCreate iosDevAdd fsPathAddedEventRaise romfsBlkDevCreate
	DECLARES 
	USES 
}
Module romfsLib.o {
	OBJECT += libfsRomfs.a::romfsLib.o
}
Library libfsRomfs.a {
	MODULES libfsRomfs.a::romfs.o libfsRomfs.a::romfsDrv.o libfsRomfs.a::romfsLib.o
}
Symbol rfsread {
}
Symbol .TOC. {
}
Symbol semTake {
}
Symbol vxBlkIO {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol rfs_open {
}
Symbol malloc {
}
Symbol memcpy {
}
Symbol printf {
}
Symbol strncmp {
}
Symbol free {
}
Symbol rfs_read {
}
Symbol rfs_seek {
}
Symbol rfs_close {
}
Symbol rfs_write {
}
Symbol rfs_stat {
}
Symbol bzero {
}
Symbol rfs_ls {
}
Symbol romfs_ntoh {
}
Symbol romfsBlkDevCreate {
}
Symbol poolItemGet {
}
Symbol errnoSet {
}
Symbol poolItemReturn {
}
Symbol romfsFsInit {
}
Symbol romfsFsDrvNum {
}
Symbol iosDrvInstall {
}
Symbol printErr {
}
Symbol iosDevFind {
}
Symbol iosDevDelete {
}
Symbol poolDelete {
}
Symbol romfsFsDevCreate {
}
Symbol poolCreate {
}
Symbol semMCreate {
}
Symbol iosDevAdd {
}
Symbol fsPathAddedEventRaise {
}
Symbol romfsVolumeCreate {
}
ObjectFile libfsRomfs.a::romfs.o {
	NAME Object file romfs.o from archive libfsRomfs.a
	EXPORTS rfsread rfs_open rfs_read rfs_seek rfs_close rfs_write rfs_stat rfs_ls romfs_ntoh
	IMPORTS .TOC. semTake vxBlkIO semGive bcopy malloc memcpy printf strncmp free bzero
	DECLARES 
	USES 
}
Module romfs.o {
	OBJECT += libfsRomfs.a::romfs.o
}
ObjectFile libfsRomfs.a::romfsDrv.o {
	NAME Object file romfsDrv.o from archive libfsRomfs.a
	EXPORTS romfsBlkDevCreate
	IMPORTS .TOC. malloc bzero bcopy
	DECLARES 
	USES 
}
Module romfsDrv.o {
	OBJECT += libfsRomfs.a::romfsDrv.o
}
ObjectFile libfsRomfs.a::romfsLib.o {
	NAME Object file romfsLib.o from archive libfsRomfs.a
	EXPORTS romfsFsInit romfsFsDrvNum romfsFsDevCreate vxBlkIO romfsVolumeCreate
	IMPORTS .TOC. poolItemGet errnoSet rfs_open poolItemReturn rfs_close rfs_read rfsread memcpy rfs_seek rfs_stat bzero iosDrvInstall printErr iosDevFind iosDevDelete poolDelete free malloc poolCreate semMCreate iosDevAdd fsPathAddedEventRaise romfsBlkDevCreate
	DECLARES 
	USES 
}
Module romfsLib.o {
	OBJECT += libfsRomfs.a::romfsLib.o
}
Library libfsRomfs.a {
	MODULES libfsRomfs.a::romfs.o libfsRomfs.a::romfsDrv.o libfsRomfs.a::romfsLib.o
}
Symbol rfsread {
}
Symbol .TOC. {
}
Symbol semTake {
}
Symbol vxBlkIO {
}
Symbol semGive {
}
Symbol bcopy {
}
Symbol rfs_open {
}
Symbol malloc {
}
Symbol memcpy {
}
Symbol printf {
}
Symbol strncmp {
}
Symbol free {
}
Symbol rfs_read {
}
Symbol rfs_seek {
}
Symbol rfs_close {
}
Symbol rfs_write {
}
Symbol rfs_stat {
}
Symbol bzero {
}
Symbol rfs_ls {
}
Symbol romfs_ntoh {
}
Symbol romfsBlkDevCreate {
}
Symbol poolItemGet {
}
Symbol errnoSet {
}
Symbol poolItemReturn {
}
Symbol romfsFsInit {
}
Symbol romfsFsDrvNum {
}
Symbol iosDrvInstall {
}
Symbol printErr {
}
Symbol iosDevFind {
}
Symbol iosDevDelete {
}
Symbol poolDelete {
}
Symbol romfsFsDevCreate {
}
Symbol poolCreate {
}
Symbol semMCreate {
}
Symbol iosDevAdd {
}
Symbol fsPathAddedEventRaise {
}
Symbol romfsVolumeCreate {
}
ObjectFile libfsRomfs.a::romfs.o {
	NAME Object file romfs.o from archive libfsRomfs.a
	EXPORTS rfsread rfs_open rfs_read rfs_seek rfs_close rfs_write rfs_stat rfs_ls romfs_ntoh
	IMPORTS .TOC. semTake vxBlkIO semGive bcopy malloc memcpy printf strncmp free bzero
	DECLARES 
	USES 
}
Module romfs.o {
	OBJECT += libfsRomfs.a::romfs.o
}
ObjectFile libfsRomfs.a::romfsDrv.o {
	NAME Object file romfsDrv.o from archive libfsRomfs.a
	EXPORTS romfsBlkDevCreate
	IMPORTS .TOC. malloc bzero bcopy
	DECLARES 
	USES 
}
Module romfsDrv.o {
	OBJECT += libfsRomfs.a::romfsDrv.o
}
ObjectFile libfsRomfs.a::romfsLib.o {
	NAME Object file romfsLib.o from archive libfsRomfs.a
	EXPORTS romfsFsInit romfsFsDrvNum romfsFsDevCreate vxBlkIO romfsVolumeCreate
	IMPORTS .TOC. poolItemGet errnoSet rfs_open poolItemReturn rfs_close rfs_read rfsread memcpy rfs_seek rfs_stat bzero iosDrvInstall printErr iosDevFind iosDevDelete poolDelete free malloc poolCreate semMCreate iosDevAdd fsPathAddedEventRaise romfsBlkDevCreate
	DECLARES 
	USES 
}
Module romfsLib.o {
	OBJECT += libfsRomfs.a::romfsLib.o
}
Library libfsRomfs.a {
	MODULES libfsRomfs.a::romfs.o libfsRomfs.a::romfsDrv.o libfsRomfs.a::romfsLib.o
}
