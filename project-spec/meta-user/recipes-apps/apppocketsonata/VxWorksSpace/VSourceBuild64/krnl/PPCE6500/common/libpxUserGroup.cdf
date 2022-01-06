Symbol pxUserGroupLibInit {
}
Symbol .TOC. {
}
Symbol setuid {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol usrRtpLockWithCallerTcb {
}
Symbol semGive {
}
Symbol __errno {
}
Symbol getuid {
}
Symbol setgid {
}
Symbol getgid {
}
Symbol seteuid {
}
Symbol geteuid {
}
Symbol setegid {
}
Symbol getegid {
}
Symbol getgroups {
}
Symbol taskCredentialsInherit {
}
Symbol rtpCredentialsInherit {
}
Symbol taskCredentialsGet {
}
Symbol taskCredentialsSet {
}
Symbol getlogin {
}
Symbol getlogin_r {
}
Symbol loginUserIdSet {
}
Symbol pxUserGroupScLibInit {
}
Symbol _setuidSc {
}
Symbol rtpLockWithCallerTcb {
}
Symbol _getuidSc {
}
Symbol _setgidSc {
}
Symbol _getgidSc {
}
Symbol _seteuidSc {
}
Symbol _geteuidSc {
}
Symbol _setegidSc {
}
Symbol _getegidSc {
}
Symbol getlogin_rSc {
}
Symbol scMemValidate {
}
ObjectFile libpxUserGroup.a::pxUserGroupLib.o {
	NAME Object file pxUserGroupLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupLibInit setuid getuid setgid getgid seteuid geteuid setegid getegid getgroups taskCredentialsInherit rtpCredentialsInherit taskCredentialsGet taskCredentialsSet
	IMPORTS .TOC. taskIdSelf kernelId usrRtpLockWithCallerTcb semGive __errno
	DECLARES 
	USES 
}
Module pxUserGroupLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupLib.o
}
ObjectFile libpxUserGroup.a::getlogin.o {
	NAME Object file getlogin.o from archive libpxUserGroup.a
	EXPORTS getlogin getlogin_r loginUserIdSet
	IMPORTS .TOC. taskIdSelf taskCredentialsGet taskCredentialsSet
	DECLARES 
	USES 
}
Module getlogin.o {
	OBJECT += libpxUserGroup.a::getlogin.o
}
ObjectFile libpxUserGroup.a::pxUserGroupScLib.o {
	NAME Object file pxUserGroupScLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupScLibInit _setuidSc _getuidSc _setgidSc _getgidSc _seteuidSc _geteuidSc _setegidSc _getegidSc getlogin_rSc
	IMPORTS .TOC. taskIdSelf rtpLockWithCallerTcb semGive __errno scMemValidate getlogin_r
	DECLARES 
	USES 
}
Module pxUserGroupScLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupScLib.o
}
Library libpxUserGroup.a {
	MODULES libpxUserGroup.a::pxUserGroupLib.o libpxUserGroup.a::getlogin.o libpxUserGroup.a::pxUserGroupScLib.o
}
Symbol pxUserGroupLibInit {
}
Symbol .TOC. {
}
Symbol setuid {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol usrRtpLockWithCallerTcb {
}
Symbol semGive {
}
Symbol __errno {
}
Symbol getuid {
}
Symbol setgid {
}
Symbol getgid {
}
Symbol seteuid {
}
Symbol geteuid {
}
Symbol setegid {
}
Symbol getegid {
}
Symbol getgroups {
}
Symbol taskCredentialsInherit {
}
Symbol rtpCredentialsInherit {
}
Symbol taskCredentialsGet {
}
Symbol taskCredentialsSet {
}
Symbol getlogin {
}
Symbol getlogin_r {
}
Symbol loginUserIdSet {
}
Symbol pxUserGroupScLibInit {
}
Symbol _setuidSc {
}
Symbol rtpLockWithCallerTcb {
}
Symbol _getuidSc {
}
Symbol _setgidSc {
}
Symbol _getgidSc {
}
Symbol _seteuidSc {
}
Symbol _geteuidSc {
}
Symbol _setegidSc {
}
Symbol _getegidSc {
}
Symbol getlogin_rSc {
}
Symbol scMemValidate {
}
ObjectFile libpxUserGroup.a::pxUserGroupLib.o {
	NAME Object file pxUserGroupLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupLibInit setuid getuid setgid getgid seteuid geteuid setegid getegid getgroups taskCredentialsInherit rtpCredentialsInherit taskCredentialsGet taskCredentialsSet
	IMPORTS .TOC. taskIdSelf kernelId usrRtpLockWithCallerTcb semGive __errno
	DECLARES 
	USES 
}
Module pxUserGroupLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupLib.o
}
ObjectFile libpxUserGroup.a::getlogin.o {
	NAME Object file getlogin.o from archive libpxUserGroup.a
	EXPORTS getlogin getlogin_r loginUserIdSet
	IMPORTS .TOC. taskIdSelf taskCredentialsGet taskCredentialsSet
	DECLARES 
	USES 
}
Module getlogin.o {
	OBJECT += libpxUserGroup.a::getlogin.o
}
ObjectFile libpxUserGroup.a::pxUserGroupScLib.o {
	NAME Object file pxUserGroupScLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupScLibInit _setuidSc _getuidSc _setgidSc _getgidSc _seteuidSc _geteuidSc _setegidSc _getegidSc getlogin_rSc
	IMPORTS .TOC. taskIdSelf rtpLockWithCallerTcb semGive __errno scMemValidate getlogin_r
	DECLARES 
	USES 
}
Module pxUserGroupScLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupScLib.o
}
Library libpxUserGroup.a {
	MODULES libpxUserGroup.a::pxUserGroupLib.o libpxUserGroup.a::getlogin.o libpxUserGroup.a::pxUserGroupScLib.o
}
Symbol pxUserGroupLibInit {
}
Symbol .TOC. {
}
Symbol setuid {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol usrRtpLockWithCallerTcb {
}
Symbol semGive {
}
Symbol __errno {
}
Symbol getuid {
}
Symbol setgid {
}
Symbol getgid {
}
Symbol seteuid {
}
Symbol geteuid {
}
Symbol setegid {
}
Symbol getegid {
}
Symbol getgroups {
}
Symbol taskCredentialsInherit {
}
Symbol rtpCredentialsInherit {
}
Symbol taskCredentialsGet {
}
Symbol taskCredentialsSet {
}
Symbol getlogin {
}
Symbol getlogin_r {
}
Symbol loginUserIdSet {
}
Symbol pxUserGroupScLibInit {
}
Symbol _setuidSc {
}
Symbol rtpLockWithCallerTcb {
}
Symbol _getuidSc {
}
Symbol _setgidSc {
}
Symbol _getgidSc {
}
Symbol _seteuidSc {
}
Symbol _geteuidSc {
}
Symbol _setegidSc {
}
Symbol _getegidSc {
}
Symbol getlogin_rSc {
}
Symbol scMemValidate {
}
ObjectFile libpxUserGroup.a::pxUserGroupLib.o {
	NAME Object file pxUserGroupLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupLibInit setuid getuid setgid getgid seteuid geteuid setegid getegid getgroups taskCredentialsInherit rtpCredentialsInherit taskCredentialsGet taskCredentialsSet
	IMPORTS .TOC. taskIdSelf kernelId usrRtpLockWithCallerTcb semGive __errno
	DECLARES 
	USES 
}
Module pxUserGroupLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupLib.o
}
ObjectFile libpxUserGroup.a::getlogin.o {
	NAME Object file getlogin.o from archive libpxUserGroup.a
	EXPORTS getlogin getlogin_r loginUserIdSet
	IMPORTS .TOC. taskIdSelf taskCredentialsGet taskCredentialsSet
	DECLARES 
	USES 
}
Module getlogin.o {
	OBJECT += libpxUserGroup.a::getlogin.o
}
ObjectFile libpxUserGroup.a::pxUserGroupScLib.o {
	NAME Object file pxUserGroupScLib.o from archive libpxUserGroup.a
	EXPORTS pxUserGroupScLibInit _setuidSc _getuidSc _setgidSc _getgidSc _seteuidSc _geteuidSc _setegidSc _getegidSc getlogin_rSc
	IMPORTS .TOC. taskIdSelf rtpLockWithCallerTcb semGive __errno scMemValidate getlogin_r
	DECLARES 
	USES 
}
Module pxUserGroupScLib.o {
	OBJECT += libpxUserGroup.a::pxUserGroupScLib.o
}
Library libpxUserGroup.a {
	MODULES libpxUserGroup.a::pxUserGroupLib.o libpxUserGroup.a::getlogin.o libpxUserGroup.a::pxUserGroupScLib.o
}
