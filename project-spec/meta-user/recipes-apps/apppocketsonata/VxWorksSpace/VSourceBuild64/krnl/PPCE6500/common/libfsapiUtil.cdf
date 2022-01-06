Symbol dosFsDevInit {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol dosFsDevInitOptionsSet {
}
Symbol dosFsMkfs {
}
Symbol dosFsMkfsOptionsSet {
}
Symbol dosFsConfigInit {
}
Symbol dosFsConfigGet {
}
Symbol dosFsConfigShow {
}
Symbol _func_dosFsShowRtn {
}
Symbol dosFsModeChange {
}
Symbol dosFsReadyChange {
}
Symbol dosFsVolOptionsGet {
}
Symbol dosFsVolOptionsSet {
}
Symbol dosFsDateTimeInstall {
}
Symbol dosFsCacheSizeDefault {
}
Symbol tarHelp {
}
Symbol TAPE {
}
Symbol read {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol strchr {
}
Symbol stat {
}
Symbol utime {
}
Symbol sscanf {
}
Symbol bfill {
}
Symbol strlen {
}
Symbol strcmp {
}
Symbol open {
}
Symbol errnoGet {
}
Symbol strerror {
}
Symbol close {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol clock_gettime {
}
Symbol sprintf {
}
Symbol __errno {
}
Symbol write {
}
Symbol lseek {
}
Symbol calloc {
}
Symbol unlink {
}
Symbol free {
}
Symbol tarExtract {
}
Symbol bzero {
}
Symbol bcmp {
}
Symbol bcopy {
}
Symbol perror {
}
Symbol strcat {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol strncat {
}
Symbol readdir {
}
Symbol errnoSet {
}
Symbol tarArchive {
}
Symbol tarToc {
}
Symbol index {
}
Symbol rindex {
}
Symbol cd {
}
Symbol ioDefPathCat {
}
Symbol pwd {
}
Symbol ioDefPathGet {
}
Symbol mkdir {
}
Symbol rmdir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol strncmp {
}
Symbol iosDevFind {
}
Symbol fstat {
}
Symbol ioctl {
}
Symbol ioMaxLinkLevels {
}
Symbol remove {
}
Symbol rm {
}
Symbol copyStreams {
}
Symbol fioRead {
}
Symbol copy {
}
Symbol time {
}
Symbol chkdsk {
}
Symbol __ctype_toupper {
}
Symbol localtime_r {
}
Symbol fdprintf {
}
Symbol dirList {
}
Symbol _func_netLsByName {
}
Symbol ls {
}
Symbol ll {
}
Symbol lsr {
}
Symbol llr {
}
Symbol cp {
}
Symbol mv {
}
Symbol snprintf {
}
Symbol xcopy {
}
Symbol xdelete {
}
Symbol attrib {
}
Symbol xattrib {
}
Symbol dosfsDiskFormat {
}
Symbol _func_dosFsFmtRtn {
}
Symbol diskFormat {
}
Symbol hrfsDiskFormat {
}
Symbol hrfsFmtRtn {
}
Symbol diskInit {
}
Symbol commit {
}
Symbol ioHelp {
}
ObjectFile libfsapiUtil.a::usrDosFsOld.o {
	NAME Object file usrDosFsOld.o from archive libfsapiUtil.a
	EXPORTS dosFsDevInit dosFsDevInitOptionsSet dosFsMkfs dosFsMkfsOptionsSet dosFsConfigInit dosFsConfigGet dosFsConfigShow dosFsModeChange dosFsReadyChange dosFsVolOptionsGet dosFsVolOptionsSet dosFsDateTimeInstall dosFsCacheSizeDefault
	IMPORTS .TOC. printf _func_dosFsShowRtn
	DECLARES 
	USES 
}
Module usrDosFsOld.o {
	OBJECT += libfsapiUtil.a::usrDosFsOld.o
}
ObjectFile libfsapiUtil.a::tarLib.o {
	NAME Object file tarLib.o from archive libfsapiUtil.a
	EXPORTS tarHelp TAPE tarExtract tarArchive tarToc
	IMPORTS .TOC. printf read printErr strncpy strchr stat utime sscanf bfill strlen strcmp open errnoGet strerror close malloc strcpy clock_gettime sprintf __errno write lseek calloc unlink free bzero bcmp bcopy perror strcat opendir closedir strncat readdir errnoSet
	DECLARES 
	USES 
}
Module tarLib.o {
	OBJECT += libfsapiUtil.a::tarLib.o
}
ObjectFile libfsapiUtil.a::usrFsLib.o {
	NAME Object file usrFsLib.o from archive libfsapiUtil.a
	EXPORTS cd pwd mkdir rmdir rm copyStreams copy chkdsk dirList ls ll lsr llr cp mv xcopy xdelete attrib xattrib dosfsDiskFormat diskFormat hrfsDiskFormat diskInit commit ioHelp
	IMPORTS .TOC. index stat strcmp sprintf strcpy __errno rindex ioDefPathCat printf bzero ioDefPathGet open close calloc pathCat pathCondense strlen strncmp free iosDevFind fstat errnoGet errnoSet ioctl ioMaxLinkLevels strncpy remove malloc fioRead write printErr time perror __ctype_toupper localtime_r fdprintf _func_netLsByName opendir readdir closedir snprintf strerror unlink _func_dosFsFmtRtn hrfsFmtRtn read
	DECLARES 
	USES 
}
Module usrFsLib.o {
	OBJECT += libfsapiUtil.a::usrFsLib.o
}
Library libfsapiUtil.a {
	MODULES libfsapiUtil.a::usrDosFsOld.o libfsapiUtil.a::tarLib.o libfsapiUtil.a::usrFsLib.o
}
Symbol dosFsDevInit {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol dosFsDevInitOptionsSet {
}
Symbol dosFsMkfs {
}
Symbol dosFsMkfsOptionsSet {
}
Symbol dosFsConfigInit {
}
Symbol dosFsConfigGet {
}
Symbol dosFsConfigShow {
}
Symbol _func_dosFsShowRtn {
}
Symbol dosFsModeChange {
}
Symbol dosFsReadyChange {
}
Symbol dosFsVolOptionsGet {
}
Symbol dosFsVolOptionsSet {
}
Symbol dosFsDateTimeInstall {
}
Symbol dosFsCacheSizeDefault {
}
Symbol tarHelp {
}
Symbol TAPE {
}
Symbol read {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol strchr {
}
Symbol stat {
}
Symbol utime {
}
Symbol sscanf {
}
Symbol bfill {
}
Symbol strlen {
}
Symbol strcmp {
}
Symbol open {
}
Symbol errnoGet {
}
Symbol strerror {
}
Symbol close {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol clock_gettime {
}
Symbol sprintf {
}
Symbol __errno {
}
Symbol write {
}
Symbol lseek {
}
Symbol calloc {
}
Symbol unlink {
}
Symbol free {
}
Symbol tarExtract {
}
Symbol bzero {
}
Symbol bcmp {
}
Symbol bcopy {
}
Symbol perror {
}
Symbol strcat {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol strncat {
}
Symbol readdir {
}
Symbol errnoSet {
}
Symbol tarArchive {
}
Symbol tarToc {
}
Symbol index {
}
Symbol rindex {
}
Symbol cd {
}
Symbol ioDefPathCat {
}
Symbol pwd {
}
Symbol ioDefPathGet {
}
Symbol mkdir {
}
Symbol rmdir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol strncmp {
}
Symbol iosDevFind {
}
Symbol fstat {
}
Symbol ioctl {
}
Symbol ioMaxLinkLevels {
}
Symbol remove {
}
Symbol rm {
}
Symbol copyStreams {
}
Symbol fioRead {
}
Symbol copy {
}
Symbol time {
}
Symbol chkdsk {
}
Symbol __ctype_toupper {
}
Symbol localtime_r {
}
Symbol fdprintf {
}
Symbol dirList {
}
Symbol _func_netLsByName {
}
Symbol ls {
}
Symbol ll {
}
Symbol lsr {
}
Symbol llr {
}
Symbol cp {
}
Symbol mv {
}
Symbol snprintf {
}
Symbol xcopy {
}
Symbol xdelete {
}
Symbol attrib {
}
Symbol xattrib {
}
Symbol dosfsDiskFormat {
}
Symbol _func_dosFsFmtRtn {
}
Symbol diskFormat {
}
Symbol hrfsDiskFormat {
}
Symbol hrfsFmtRtn {
}
Symbol diskInit {
}
Symbol commit {
}
Symbol ioHelp {
}
ObjectFile libfsapiUtil.a::usrDosFsOld.o {
	NAME Object file usrDosFsOld.o from archive libfsapiUtil.a
	EXPORTS dosFsDevInit dosFsDevInitOptionsSet dosFsMkfs dosFsMkfsOptionsSet dosFsConfigInit dosFsConfigGet dosFsConfigShow dosFsModeChange dosFsReadyChange dosFsVolOptionsGet dosFsVolOptionsSet dosFsDateTimeInstall dosFsCacheSizeDefault
	IMPORTS .TOC. printf _func_dosFsShowRtn
	DECLARES 
	USES 
}
Module usrDosFsOld.o {
	OBJECT += libfsapiUtil.a::usrDosFsOld.o
}
ObjectFile libfsapiUtil.a::tarLib.o {
	NAME Object file tarLib.o from archive libfsapiUtil.a
	EXPORTS tarHelp TAPE tarExtract tarArchive tarToc
	IMPORTS .TOC. printf read printErr strncpy strchr stat utime sscanf bfill strlen strcmp open errnoGet strerror close malloc strcpy clock_gettime sprintf __errno write lseek calloc unlink free bzero bcmp bcopy perror strcat opendir closedir strncat readdir errnoSet
	DECLARES 
	USES 
}
Module tarLib.o {
	OBJECT += libfsapiUtil.a::tarLib.o
}
ObjectFile libfsapiUtil.a::usrFsLib.o {
	NAME Object file usrFsLib.o from archive libfsapiUtil.a
	EXPORTS cd pwd mkdir rmdir rm copyStreams copy chkdsk dirList ls ll lsr llr cp mv xcopy xdelete attrib xattrib dosfsDiskFormat diskFormat hrfsDiskFormat diskInit commit ioHelp
	IMPORTS .TOC. index stat strcmp sprintf strcpy __errno rindex ioDefPathCat printf bzero ioDefPathGet open close calloc pathCat pathCondense strlen strncmp free iosDevFind fstat errnoGet errnoSet ioctl ioMaxLinkLevels strncpy remove malloc fioRead write printErr time perror __ctype_toupper localtime_r fdprintf _func_netLsByName opendir readdir closedir snprintf strerror unlink _func_dosFsFmtRtn hrfsFmtRtn read
	DECLARES 
	USES 
}
Module usrFsLib.o {
	OBJECT += libfsapiUtil.a::usrFsLib.o
}
Library libfsapiUtil.a {
	MODULES libfsapiUtil.a::usrDosFsOld.o libfsapiUtil.a::tarLib.o libfsapiUtil.a::usrFsLib.o
}
Symbol dosFsDevInit {
}
Symbol .TOC. {
}
Symbol printf {
}
Symbol dosFsDevInitOptionsSet {
}
Symbol dosFsMkfs {
}
Symbol dosFsMkfsOptionsSet {
}
Symbol dosFsConfigInit {
}
Symbol dosFsConfigGet {
}
Symbol dosFsConfigShow {
}
Symbol _func_dosFsShowRtn {
}
Symbol dosFsModeChange {
}
Symbol dosFsReadyChange {
}
Symbol dosFsVolOptionsGet {
}
Symbol dosFsVolOptionsSet {
}
Symbol dosFsDateTimeInstall {
}
Symbol dosFsCacheSizeDefault {
}
Symbol tarHelp {
}
Symbol TAPE {
}
Symbol read {
}
Symbol printErr {
}
Symbol strncpy {
}
Symbol strchr {
}
Symbol stat {
}
Symbol utime {
}
Symbol sscanf {
}
Symbol bfill {
}
Symbol strlen {
}
Symbol strcmp {
}
Symbol open {
}
Symbol errnoGet {
}
Symbol strerror {
}
Symbol close {
}
Symbol malloc {
}
Symbol strcpy {
}
Symbol clock_gettime {
}
Symbol sprintf {
}
Symbol __errno {
}
Symbol write {
}
Symbol lseek {
}
Symbol calloc {
}
Symbol unlink {
}
Symbol free {
}
Symbol tarExtract {
}
Symbol bzero {
}
Symbol bcmp {
}
Symbol bcopy {
}
Symbol perror {
}
Symbol strcat {
}
Symbol opendir {
}
Symbol closedir {
}
Symbol strncat {
}
Symbol readdir {
}
Symbol errnoSet {
}
Symbol tarArchive {
}
Symbol tarToc {
}
Symbol index {
}
Symbol rindex {
}
Symbol cd {
}
Symbol ioDefPathCat {
}
Symbol pwd {
}
Symbol ioDefPathGet {
}
Symbol mkdir {
}
Symbol rmdir {
}
Symbol pathCat {
}
Symbol pathCondense {
}
Symbol strncmp {
}
Symbol iosDevFind {
}
Symbol fstat {
}
Symbol ioctl {
}
Symbol ioMaxLinkLevels {
}
Symbol remove {
}
Symbol rm {
}
Symbol copyStreams {
}
Symbol fioRead {
}
Symbol copy {
}
Symbol time {
}
Symbol chkdsk {
}
Symbol __ctype_toupper {
}
Symbol localtime_r {
}
Symbol fdprintf {
}
Symbol dirList {
}
Symbol _func_netLsByName {
}
Symbol ls {
}
Symbol ll {
}
Symbol lsr {
}
Symbol llr {
}
Symbol cp {
}
Symbol mv {
}
Symbol snprintf {
}
Symbol xcopy {
}
Symbol xdelete {
}
Symbol attrib {
}
Symbol xattrib {
}
Symbol dosfsDiskFormat {
}
Symbol _func_dosFsFmtRtn {
}
Symbol diskFormat {
}
Symbol hrfsDiskFormat {
}
Symbol hrfsFmtRtn {
}
Symbol diskInit {
}
Symbol commit {
}
Symbol ioHelp {
}
ObjectFile libfsapiUtil.a::usrDosFsOld.o {
	NAME Object file usrDosFsOld.o from archive libfsapiUtil.a
	EXPORTS dosFsDevInit dosFsDevInitOptionsSet dosFsMkfs dosFsMkfsOptionsSet dosFsConfigInit dosFsConfigGet dosFsConfigShow dosFsModeChange dosFsReadyChange dosFsVolOptionsGet dosFsVolOptionsSet dosFsDateTimeInstall dosFsCacheSizeDefault
	IMPORTS .TOC. printf _func_dosFsShowRtn
	DECLARES 
	USES 
}
Module usrDosFsOld.o {
	OBJECT += libfsapiUtil.a::usrDosFsOld.o
}
ObjectFile libfsapiUtil.a::tarLib.o {
	NAME Object file tarLib.o from archive libfsapiUtil.a
	EXPORTS tarHelp TAPE tarExtract tarArchive tarToc
	IMPORTS .TOC. printf read printErr strncpy strchr stat utime sscanf bfill strlen strcmp open errnoGet strerror close malloc strcpy clock_gettime sprintf __errno write lseek calloc unlink free bzero bcmp bcopy perror strcat opendir closedir strncat readdir errnoSet
	DECLARES 
	USES 
}
Module tarLib.o {
	OBJECT += libfsapiUtil.a::tarLib.o
}
ObjectFile libfsapiUtil.a::usrFsLib.o {
	NAME Object file usrFsLib.o from archive libfsapiUtil.a
	EXPORTS cd pwd mkdir rmdir rm copyStreams copy chkdsk dirList ls ll lsr llr cp mv xcopy xdelete attrib xattrib dosfsDiskFormat diskFormat hrfsDiskFormat diskInit commit ioHelp
	IMPORTS .TOC. index stat strcmp sprintf strcpy __errno rindex ioDefPathCat printf bzero ioDefPathGet open close calloc pathCat pathCondense strlen strncmp free iosDevFind fstat errnoGet errnoSet ioctl ioMaxLinkLevels strncpy remove malloc fioRead write printErr time perror __ctype_toupper localtime_r fdprintf _func_netLsByName opendir readdir closedir snprintf strerror unlink _func_dosFsFmtRtn hrfsFmtRtn read
	DECLARES 
	USES 
}
Module usrFsLib.o {
	OBJECT += libfsapiUtil.a::usrFsLib.o
}
Library libfsapiUtil.a {
	MODULES libfsapiUtil.a::usrDosFsOld.o libfsapiUtil.a::tarLib.o libfsapiUtil.a::usrFsLib.o
}
