Symbol sockLibInit {
}
Symbol .TOC. {
}
Symbol socketDevHdr {
}
Symbol iosDrvInstall {
}
Symbol sockLibAdd {
}
Symbol errnoSet {
}
Symbol sockLibMap {
}
Symbol socket {
}
Symbol taskSafeTcbGet {
}
Symbol taskUnsafeTcb {
}
Symbol iosFdNew {
}
Symbol bind {
}
Symbol iosFdDrvValue {
}
Symbol listen {
}
Symbol accept {
}
Symbol connect {
}
Symbol connectWithTimeout {
}
Symbol sendto {
}
Symbol send {
}
Symbol sendmsg {
}
Symbol recvfrom {
}
Symbol recv {
}
Symbol recvmsg {
}
Symbol setsockopt {
}
Symbol getsockopt {
}
Symbol getsockname {
}
Symbol getpeername {
}
Symbol shutdown {
}
Symbol pSockIoctlMemVal {
}
Symbol pUnixIoctlMemVal {
}
Symbol sockScLibInit {
}
Symbol unixIoctlMemValidate {
}
Symbol iosDrvIoctlMemValSet {
}
Symbol _socketSc {
}
Symbol _bindSc {
}
Symbol scMemValidate {
}
Symbol _listenSc {
}
Symbol _acceptSc {
}
Symbol _connectSc {
}
Symbol _sendtoSc {
}
Symbol _sendSc {
}
Symbol _sendmsgSc {
}
Symbol _recvfromSc {
}
Symbol _recvSc {
}
Symbol _recvmsgSc {
}
Symbol _setsockoptSc {
}
Symbol _getsockoptSc {
}
Symbol _getsocknameSc {
}
Symbol _getpeernameSc {
}
Symbol _shutdownSc {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
ObjectFile libsocket.a::sockLib.o {
	NAME Object file sockLib.o from archive libsocket.a
	EXPORTS sockLibInit sockLibAdd socket bind listen accept connect connectWithTimeout sendto send sendmsg recvfrom recv recvmsg setsockopt getsockopt getsockname getpeername shutdown pSockIoctlMemVal pUnixIoctlMemVal
	IMPORTS .TOC. iosDrvInstall errnoSet taskSafeTcbGet taskUnsafeTcb iosFdNew iosFdDrvValue
	DECLARES socketDevHdr sockLibMap
	USES 
}
Module sockLib.o {
	OBJECT += libsocket.a::sockLib.o
}
ObjectFile libsocket.a::sockScLib.o {
	NAME Object file sockScLib.o from archive libsocket.a
	EXPORTS sockScLibInit unixIoctlMemValidate _socketSc _bindSc _listenSc _acceptSc _connectSc _sendtoSc _sendSc _sendmsgSc _recvfromSc _recvSc _recvmsgSc _setsockoptSc _getsockoptSc _getsocknameSc _getpeernameSc _shutdownSc
	IMPORTS .TOC. pSockIoctlMemVal pUnixIoctlMemVal socketDevHdr iosDrvIoctlMemValSet sockLibMap taskSafeTcbGet iosFdNew errnoSet taskUnsafeTcb scMemValidate iosFdDrvValue taskIdSelf kernelId
	DECLARES 
	USES 
}
Module sockScLib.o {
	OBJECT += libsocket.a::sockScLib.o
}
Library libsocket.a {
	MODULES libsocket.a::sockLib.o libsocket.a::sockScLib.o
}
Symbol sockLibInit {
}
Symbol .TOC. {
}
Symbol socketDevHdr {
}
Symbol iosDrvInstall {
}
Symbol sockLibAdd {
}
Symbol errnoSet {
}
Symbol sockLibMap {
}
Symbol socket {
}
Symbol taskSafeTcbGet {
}
Symbol taskUnsafeTcb {
}
Symbol iosFdNew {
}
Symbol bind {
}
Symbol iosFdDrvValue {
}
Symbol listen {
}
Symbol accept {
}
Symbol connect {
}
Symbol connectWithTimeout {
}
Symbol sendto {
}
Symbol send {
}
Symbol sendmsg {
}
Symbol recvfrom {
}
Symbol recv {
}
Symbol recvmsg {
}
Symbol setsockopt {
}
Symbol getsockopt {
}
Symbol getsockname {
}
Symbol getpeername {
}
Symbol shutdown {
}
Symbol pSockIoctlMemVal {
}
Symbol pUnixIoctlMemVal {
}
Symbol sockScLibInit {
}
Symbol unixIoctlMemValidate {
}
Symbol iosDrvIoctlMemValSet {
}
Symbol _socketSc {
}
Symbol _bindSc {
}
Symbol scMemValidate {
}
Symbol _listenSc {
}
Symbol _acceptSc {
}
Symbol _connectSc {
}
Symbol _sendtoSc {
}
Symbol _sendSc {
}
Symbol _sendmsgSc {
}
Symbol _recvfromSc {
}
Symbol _recvSc {
}
Symbol _recvmsgSc {
}
Symbol _setsockoptSc {
}
Symbol _getsockoptSc {
}
Symbol _getsocknameSc {
}
Symbol _getpeernameSc {
}
Symbol _shutdownSc {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
ObjectFile libsocket.a::sockLib.o {
	NAME Object file sockLib.o from archive libsocket.a
	EXPORTS sockLibInit sockLibAdd socket bind listen accept connect connectWithTimeout sendto send sendmsg recvfrom recv recvmsg setsockopt getsockopt getsockname getpeername shutdown pSockIoctlMemVal pUnixIoctlMemVal
	IMPORTS .TOC. iosDrvInstall errnoSet taskSafeTcbGet taskUnsafeTcb iosFdNew iosFdDrvValue
	DECLARES socketDevHdr sockLibMap
	USES 
}
Module sockLib.o {
	OBJECT += libsocket.a::sockLib.o
}
ObjectFile libsocket.a::sockScLib.o {
	NAME Object file sockScLib.o from archive libsocket.a
	EXPORTS sockScLibInit unixIoctlMemValidate _socketSc _bindSc _listenSc _acceptSc _connectSc _sendtoSc _sendSc _sendmsgSc _recvfromSc _recvSc _recvmsgSc _setsockoptSc _getsockoptSc _getsocknameSc _getpeernameSc _shutdownSc
	IMPORTS .TOC. pSockIoctlMemVal pUnixIoctlMemVal socketDevHdr iosDrvIoctlMemValSet sockLibMap taskSafeTcbGet iosFdNew errnoSet taskUnsafeTcb scMemValidate iosFdDrvValue taskIdSelf kernelId
	DECLARES 
	USES 
}
Module sockScLib.o {
	OBJECT += libsocket.a::sockScLib.o
}
Library libsocket.a {
	MODULES libsocket.a::sockLib.o libsocket.a::sockScLib.o
}
Symbol sockLibInit {
}
Symbol .TOC. {
}
Symbol socketDevHdr {
}
Symbol iosDrvInstall {
}
Symbol sockLibAdd {
}
Symbol errnoSet {
}
Symbol sockLibMap {
}
Symbol socket {
}
Symbol taskSafeTcbGet {
}
Symbol taskUnsafeTcb {
}
Symbol iosFdNew {
}
Symbol bind {
}
Symbol iosFdDrvValue {
}
Symbol listen {
}
Symbol accept {
}
Symbol connect {
}
Symbol connectWithTimeout {
}
Symbol sendto {
}
Symbol send {
}
Symbol sendmsg {
}
Symbol recvfrom {
}
Symbol recv {
}
Symbol recvmsg {
}
Symbol setsockopt {
}
Symbol getsockopt {
}
Symbol getsockname {
}
Symbol getpeername {
}
Symbol shutdown {
}
Symbol pSockIoctlMemVal {
}
Symbol pUnixIoctlMemVal {
}
Symbol sockScLibInit {
}
Symbol unixIoctlMemValidate {
}
Symbol iosDrvIoctlMemValSet {
}
Symbol _socketSc {
}
Symbol _bindSc {
}
Symbol scMemValidate {
}
Symbol _listenSc {
}
Symbol _acceptSc {
}
Symbol _connectSc {
}
Symbol _sendtoSc {
}
Symbol _sendSc {
}
Symbol _sendmsgSc {
}
Symbol _recvfromSc {
}
Symbol _recvSc {
}
Symbol _recvmsgSc {
}
Symbol _setsockoptSc {
}
Symbol _getsockoptSc {
}
Symbol _getsocknameSc {
}
Symbol _getpeernameSc {
}
Symbol _shutdownSc {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
ObjectFile libsocket.a::sockLib.o {
	NAME Object file sockLib.o from archive libsocket.a
	EXPORTS sockLibInit sockLibAdd socket bind listen accept connect connectWithTimeout sendto send sendmsg recvfrom recv recvmsg setsockopt getsockopt getsockname getpeername shutdown pSockIoctlMemVal pUnixIoctlMemVal
	IMPORTS .TOC. iosDrvInstall errnoSet taskSafeTcbGet taskUnsafeTcb iosFdNew iosFdDrvValue
	DECLARES socketDevHdr sockLibMap
	USES 
}
Module sockLib.o {
	OBJECT += libsocket.a::sockLib.o
}
ObjectFile libsocket.a::sockScLib.o {
	NAME Object file sockScLib.o from archive libsocket.a
	EXPORTS sockScLibInit unixIoctlMemValidate _socketSc _bindSc _listenSc _acceptSc _connectSc _sendtoSc _sendSc _sendmsgSc _recvfromSc _recvSc _recvmsgSc _setsockoptSc _getsockoptSc _getsocknameSc _getpeernameSc _shutdownSc
	IMPORTS .TOC. pSockIoctlMemVal pUnixIoctlMemVal socketDevHdr iosDrvIoctlMemValSet sockLibMap taskSafeTcbGet iosFdNew errnoSet taskUnsafeTcb scMemValidate iosFdDrvValue taskIdSelf kernelId
	DECLARES 
	USES 
}
Module sockScLib.o {
	OBJECT += libsocket.a::sockScLib.o
}
Library libsocket.a {
	MODULES libsocket.a::sockLib.o libsocket.a::sockScLib.o
}
