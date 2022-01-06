Symbol umaskLibInit {
}
Symbol .TOC. {
}
Symbol umask {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol umaskGet {
}
Symbol umaskSet {
}
Symbol globalUmaskGet {
}
Symbol umaskScLibInit {
}
Symbol _umaskSc {
}
ObjectFile libumask.a::umaskLib.o {
	NAME Object file umaskLib.o from archive libumask.a
	EXPORTS umaskLibInit umask umaskGet umaskSet globalUmaskGet
	IMPORTS .TOC. taskIdSelf kernelId
	DECLARES 
	USES 
}
Module umaskLib.o {
	OBJECT += libumask.a::umaskLib.o
}
ObjectFile libumask.a::umaskScLib.o {
	NAME Object file umaskScLib.o from archive libumask.a
	EXPORTS umaskScLibInit _umaskSc
	IMPORTS .TOC. umask
	DECLARES 
	USES 
}
Module umaskScLib.o {
	OBJECT += libumask.a::umaskScLib.o
}
Library libumask.a {
	MODULES libumask.a::umaskLib.o libumask.a::umaskScLib.o
}
Symbol umaskLibInit {
}
Symbol .TOC. {
}
Symbol umask {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol umaskGet {
}
Symbol umaskSet {
}
Symbol globalUmaskGet {
}
Symbol umaskScLibInit {
}
Symbol _umaskSc {
}
ObjectFile libumask.a::umaskLib.o {
	NAME Object file umaskLib.o from archive libumask.a
	EXPORTS umaskLibInit umask umaskGet umaskSet globalUmaskGet
	IMPORTS .TOC. taskIdSelf kernelId
	DECLARES 
	USES 
}
Module umaskLib.o {
	OBJECT += libumask.a::umaskLib.o
}
ObjectFile libumask.a::umaskScLib.o {
	NAME Object file umaskScLib.o from archive libumask.a
	EXPORTS umaskScLibInit _umaskSc
	IMPORTS .TOC. umask
	DECLARES 
	USES 
}
Module umaskScLib.o {
	OBJECT += libumask.a::umaskScLib.o
}
Library libumask.a {
	MODULES libumask.a::umaskLib.o libumask.a::umaskScLib.o
}
Symbol umaskLibInit {
}
Symbol .TOC. {
}
Symbol umask {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol umaskGet {
}
Symbol umaskSet {
}
Symbol globalUmaskGet {
}
Symbol umaskScLibInit {
}
Symbol _umaskSc {
}
ObjectFile libumask.a::umaskLib.o {
	NAME Object file umaskLib.o from archive libumask.a
	EXPORTS umaskLibInit umask umaskGet umaskSet globalUmaskGet
	IMPORTS .TOC. taskIdSelf kernelId
	DECLARES 
	USES 
}
Module umaskLib.o {
	OBJECT += libumask.a::umaskLib.o
}
ObjectFile libumask.a::umaskScLib.o {
	NAME Object file umaskScLib.o from archive libumask.a
	EXPORTS umaskScLibInit _umaskSc
	IMPORTS .TOC. umask
	DECLARES 
	USES 
}
Module umaskScLib.o {
	OBJECT += libumask.a::umaskScLib.o
}
Library libumask.a {
	MODULES libumask.a::umaskLib.o libumask.a::umaskScLib.o
}
