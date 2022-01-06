Symbol __assert {
}
Symbol .TOC. {
}
Symbol fdprintf {
}
Symbol abort {
}
Symbol __ctype {
}
Symbol __ctype_tolower {
}
Symbol __ctype_toupper {
}
Symbol isalnum {
}
Symbol isalpha {
}
Symbol iscntrl {
}
Symbol isdigit {
}
Symbol isgraph {
}
Symbol islower {
}
Symbol isprint {
}
Symbol ispunct {
}
Symbol isspace {
}
Symbol isupper {
}
Symbol isxdigit {
}
Symbol tolower {
}
Symbol toupper {
}
Symbol localeconv {
}
Symbol __locale {
}
Symbol setlocale {
}
Symbol strcmp {
}
Symbol __clocale {
}
Symbol _setjmpSetup {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol _func_rtpSigprocmask {
}
Symbol longjmp {
}
Symbol taskSuspend {
}
Symbol __rta_longjmp {
}
Symbol _func_sigprocmask {
}
Symbol _sigCtxRtnValSet {
}
Symbol _sigCtxLoad {
}
Symbol clearerr {
}
Symbol fdopen {
}
Symbol iosFdMap {
}
Symbol __sflags {
}
Symbol stdioFpCreate {
}
Symbol feof {
}
Symbol ferror {
}
Symbol __sflush {
}
Symbol __swrite {
}
Symbol fflush {
}
Symbol __errno {
}
Symbol fgetc {
}
Symbol __srget {
}
Symbol fgetpos {
}
Symbol ftell {
}
Symbol fgets {
}
Symbol __srefill {
}
Symbol memchr {
}
Symbol bcopy {
}
Symbol fileno {
}
Symbol fopen {
}
Symbol open {
}
Symbol stdioFpDestroy {
}
Symbol __sseek {
}
Symbol fputc {
}
Symbol __swbuf {
}
Symbol fputs {
}
Symbol strlen {
}
Symbol __sfvwrite {
}
Symbol fread {
}
Symbol fsetpos {
}
Symbol fseek {
}
Symbol __swsetup {
}
Symbol fwrite {
}
Symbol getc {
}
Symbol getchar {
}
Symbol __stdin {
}
Symbol gets {
}
Symbol getw {
}
Symbol perror {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol strerror {
}
Symbol putc {
}
Symbol putchar {
}
Symbol __stdout {
}
Symbol putw {
}
Symbol puts {
}
Symbol rewind {
}
Symbol setbuf {
}
Symbol setvbuf {
}
Symbol setbuffer {
}
Symbol setlinebuf {
}
Symbol __sread {
}
Symbol read {
}
Symbol lseek {
}
Symbol write {
}
Symbol __sclose {
}
Symbol close {
}
Symbol tmpnam {
}
Symbol strcpy {
}
Symbol tmpfile {
}
Symbol vfprintf {
}
Symbol handleInit {
}
Symbol fioFormatV {
}
Symbol handleTerminate {
}
Symbol fscanf {
}
Symbol fioScanV {
}
Symbol ungetc {
}
Symbol scanf {
}
Symbol _func_fclose {
}
Symbol fclose {
}
Symbol free {
}
Symbol freopen {
}
Symbol __smakebuf {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol isatty {
}
Symbol stdioInit {
}
Symbol _func_taskDeleteHookAdd {
}
Symbol taskCreateHookInit {
}
Symbol taskDeleteHookAdd {
}
Symbol stdioFp {
}
Symbol stdioShowInit {
}
Symbol stdioShow {
}
Symbol handleShowConnect {
}
Symbol printf {
}
Symbol realloc {
}
Symbol raise {
}
Symbol exit {
}
Symbol abs {
}
Symbol atexit {
}
Symbol atof {
}
Symbol strtod {
}
Symbol atoi {
}
Symbol strtol {
}
Symbol atol {
}
Symbol bsearch {
}
Symbol div_r {
}
Symbol div {
}
Symbol labs {
}
Symbol ldiv_r {
}
Symbol ldiv {
}
Symbol mblen {
}
Symbol mbtowc {
}
Symbol wctomb {
}
Symbol mbstowcs {
}
Symbol wcstombs {
}
Symbol qsort {
}
Symbol rand {
}
Symbol _Randseed {
}
Symbol srand {
}
Symbol strtoul {
}
Symbol system {
}
Symbol ldexp {
}
Symbol strtoll {
}
Symbol errnoSet {
}
Symbol strtoull {
}
Symbol memcmp {
}
Symbol memcpy {
}
Symbol memmove {
}
Symbol memset {
}
Symbol bfill {
}
Symbol __internal_memset_s {
}
Symbol memset_s {
}
Symbol _memset_s_func {
}
Symbol strcat {
}
Symbol strchr {
}
Symbol __strxfrm {
}
Symbol strcoll {
}
Symbol strcspn {
}
Symbol strerrorIf {
}
Symbol _func_symFindSymbol {
}
Symbol statSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol strerror_r {
}
Symbol strlcpy {
}
Symbol snprintf {
}
Symbol strncat {
}
Symbol strncmp {
}
Symbol strncpy {
}
Symbol strpbrk {
}
Symbol strrchr {
}
Symbol strspn {
}
Symbol strstr {
}
Symbol strtok {
}
Symbol strtok_r {
}
Symbol __costate {
}
Symbol strxfrm {
}
Symbol strlcat {
}
Symbol strcasecmp {
}
Symbol strncasecmp {
}
Symbol strdup {
}
Symbol __loctime {
}
Symbol asctime_r {
}
Symbol strftime {
}
Symbol asctime {
}
Symbol _vxworks_asctime_r {
}
Symbol clock {
}
Symbol ctime_r {
}
Symbol localtime {
}
Symbol ctime {
}
Symbol _vxworks_ctime_r {
}
Symbol __daysSinceEpoch {
}
Symbol __julday {
}
Symbol __getTime {
}
Symbol gmtime_r {
}
Symbol gmtime {
}
Symbol _vxworks_gmtime_r {
}
Symbol localtime_r {
}
Symbol __getZoneInfo {
}
Symbol __getDstInfoSub {
}
Symbol _vxworks_localtime_r {
}
Symbol mktime {
}
Symbol getenv_s {
}
Symbol bzero {
}
Symbol __getDstInfo {
}
Symbol time {
}
Symbol clock_gettime {
}
Symbol difftime {
}
Symbol __ulltod {
}
ObjectFile libc_wr.a::assert.o {
	NAME Object file assert.o from archive libc_wr.a
	EXPORTS __assert
	IMPORTS .TOC. fdprintf abort
	DECLARES 
	USES 
}
Module assert.o {
	OBJECT += libc_wr.a::assert.o
}
ObjectFile libc_wr.a::__ctype_tab.o {
	NAME Object file __ctype_tab.o from archive libc_wr.a
	EXPORTS __ctype __ctype_tolower __ctype_toupper
	IMPORTS 
	DECLARES 
	USES 
}
Module __ctype_tab.o {
	OBJECT += libc_wr.a::__ctype_tab.o
}
ObjectFile libc_wr.a::isalnum.o {
	NAME Object file isalnum.o from archive libc_wr.a
	EXPORTS isalnum
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalnum.o {
	OBJECT += libc_wr.a::isalnum.o
}
ObjectFile libc_wr.a::isalpha.o {
	NAME Object file isalpha.o from archive libc_wr.a
	EXPORTS isalpha
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalpha.o {
	OBJECT += libc_wr.a::isalpha.o
}
ObjectFile libc_wr.a::iscntrl.o {
	NAME Object file iscntrl.o from archive libc_wr.a
	EXPORTS iscntrl
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module iscntrl.o {
	OBJECT += libc_wr.a::iscntrl.o
}
ObjectFile libc_wr.a::isdigit.o {
	NAME Object file isdigit.o from archive libc_wr.a
	EXPORTS isdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isdigit.o {
	OBJECT += libc_wr.a::isdigit.o
}
ObjectFile libc_wr.a::isgraph.o {
	NAME Object file isgraph.o from archive libc_wr.a
	EXPORTS isgraph
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isgraph.o {
	OBJECT += libc_wr.a::isgraph.o
}
ObjectFile libc_wr.a::islower.o {
	NAME Object file islower.o from archive libc_wr.a
	EXPORTS islower
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module islower.o {
	OBJECT += libc_wr.a::islower.o
}
ObjectFile libc_wr.a::isprint.o {
	NAME Object file isprint.o from archive libc_wr.a
	EXPORTS isprint
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isprint.o {
	OBJECT += libc_wr.a::isprint.o
}
ObjectFile libc_wr.a::ispunct.o {
	NAME Object file ispunct.o from archive libc_wr.a
	EXPORTS ispunct
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module ispunct.o {
	OBJECT += libc_wr.a::ispunct.o
}
ObjectFile libc_wr.a::isspace.o {
	NAME Object file isspace.o from archive libc_wr.a
	EXPORTS isspace
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isspace.o {
	OBJECT += libc_wr.a::isspace.o
}
ObjectFile libc_wr.a::isupper.o {
	NAME Object file isupper.o from archive libc_wr.a
	EXPORTS isupper
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isupper.o {
	OBJECT += libc_wr.a::isupper.o
}
ObjectFile libc_wr.a::isxdigit.o {
	NAME Object file isxdigit.o from archive libc_wr.a
	EXPORTS isxdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isxdigit.o {
	OBJECT += libc_wr.a::isxdigit.o
}
ObjectFile libc_wr.a::tolower.o {
	NAME Object file tolower.o from archive libc_wr.a
	EXPORTS tolower
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module tolower.o {
	OBJECT += libc_wr.a::tolower.o
}
ObjectFile libc_wr.a::toupper.o {
	NAME Object file toupper.o from archive libc_wr.a
	EXPORTS toupper
	IMPORTS .TOC. __ctype_toupper
	DECLARES 
	USES 
}
Module toupper.o {
	OBJECT += libc_wr.a::toupper.o
}
ObjectFile libc_wr.a::localeconv.o {
	NAME Object file localeconv.o from archive libc_wr.a
	EXPORTS localeconv __locale
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module localeconv.o {
	OBJECT += libc_wr.a::localeconv.o
}
ObjectFile libc_wr.a::setlocale.o {
	NAME Object file setlocale.o from archive libc_wr.a
	EXPORTS setlocale __clocale
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module setlocale.o {
	OBJECT += libc_wr.a::setlocale.o
}
ObjectFile libc_wr.a::longjmp.o {
	NAME Object file longjmp.o from archive libc_wr.a
	EXPORTS _setjmpSetup longjmp
	IMPORTS .TOC. taskIdSelf kernelId _func_rtpSigprocmask taskSuspend __rta_longjmp _func_sigprocmask _sigCtxRtnValSet _sigCtxLoad
	DECLARES 
	USES 
}
Module longjmp.o {
	OBJECT += libc_wr.a::longjmp.o
}
ObjectFile libc_wr.a::clearerr.o {
	NAME Object file clearerr.o from archive libc_wr.a
	EXPORTS clearerr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clearerr.o {
	OBJECT += libc_wr.a::clearerr.o
}
ObjectFile libc_wr.a::fdopen.o {
	NAME Object file fdopen.o from archive libc_wr.a
	EXPORTS fdopen
	IMPORTS .TOC. iosFdMap __sflags stdioFpCreate
	DECLARES 
	USES 
}
Module fdopen.o {
	OBJECT += libc_wr.a::fdopen.o
}
ObjectFile libc_wr.a::feof.o {
	NAME Object file feof.o from archive libc_wr.a
	EXPORTS feof
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module feof.o {
	OBJECT += libc_wr.a::feof.o
}
ObjectFile libc_wr.a::ferror.o {
	NAME Object file ferror.o from archive libc_wr.a
	EXPORTS ferror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ferror.o {
	OBJECT += libc_wr.a::ferror.o
}
ObjectFile libc_wr.a::fflush.o {
	NAME Object file fflush.o from archive libc_wr.a
	EXPORTS __sflush fflush
	IMPORTS .TOC. __swrite __errno
	DECLARES 
	USES 
}
Module fflush.o {
	OBJECT += libc_wr.a::fflush.o
}
ObjectFile libc_wr.a::fgetc.o {
	NAME Object file fgetc.o from archive libc_wr.a
	EXPORTS fgetc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module fgetc.o {
	OBJECT += libc_wr.a::fgetc.o
}
ObjectFile libc_wr.a::fgetpos.o {
	NAME Object file fgetpos.o from archive libc_wr.a
	EXPORTS fgetpos
	IMPORTS .TOC. ftell
	DECLARES 
	USES 
}
Module fgetpos.o {
	OBJECT += libc_wr.a::fgetpos.o
}
ObjectFile libc_wr.a::fgets.o {
	NAME Object file fgets.o from archive libc_wr.a
	EXPORTS fgets
	IMPORTS .TOC. __srefill memchr bcopy
	DECLARES 
	USES 
}
Module fgets.o {
	OBJECT += libc_wr.a::fgets.o
}
ObjectFile libc_wr.a::fileno.o {
	NAME Object file fileno.o from archive libc_wr.a
	EXPORTS fileno
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fileno.o {
	OBJECT += libc_wr.a::fileno.o
}
ObjectFile libc_wr.a::flags.o {
	NAME Object file flags.o from archive libc_wr.a
	EXPORTS __sflags
	IMPORTS .TOC. __errno
	DECLARES 
	USES 
}
Module flags.o {
	OBJECT += libc_wr.a::flags.o
}
ObjectFile libc_wr.a::fopen.o {
	NAME Object file fopen.o from archive libc_wr.a
	EXPORTS fopen
	IMPORTS .TOC. __sflags stdioFpCreate open stdioFpDestroy __sseek
	DECLARES 
	USES 
}
Module fopen.o {
	OBJECT += libc_wr.a::fopen.o
}
ObjectFile libc_wr.a::fputc.o {
	NAME Object file fputc.o from archive libc_wr.a
	EXPORTS fputc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module fputc.o {
	OBJECT += libc_wr.a::fputc.o
}
ObjectFile libc_wr.a::fputs.o {
	NAME Object file fputs.o from archive libc_wr.a
	EXPORTS fputs
	IMPORTS .TOC. strlen __sfvwrite
	DECLARES 
	USES 
}
Module fputs.o {
	OBJECT += libc_wr.a::fputs.o
}
ObjectFile libc_wr.a::fread.o {
	NAME Object file fread.o from archive libc_wr.a
	EXPORTS fread
	IMPORTS .TOC. bcopy __srefill
	DECLARES 
	USES 
}
Module fread.o {
	OBJECT += libc_wr.a::fread.o
}
ObjectFile libc_wr.a::fsetpos.o {
	NAME Object file fsetpos.o from archive libc_wr.a
	EXPORTS fsetpos
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module fsetpos.o {
	OBJECT += libc_wr.a::fsetpos.o
}
ObjectFile libc_wr.a::ftell.o {
	NAME Object file ftell.o from archive libc_wr.a
	EXPORTS ftell
	IMPORTS .TOC. __sseek
	DECLARES 
	USES 
}
Module ftell.o {
	OBJECT += libc_wr.a::ftell.o
}
ObjectFile libc_wr.a::fvwrite.o {
	NAME Object file fvwrite.o from archive libc_wr.a
	EXPORTS __sfvwrite
	IMPORTS .TOC. __swsetup __swrite bcopy fflush memchr
	DECLARES 
	USES 
}
Module fvwrite.o {
	OBJECT += libc_wr.a::fvwrite.o
}
ObjectFile libc_wr.a::fwrite.o {
	NAME Object file fwrite.o from archive libc_wr.a
	EXPORTS fwrite
	IMPORTS .TOC. __sfvwrite
	DECLARES 
	USES 
}
Module fwrite.o {
	OBJECT += libc_wr.a::fwrite.o
}
ObjectFile libc_wr.a::getc.o {
	NAME Object file getc.o from archive libc_wr.a
	EXPORTS getc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module getc.o {
	OBJECT += libc_wr.a::getc.o
}
ObjectFile libc_wr.a::getchar.o {
	NAME Object file getchar.o from archive libc_wr.a
	EXPORTS getchar
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module getchar.o {
	OBJECT += libc_wr.a::getchar.o
}
ObjectFile libc_wr.a::gets.o {
	NAME Object file gets.o from archive libc_wr.a
	EXPORTS gets
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module gets.o {
	OBJECT += libc_wr.a::gets.o
}
ObjectFile libc_wr.a::getw.o {
	NAME Object file getw.o from archive libc_wr.a
	EXPORTS getw
	IMPORTS .TOC. fread
	DECLARES 
	USES 
}
Module getw.o {
	OBJECT += libc_wr.a::getw.o
}
ObjectFile libc_wr.a::perror.o {
	NAME Object file perror.o from archive libc_wr.a
	EXPORTS perror
	IMPORTS .TOC. __stderr fprintf __errno strerror
	DECLARES 
	USES 
}
Module perror.o {
	OBJECT += libc_wr.a::perror.o
}
ObjectFile libc_wr.a::putc.o {
	NAME Object file putc.o from archive libc_wr.a
	EXPORTS putc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module putc.o {
	OBJECT += libc_wr.a::putc.o
}
ObjectFile libc_wr.a::putchar.o {
	NAME Object file putchar.o from archive libc_wr.a
	EXPORTS putchar
	IMPORTS .TOC. __stdout __swbuf
	DECLARES 
	USES 
}
Module putchar.o {
	OBJECT += libc_wr.a::putchar.o
}
ObjectFile libc_wr.a::putw.o {
	NAME Object file putw.o from archive libc_wr.a
	EXPORTS putw
	IMPORTS .TOC. fwrite
	DECLARES 
	USES 
}
Module putw.o {
	OBJECT += libc_wr.a::putw.o
}
ObjectFile libc_wr.a::puts.o {
	NAME Object file puts.o from archive libc_wr.a
	EXPORTS puts
	IMPORTS .TOC. strlen __stdout __sfvwrite
	DECLARES 
	USES 
}
Module puts.o {
	OBJECT += libc_wr.a::puts.o
}
ObjectFile libc_wr.a::rewind.o {
	NAME Object file rewind.o from archive libc_wr.a
	EXPORTS rewind
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module rewind.o {
	OBJECT += libc_wr.a::rewind.o
}
ObjectFile libc_wr.a::rget.o {
	NAME Object file rget.o from archive libc_wr.a
	EXPORTS __srget
	IMPORTS .TOC. __srefill
	DECLARES 
	USES 
}
Module rget.o {
	OBJECT += libc_wr.a::rget.o
}
ObjectFile libc_wr.a::setbuf.o {
	NAME Object file setbuf.o from archive libc_wr.a
	EXPORTS setbuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuf.o {
	OBJECT += libc_wr.a::setbuf.o
}
ObjectFile libc_wr.a::setbuffer.o {
	NAME Object file setbuffer.o from archive libc_wr.a
	EXPORTS setbuffer setlinebuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuffer.o {
	OBJECT += libc_wr.a::setbuffer.o
}
ObjectFile libc_wr.a::stdio.o {
	NAME Object file stdio.o from archive libc_wr.a
	EXPORTS __sread __swrite __sseek __sclose
	IMPORTS .TOC. read lseek write close
	DECLARES 
	USES 
}
Module stdio.o {
	OBJECT += libc_wr.a::stdio.o
}
ObjectFile libc_wr.a::tmpnam.o {
	NAME Object file tmpnam.o from archive libc_wr.a
	EXPORTS tmpnam
	IMPORTS .TOC. strcpy strlen
	DECLARES 
	USES 
}
Module tmpnam.o {
	OBJECT += libc_wr.a::tmpnam.o
}
ObjectFile libc_wr.a::tmpfile.o {
	NAME Object file tmpfile.o from archive libc_wr.a
	EXPORTS tmpfile
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module tmpfile.o {
	OBJECT += libc_wr.a::tmpfile.o
}
ObjectFile libc_wr.a::wbuf.o {
	NAME Object file wbuf.o from archive libc_wr.a
	EXPORTS __swbuf
	IMPORTS .TOC. __swsetup fflush
	DECLARES 
	USES 
}
Module wbuf.o {
	OBJECT += libc_wr.a::wbuf.o
}
ObjectFile libc_wr.a::vfprintf.o {
	NAME Object file vfprintf.o from archive libc_wr.a
	EXPORTS vfprintf
	IMPORTS .TOC. __swsetup handleInit fioFormatV fflush handleTerminate __swbuf
	DECLARES 
	USES 
}
Module vfprintf.o {
	OBJECT += libc_wr.a::vfprintf.o
}
ObjectFile libc_wr.a::fprintf.o {
	NAME Object file fprintf.o from archive libc_wr.a
	EXPORTS fprintf
	IMPORTS .TOC. vfprintf
	DECLARES 
	USES 
}
Module fprintf.o {
	OBJECT += libc_wr.a::fprintf.o
}
ObjectFile libc_wr.a::fscanf.o {
	NAME Object file fscanf.o from archive libc_wr.a
	EXPORTS fscanf
	IMPORTS .TOC. fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module fscanf.o {
	OBJECT += libc_wr.a::fscanf.o
}
ObjectFile libc_wr.a::scanf.o {
	NAME Object file scanf.o from archive libc_wr.a
	EXPORTS scanf
	IMPORTS .TOC. __stdin fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module scanf.o {
	OBJECT += libc_wr.a::scanf.o
}
ObjectFile libc_wr.a::stdioFuncBind.o {
	NAME Object file stdioFuncBind.o from archive libc_wr.a
	EXPORTS _func_fclose
	IMPORTS 
	DECLARES 
	USES 
}
Module stdioFuncBind.o {
	OBJECT += libc_wr.a::stdioFuncBind.o
}
ObjectFile libc_wr.a::fclose.o {
	NAME Object file fclose.o from archive libc_wr.a
	EXPORTS fclose
	IMPORTS .TOC. __errno __sflush __sclose free stdioFpDestroy
	DECLARES 
	USES 
}
Module fclose.o {
	OBJECT += libc_wr.a::fclose.o
}
ObjectFile libc_wr.a::freopen.o {
	NAME Object file freopen.o from archive libc_wr.a
	EXPORTS freopen
	IMPORTS .TOC. __sflags fclose __sflush __sclose open __errno free stdioFpDestroy
	DECLARES 
	USES 
}
Module freopen.o {
	OBJECT += libc_wr.a::freopen.o
}
ObjectFile libc_wr.a::fseek.o {
	NAME Object file fseek.o from archive libc_wr.a
	EXPORTS fseek
	IMPORTS .TOC. __sseek __errno __smakebuf ioctl free __srefill __sflush
	DECLARES 
	USES 
}
Module fseek.o {
	OBJECT += libc_wr.a::fseek.o
}
ObjectFile libc_wr.a::makebuf.o {
	NAME Object file makebuf.o from archive libc_wr.a
	EXPORTS __smakebuf
	IMPORTS .TOC. ioctl malloc isatty
	DECLARES 
	USES 
}
Module makebuf.o {
	OBJECT += libc_wr.a::makebuf.o
}
ObjectFile libc_wr.a::refill.o {
	NAME Object file refill.o from archive libc_wr.a
	EXPORTS __srefill
	IMPORTS .TOC. __sflush __errno free __smakebuf __sread
	DECLARES 
	USES 
}
Module refill.o {
	OBJECT += libc_wr.a::refill.o
}
ObjectFile libc_wr.a::setvbuf.o {
	NAME Object file setvbuf.o from archive libc_wr.a
	EXPORTS setvbuf
	IMPORTS .TOC. __sflush free
	DECLARES 
	USES 
}
Module setvbuf.o {
	OBJECT += libc_wr.a::setvbuf.o
}
ObjectFile libc_wr.a::stdioLib.o {
	NAME Object file stdioLib.o from archive libc_wr.a
	EXPORTS stdioInit stdioFpCreate stdioFpDestroy __stdin __stdout __stderr stdioFp
	IMPORTS .TOC. fclose _func_fclose malloc taskIdSelf handleInit handleTerminate free _func_taskDeleteHookAdd taskCreateHookInit taskDeleteHookAdd
	DECLARES 
	USES 
}
Module stdioLib.o {
	OBJECT += libc_wr.a::stdioLib.o
}
ObjectFile libc_wr.a::stdioShow.o {
	NAME Object file stdioShow.o from archive libc_wr.a
	EXPORTS stdioShowInit stdioShow
	IMPORTS .TOC. handleShowConnect printf
	DECLARES 
	USES 
}
Module stdioShow.o {
	OBJECT += libc_wr.a::stdioShow.o
}
ObjectFile libc_wr.a::ungetc.o {
	NAME Object file ungetc.o from archive libc_wr.a
	EXPORTS ungetc
	IMPORTS .TOC. malloc realloc bcopy __sflush
	DECLARES 
	USES 
}
Module ungetc.o {
	OBJECT += libc_wr.a::ungetc.o
}
ObjectFile libc_wr.a::wsetup.o {
	NAME Object file wsetup.o from archive libc_wr.a
	EXPORTS __swsetup
	IMPORTS .TOC. free __smakebuf
	DECLARES 
	USES 
}
Module wsetup.o {
	OBJECT += libc_wr.a::wsetup.o
}
ObjectFile libc_wr.a::abort.o {
	NAME Object file abort.o from archive libc_wr.a
	EXPORTS abort
	IMPORTS .TOC. raise exit
	DECLARES 
	USES 
}
Module abort.o {
	OBJECT += libc_wr.a::abort.o
}
ObjectFile libc_wr.a::abs.o {
	NAME Object file abs.o from archive libc_wr.a
	EXPORTS abs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module abs.o {
	OBJECT += libc_wr.a::abs.o
}
ObjectFile libc_wr.a::atexit.o {
	NAME Object file atexit.o from archive libc_wr.a
	EXPORTS atexit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module atexit.o {
	OBJECT += libc_wr.a::atexit.o
}
ObjectFile libc_wr.a::atof.o {
	NAME Object file atof.o from archive libc_wr.a
	EXPORTS atof
	IMPORTS .TOC. strtod
	DECLARES 
	USES 
}
Module atof.o {
	OBJECT += libc_wr.a::atof.o
}
ObjectFile libc_wr.a::atoi.o {
	NAME Object file atoi.o from archive libc_wr.a
	EXPORTS atoi
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atoi.o {
	OBJECT += libc_wr.a::atoi.o
}
ObjectFile libc_wr.a::atol.o {
	NAME Object file atol.o from archive libc_wr.a
	EXPORTS atol
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atol.o {
	OBJECT += libc_wr.a::atol.o
}
ObjectFile libc_wr.a::bsearch.o {
	NAME Object file bsearch.o from archive libc_wr.a
	EXPORTS bsearch
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module bsearch.o {
	OBJECT += libc_wr.a::bsearch.o
}
ObjectFile libc_wr.a::div.o {
	NAME Object file div.o from archive libc_wr.a
	EXPORTS div_r div
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module div.o {
	OBJECT += libc_wr.a::div.o
}
ObjectFile libc_wr.a::labs.o {
	NAME Object file labs.o from archive libc_wr.a
	EXPORTS labs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module labs.o {
	OBJECT += libc_wr.a::labs.o
}
ObjectFile libc_wr.a::ldiv.o {
	NAME Object file ldiv.o from archive libc_wr.a
	EXPORTS ldiv_r ldiv
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ldiv.o {
	OBJECT += libc_wr.a::ldiv.o
}
ObjectFile libc_wr.a::multibyte.o {
	NAME Object file multibyte.o from archive libc_wr.a
	EXPORTS mblen mbtowc wctomb mbstowcs wcstombs
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module multibyte.o {
	OBJECT += libc_wr.a::multibyte.o
}
ObjectFile libc_wr.a::qsort.o {
	NAME Object file qsort.o from archive libc_wr.a
	EXPORTS qsort
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module qsort.o {
	OBJECT += libc_wr.a::qsort.o
}
ObjectFile libc_wr.a::stdrand.o {
	NAME Object file stdrand.o from archive libc_wr.a
	EXPORTS rand _Randseed srand
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module stdrand.o {
	OBJECT += libc_wr.a::stdrand.o
}
ObjectFile libc_wr.a::strtol.o {
	NAME Object file strtol.o from archive libc_wr.a
	EXPORTS strtol
	IMPORTS .TOC. __errno __ctype
	DECLARES 
	USES 
}
Module strtol.o {
	OBJECT += libc_wr.a::strtol.o
}
ObjectFile libc_wr.a::strtoul.o {
	NAME Object file strtoul.o from archive libc_wr.a
	EXPORTS strtoul
	IMPORTS .TOC. __ctype __errno
	DECLARES 
	USES 
}
Module strtoul.o {
	OBJECT += libc_wr.a::strtoul.o
}
ObjectFile libc_wr.a::system.o {
	NAME Object file system.o from archive libc_wr.a
	EXPORTS system
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module system.o {
	OBJECT += libc_wr.a::system.o
}
ObjectFile libc_wr.a::strtod.o {
	NAME Object file strtod.o from archive libc_wr.a
	EXPORTS strtod
	IMPORTS .TOC. __ctype ldexp
	DECLARES 
	USES 
}
Module strtod.o {
	OBJECT += libc_wr.a::strtod.o
}
ObjectFile libc_wr.a::strtoll.o {
	NAME Object file strtoll.o from archive libc_wr.a
	EXPORTS strtoll
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoll.o {
	OBJECT += libc_wr.a::strtoll.o
}
ObjectFile libc_wr.a::strtoull.o {
	NAME Object file strtoull.o from archive libc_wr.a
	EXPORTS strtoull
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoull.o {
	OBJECT += libc_wr.a::strtoull.o
}
ObjectFile libc_wr.a::memchr.o {
	NAME Object file memchr.o from archive libc_wr.a
	EXPORTS memchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memchr.o {
	OBJECT += libc_wr.a::memchr.o
}
ObjectFile libc_wr.a::memcmp.o {
	NAME Object file memcmp.o from archive libc_wr.a
	EXPORTS memcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memcmp.o {
	OBJECT += libc_wr.a::memcmp.o
}
ObjectFile libc_wr.a::memcpy.o {
	NAME Object file memcpy.o from archive libc_wr.a
	EXPORTS memcpy
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memcpy.o {
	OBJECT += libc_wr.a::memcpy.o
}
ObjectFile libc_wr.a::memmove.o {
	NAME Object file memmove.o from archive libc_wr.a
	EXPORTS memmove
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memmove.o {
	OBJECT += libc_wr.a::memmove.o
}
ObjectFile libc_wr.a::memset.o {
	NAME Object file memset.o from archive libc_wr.a
	EXPORTS memset
	IMPORTS .TOC. bfill
	DECLARES 
	USES 
}
Module memset.o {
	OBJECT += libc_wr.a::memset.o
}
ObjectFile libc_wr.a::memset_s.o {
	NAME Object file memset_s.o from archive libc_wr.a
	EXPORTS __internal_memset_s memset_s _memset_s_func
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memset_s.o {
	OBJECT += libc_wr.a::memset_s.o
}
ObjectFile libc_wr.a::strcat.o {
	NAME Object file strcat.o from archive libc_wr.a
	EXPORTS strcat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcat.o {
	OBJECT += libc_wr.a::strcat.o
}
ObjectFile libc_wr.a::strchr.o {
	NAME Object file strchr.o from archive libc_wr.a
	EXPORTS strchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strchr.o {
	OBJECT += libc_wr.a::strchr.o
}
ObjectFile libc_wr.a::strcmp.o {
	NAME Object file strcmp.o from archive libc_wr.a
	EXPORTS strcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcmp.o {
	OBJECT += libc_wr.a::strcmp.o
}
ObjectFile libc_wr.a::strcoll.o {
	NAME Object file strcoll.o from archive libc_wr.a
	EXPORTS strcoll
	IMPORTS .TOC. __strxfrm memcmp
	DECLARES 
	USES 
}
Module strcoll.o {
	OBJECT += libc_wr.a::strcoll.o
}
ObjectFile libc_wr.a::strcpy.o {
	NAME Object file strcpy.o from archive libc_wr.a
	EXPORTS strcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcpy.o {
	OBJECT += libc_wr.a::strcpy.o
}
ObjectFile libc_wr.a::strcspn.o {
	NAME Object file strcspn.o from archive libc_wr.a
	EXPORTS strcspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcspn.o {
	OBJECT += libc_wr.a::strcspn.o
}
ObjectFile libc_wr.a::strerror.o {
	NAME Object file strerror.o from archive libc_wr.a
	EXPORTS strerrorIf strerror_r strerror
	IMPORTS .TOC. _func_symFindSymbol statSymTbl _func_symNameGet _func_symValueGet strlcpy snprintf
	DECLARES 
	USES 
}
Module strerror.o {
	OBJECT += libc_wr.a::strerror.o
}
ObjectFile libc_wr.a::strlen.o {
	NAME Object file strlen.o from archive libc_wr.a
	EXPORTS strlen
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlen.o {
	OBJECT += libc_wr.a::strlen.o
}
ObjectFile libc_wr.a::strncat.o {
	NAME Object file strncat.o from archive libc_wr.a
	EXPORTS strncat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncat.o {
	OBJECT += libc_wr.a::strncat.o
}
ObjectFile libc_wr.a::strncmp.o {
	NAME Object file strncmp.o from archive libc_wr.a
	EXPORTS strncmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncmp.o {
	OBJECT += libc_wr.a::strncmp.o
}
ObjectFile libc_wr.a::strncpy.o {
	NAME Object file strncpy.o from archive libc_wr.a
	EXPORTS strncpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncpy.o {
	OBJECT += libc_wr.a::strncpy.o
}
ObjectFile libc_wr.a::strpbrk.o {
	NAME Object file strpbrk.o from archive libc_wr.a
	EXPORTS strpbrk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strpbrk.o {
	OBJECT += libc_wr.a::strpbrk.o
}
ObjectFile libc_wr.a::strrchr.o {
	NAME Object file strrchr.o from archive libc_wr.a
	EXPORTS strrchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strrchr.o {
	OBJECT += libc_wr.a::strrchr.o
}
ObjectFile libc_wr.a::strspn.o {
	NAME Object file strspn.o from archive libc_wr.a
	EXPORTS strspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strspn.o {
	OBJECT += libc_wr.a::strspn.o
}
ObjectFile libc_wr.a::strstr.o {
	NAME Object file strstr.o from archive libc_wr.a
	EXPORTS strstr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strstr.o {
	OBJECT += libc_wr.a::strstr.o
}
ObjectFile libc_wr.a::strtok.o {
	NAME Object file strtok.o from archive libc_wr.a
	EXPORTS strtok
	IMPORTS .TOC. strtok_r
	DECLARES 
	USES 
}
Module strtok.o {
	OBJECT += libc_wr.a::strtok.o
}
ObjectFile libc_wr.a::strtok_r.o {
	NAME Object file strtok_r.o from archive libc_wr.a
	EXPORTS strtok_r
	IMPORTS .TOC. strspn strpbrk
	DECLARES 
	USES 
}
Module strtok_r.o {
	OBJECT += libc_wr.a::strtok_r.o
}
ObjectFile libc_wr.a::strxfrm.o {
	NAME Object file strxfrm.o from archive libc_wr.a
	EXPORTS __strxfrm strxfrm
	IMPORTS .TOC. __costate
	DECLARES 
	USES 
}
Module strxfrm.o {
	OBJECT += libc_wr.a::strxfrm.o
}
ObjectFile libc_wr.a::xstate.o {
	NAME Object file xstate.o from archive libc_wr.a
	EXPORTS __costate
	IMPORTS 
	DECLARES 
	USES 
}
Module xstate.o {
	OBJECT += libc_wr.a::xstate.o
}
ObjectFile libc_wr.a::strlcat.o {
	NAME Object file strlcat.o from archive libc_wr.a
	EXPORTS strlcat
	IMPORTS .TOC. strlen
	DECLARES 
	USES 
}
Module strlcat.o {
	OBJECT += libc_wr.a::strlcat.o
}
ObjectFile libc_wr.a::strlcpy.o {
	NAME Object file strlcpy.o from archive libc_wr.a
	EXPORTS strlcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlcpy.o {
	OBJECT += libc_wr.a::strlcpy.o
}
ObjectFile libc_wr.a::strcasecmp.o {
	NAME Object file strcasecmp.o from archive libc_wr.a
	EXPORTS strcasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strcasecmp.o {
	OBJECT += libc_wr.a::strcasecmp.o
}
ObjectFile libc_wr.a::strncasecmp.o {
	NAME Object file strncasecmp.o from archive libc_wr.a
	EXPORTS strncasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strncasecmp.o {
	OBJECT += libc_wr.a::strncasecmp.o
}
ObjectFile libc_wr.a::strdup.o {
	NAME Object file strdup.o from archive libc_wr.a
	EXPORTS strdup
	IMPORTS .TOC. strlen malloc strcpy
	DECLARES 
	USES 
}
Module strdup.o {
	OBJECT += libc_wr.a::strdup.o
}
ObjectFile libc_wr.a::locTime.o {
	NAME Object file locTime.o from archive libc_wr.a
	EXPORTS __loctime
	IMPORTS 
	DECLARES 
	USES 
}
Module locTime.o {
	OBJECT += libc_wr.a::locTime.o
}
ObjectFile libc_wr.a::asctime.o {
	NAME Object file asctime.o from archive libc_wr.a
	EXPORTS asctime_r asctime _vxworks_asctime_r
	IMPORTS .TOC. strftime
	DECLARES 
	USES 
}
Module asctime.o {
	OBJECT += libc_wr.a::asctime.o
}
ObjectFile libc_wr.a::clock.o {
	NAME Object file clock.o from archive libc_wr.a
	EXPORTS clock
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clock.o {
	OBJECT += libc_wr.a::clock.o
}
ObjectFile libc_wr.a::ctime.o {
	NAME Object file ctime.o from archive libc_wr.a
	EXPORTS ctime_r ctime _vxworks_ctime_r
	IMPORTS .TOC. localtime asctime_r _vxworks_asctime_r
	DECLARES 
	USES 
}
Module ctime.o {
	OBJECT += libc_wr.a::ctime.o
}
ObjectFile libc_wr.a::gmtime.o {
	NAME Object file gmtime.o from archive libc_wr.a
	EXPORTS __daysSinceEpoch __julday __getTime gmtime_r gmtime _vxworks_gmtime_r
	IMPORTS .TOC. ldiv_r
	DECLARES 
	USES 
}
Module gmtime.o {
	OBJECT += libc_wr.a::gmtime.o
}
ObjectFile libc_wr.a::localtime.o {
	NAME Object file localtime.o from archive libc_wr.a
	EXPORTS localtime_r localtime _vxworks_localtime_r
	IMPORTS .TOC. __loctime __getZoneInfo atoi __getTime __getDstInfoSub
	DECLARES 
	USES 
}
Module localtime.o {
	OBJECT += libc_wr.a::localtime.o
}
ObjectFile libc_wr.a::mktime.o {
	NAME Object file mktime.o from archive libc_wr.a
	EXPORTS mktime
	IMPORTS .TOC. __julday __daysSinceEpoch __loctime __getDstInfoSub __getZoneInfo atoi
	DECLARES 
	USES 
}
Module mktime.o {
	OBJECT += libc_wr.a::mktime.o
}
ObjectFile libc_wr.a::strftime.o {
	NAME Object file strftime.o from archive libc_wr.a
	EXPORTS __getZoneInfo strftime __getDstInfoSub __getDstInfo
	IMPORTS .TOC. getenv_s strpbrk strncpy strcmp strlen memcpy abs __loctime strtok_r bzero atoi
	DECLARES 
	USES 
}
Module strftime.o {
	OBJECT += libc_wr.a::strftime.o
}
ObjectFile libc_wr.a::time.o {
	NAME Object file time.o from archive libc_wr.a
	EXPORTS time
	IMPORTS .TOC. clock_gettime
	DECLARES 
	USES 
}
Module time.o {
	OBJECT += libc_wr.a::time.o
}
ObjectFile libc_wr.a::difftime.o {
	NAME Object file difftime.o from archive libc_wr.a
	EXPORTS difftime
	IMPORTS .TOC. __ulltod
	DECLARES 
	USES 
}
Module difftime.o {
	OBJECT += libc_wr.a::difftime.o
}
Library libc_wr.a {
	MODULES libc_wr.a::assert.o libc_wr.a::__ctype_tab.o libc_wr.a::isalnum.o libc_wr.a::isalpha.o libc_wr.a::iscntrl.o libc_wr.a::isdigit.o libc_wr.a::isgraph.o libc_wr.a::islower.o libc_wr.a::isprint.o libc_wr.a::ispunct.o libc_wr.a::isspace.o libc_wr.a::isupper.o libc_wr.a::isxdigit.o libc_wr.a::tolower.o libc_wr.a::toupper.o libc_wr.a::localeconv.o libc_wr.a::setlocale.o libc_wr.a::longjmp.o libc_wr.a::clearerr.o libc_wr.a::fdopen.o libc_wr.a::feof.o libc_wr.a::ferror.o libc_wr.a::fflush.o libc_wr.a::fgetc.o libc_wr.a::fgetpos.o libc_wr.a::fgets.o libc_wr.a::fileno.o libc_wr.a::flags.o libc_wr.a::fopen.o libc_wr.a::fputc.o libc_wr.a::fputs.o libc_wr.a::fread.o libc_wr.a::fsetpos.o libc_wr.a::ftell.o libc_wr.a::fvwrite.o libc_wr.a::fwrite.o libc_wr.a::getc.o libc_wr.a::getchar.o libc_wr.a::gets.o libc_wr.a::getw.o libc_wr.a::perror.o libc_wr.a::putc.o libc_wr.a::putchar.o libc_wr.a::putw.o libc_wr.a::puts.o libc_wr.a::rewind.o libc_wr.a::rget.o libc_wr.a::setbuf.o libc_wr.a::setbuffer.o libc_wr.a::stdio.o libc_wr.a::tmpnam.o libc_wr.a::tmpfile.o libc_wr.a::wbuf.o libc_wr.a::vfprintf.o libc_wr.a::fprintf.o libc_wr.a::fscanf.o libc_wr.a::scanf.o libc_wr.a::stdioFuncBind.o libc_wr.a::fclose.o libc_wr.a::freopen.o libc_wr.a::fseek.o libc_wr.a::makebuf.o libc_wr.a::refill.o libc_wr.a::setvbuf.o libc_wr.a::stdioLib.o libc_wr.a::stdioShow.o libc_wr.a::ungetc.o libc_wr.a::wsetup.o libc_wr.a::abort.o libc_wr.a::abs.o libc_wr.a::atexit.o libc_wr.a::atof.o libc_wr.a::atoi.o libc_wr.a::atol.o libc_wr.a::bsearch.o libc_wr.a::div.o libc_wr.a::labs.o libc_wr.a::ldiv.o libc_wr.a::multibyte.o libc_wr.a::qsort.o libc_wr.a::stdrand.o libc_wr.a::strtol.o libc_wr.a::strtoul.o libc_wr.a::system.o libc_wr.a::strtod.o libc_wr.a::strtoll.o libc_wr.a::strtoull.o libc_wr.a::memchr.o libc_wr.a::memcmp.o libc_wr.a::memcpy.o libc_wr.a::memmove.o libc_wr.a::memset.o libc_wr.a::memset_s.o libc_wr.a::strcat.o libc_wr.a::strchr.o libc_wr.a::strcmp.o libc_wr.a::strcoll.o libc_wr.a::strcpy.o libc_wr.a::strcspn.o libc_wr.a::strerror.o libc_wr.a::strlen.o libc_wr.a::strncat.o libc_wr.a::strncmp.o libc_wr.a::strncpy.o libc_wr.a::strpbrk.o libc_wr.a::strrchr.o libc_wr.a::strspn.o libc_wr.a::strstr.o libc_wr.a::strtok.o libc_wr.a::strtok_r.o libc_wr.a::strxfrm.o libc_wr.a::xstate.o libc_wr.a::strlcat.o libc_wr.a::strlcpy.o libc_wr.a::strcasecmp.o libc_wr.a::strncasecmp.o libc_wr.a::strdup.o libc_wr.a::locTime.o libc_wr.a::asctime.o libc_wr.a::clock.o libc_wr.a::ctime.o libc_wr.a::gmtime.o libc_wr.a::localtime.o libc_wr.a::mktime.o libc_wr.a::strftime.o libc_wr.a::time.o libc_wr.a::difftime.o
}
Symbol __assert {
}
Symbol .TOC. {
}
Symbol fdprintf {
}
Symbol abort {
}
Symbol __ctype {
}
Symbol __ctype_tolower {
}
Symbol __ctype_toupper {
}
Symbol isalnum {
}
Symbol isalpha {
}
Symbol iscntrl {
}
Symbol isdigit {
}
Symbol isgraph {
}
Symbol islower {
}
Symbol isprint {
}
Symbol ispunct {
}
Symbol isspace {
}
Symbol isupper {
}
Symbol isxdigit {
}
Symbol tolower {
}
Symbol toupper {
}
Symbol localeconv {
}
Symbol __locale {
}
Symbol setlocale {
}
Symbol strcmp {
}
Symbol __clocale {
}
Symbol _setjmpSetup {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol _func_rtpSigprocmask {
}
Symbol longjmp {
}
Symbol taskSuspend {
}
Symbol __rta_longjmp {
}
Symbol _func_sigprocmask {
}
Symbol _sigCtxRtnValSet {
}
Symbol _sigCtxLoad {
}
Symbol clearerr {
}
Symbol fdopen {
}
Symbol iosFdMap {
}
Symbol __sflags {
}
Symbol stdioFpCreate {
}
Symbol feof {
}
Symbol ferror {
}
Symbol __sflush {
}
Symbol __swrite {
}
Symbol fflush {
}
Symbol __errno {
}
Symbol fgetc {
}
Symbol __srget {
}
Symbol fgetpos {
}
Symbol ftell {
}
Symbol fgets {
}
Symbol __srefill {
}
Symbol memchr {
}
Symbol bcopy {
}
Symbol fileno {
}
Symbol fopen {
}
Symbol open {
}
Symbol stdioFpDestroy {
}
Symbol __sseek {
}
Symbol fputc {
}
Symbol __swbuf {
}
Symbol fputs {
}
Symbol strlen {
}
Symbol __sfvwrite {
}
Symbol fread {
}
Symbol fsetpos {
}
Symbol fseek {
}
Symbol __swsetup {
}
Symbol fwrite {
}
Symbol getc {
}
Symbol getchar {
}
Symbol __stdin {
}
Symbol gets {
}
Symbol getw {
}
Symbol perror {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol strerror {
}
Symbol putc {
}
Symbol putchar {
}
Symbol __stdout {
}
Symbol putw {
}
Symbol puts {
}
Symbol rewind {
}
Symbol setbuf {
}
Symbol setvbuf {
}
Symbol setbuffer {
}
Symbol setlinebuf {
}
Symbol __sread {
}
Symbol read {
}
Symbol lseek {
}
Symbol write {
}
Symbol __sclose {
}
Symbol close {
}
Symbol tmpnam {
}
Symbol strcpy {
}
Symbol tmpfile {
}
Symbol vfprintf {
}
Symbol handleInit {
}
Symbol fioFormatV {
}
Symbol handleTerminate {
}
Symbol fscanf {
}
Symbol fioScanV {
}
Symbol ungetc {
}
Symbol scanf {
}
Symbol _func_fclose {
}
Symbol fclose {
}
Symbol free {
}
Symbol freopen {
}
Symbol __smakebuf {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol isatty {
}
Symbol stdioInit {
}
Symbol _func_taskDeleteHookAdd {
}
Symbol taskCreateHookInit {
}
Symbol taskDeleteHookAdd {
}
Symbol stdioFp {
}
Symbol stdioShowInit {
}
Symbol stdioShow {
}
Symbol handleShowConnect {
}
Symbol printf {
}
Symbol realloc {
}
Symbol raise {
}
Symbol exit {
}
Symbol abs {
}
Symbol atexit {
}
Symbol atof {
}
Symbol strtod {
}
Symbol atoi {
}
Symbol strtol {
}
Symbol atol {
}
Symbol bsearch {
}
Symbol div_r {
}
Symbol div {
}
Symbol labs {
}
Symbol ldiv_r {
}
Symbol ldiv {
}
Symbol mblen {
}
Symbol mbtowc {
}
Symbol wctomb {
}
Symbol mbstowcs {
}
Symbol wcstombs {
}
Symbol qsort {
}
Symbol rand {
}
Symbol _Randseed {
}
Symbol srand {
}
Symbol strtoul {
}
Symbol system {
}
Symbol ldexp {
}
Symbol strtoll {
}
Symbol errnoSet {
}
Symbol strtoull {
}
Symbol memcmp {
}
Symbol memcpy {
}
Symbol memmove {
}
Symbol memset {
}
Symbol bfill {
}
Symbol __internal_memset_s {
}
Symbol memset_s {
}
Symbol _memset_s_func {
}
Symbol strcat {
}
Symbol strchr {
}
Symbol __strxfrm {
}
Symbol strcoll {
}
Symbol strcspn {
}
Symbol strerrorIf {
}
Symbol _func_symFindSymbol {
}
Symbol statSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol strerror_r {
}
Symbol strlcpy {
}
Symbol snprintf {
}
Symbol strncat {
}
Symbol strncmp {
}
Symbol strncpy {
}
Symbol strpbrk {
}
Symbol strrchr {
}
Symbol strspn {
}
Symbol strstr {
}
Symbol strtok {
}
Symbol strtok_r {
}
Symbol __costate {
}
Symbol strxfrm {
}
Symbol strlcat {
}
Symbol strcasecmp {
}
Symbol strncasecmp {
}
Symbol strdup {
}
Symbol __loctime {
}
Symbol asctime_r {
}
Symbol strftime {
}
Symbol asctime {
}
Symbol _vxworks_asctime_r {
}
Symbol clock {
}
Symbol ctime_r {
}
Symbol localtime {
}
Symbol ctime {
}
Symbol _vxworks_ctime_r {
}
Symbol __daysSinceEpoch {
}
Symbol __julday {
}
Symbol __getTime {
}
Symbol gmtime_r {
}
Symbol gmtime {
}
Symbol _vxworks_gmtime_r {
}
Symbol localtime_r {
}
Symbol __getZoneInfo {
}
Symbol __getDstInfoSub {
}
Symbol _vxworks_localtime_r {
}
Symbol mktime {
}
Symbol getenv_s {
}
Symbol bzero {
}
Symbol __getDstInfo {
}
Symbol time {
}
Symbol clock_gettime {
}
Symbol difftime {
}
Symbol __ulltod {
}
ObjectFile libc_wr.a::assert.o {
	NAME Object file assert.o from archive libc_wr.a
	EXPORTS __assert
	IMPORTS .TOC. fdprintf abort
	DECLARES 
	USES 
}
Module assert.o {
	OBJECT += libc_wr.a::assert.o
}
ObjectFile libc_wr.a::__ctype_tab.o {
	NAME Object file __ctype_tab.o from archive libc_wr.a
	EXPORTS __ctype __ctype_tolower __ctype_toupper
	IMPORTS 
	DECLARES 
	USES 
}
Module __ctype_tab.o {
	OBJECT += libc_wr.a::__ctype_tab.o
}
ObjectFile libc_wr.a::isalnum.o {
	NAME Object file isalnum.o from archive libc_wr.a
	EXPORTS isalnum
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalnum.o {
	OBJECT += libc_wr.a::isalnum.o
}
ObjectFile libc_wr.a::isalpha.o {
	NAME Object file isalpha.o from archive libc_wr.a
	EXPORTS isalpha
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalpha.o {
	OBJECT += libc_wr.a::isalpha.o
}
ObjectFile libc_wr.a::iscntrl.o {
	NAME Object file iscntrl.o from archive libc_wr.a
	EXPORTS iscntrl
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module iscntrl.o {
	OBJECT += libc_wr.a::iscntrl.o
}
ObjectFile libc_wr.a::isdigit.o {
	NAME Object file isdigit.o from archive libc_wr.a
	EXPORTS isdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isdigit.o {
	OBJECT += libc_wr.a::isdigit.o
}
ObjectFile libc_wr.a::isgraph.o {
	NAME Object file isgraph.o from archive libc_wr.a
	EXPORTS isgraph
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isgraph.o {
	OBJECT += libc_wr.a::isgraph.o
}
ObjectFile libc_wr.a::islower.o {
	NAME Object file islower.o from archive libc_wr.a
	EXPORTS islower
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module islower.o {
	OBJECT += libc_wr.a::islower.o
}
ObjectFile libc_wr.a::isprint.o {
	NAME Object file isprint.o from archive libc_wr.a
	EXPORTS isprint
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isprint.o {
	OBJECT += libc_wr.a::isprint.o
}
ObjectFile libc_wr.a::ispunct.o {
	NAME Object file ispunct.o from archive libc_wr.a
	EXPORTS ispunct
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module ispunct.o {
	OBJECT += libc_wr.a::ispunct.o
}
ObjectFile libc_wr.a::isspace.o {
	NAME Object file isspace.o from archive libc_wr.a
	EXPORTS isspace
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isspace.o {
	OBJECT += libc_wr.a::isspace.o
}
ObjectFile libc_wr.a::isupper.o {
	NAME Object file isupper.o from archive libc_wr.a
	EXPORTS isupper
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isupper.o {
	OBJECT += libc_wr.a::isupper.o
}
ObjectFile libc_wr.a::isxdigit.o {
	NAME Object file isxdigit.o from archive libc_wr.a
	EXPORTS isxdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isxdigit.o {
	OBJECT += libc_wr.a::isxdigit.o
}
ObjectFile libc_wr.a::tolower.o {
	NAME Object file tolower.o from archive libc_wr.a
	EXPORTS tolower
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module tolower.o {
	OBJECT += libc_wr.a::tolower.o
}
ObjectFile libc_wr.a::toupper.o {
	NAME Object file toupper.o from archive libc_wr.a
	EXPORTS toupper
	IMPORTS .TOC. __ctype_toupper
	DECLARES 
	USES 
}
Module toupper.o {
	OBJECT += libc_wr.a::toupper.o
}
ObjectFile libc_wr.a::localeconv.o {
	NAME Object file localeconv.o from archive libc_wr.a
	EXPORTS localeconv __locale
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module localeconv.o {
	OBJECT += libc_wr.a::localeconv.o
}
ObjectFile libc_wr.a::setlocale.o {
	NAME Object file setlocale.o from archive libc_wr.a
	EXPORTS setlocale __clocale
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module setlocale.o {
	OBJECT += libc_wr.a::setlocale.o
}
ObjectFile libc_wr.a::longjmp.o {
	NAME Object file longjmp.o from archive libc_wr.a
	EXPORTS _setjmpSetup longjmp
	IMPORTS .TOC. taskIdSelf kernelId _func_rtpSigprocmask taskSuspend __rta_longjmp _func_sigprocmask _sigCtxRtnValSet _sigCtxLoad
	DECLARES 
	USES 
}
Module longjmp.o {
	OBJECT += libc_wr.a::longjmp.o
}
ObjectFile libc_wr.a::clearerr.o {
	NAME Object file clearerr.o from archive libc_wr.a
	EXPORTS clearerr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clearerr.o {
	OBJECT += libc_wr.a::clearerr.o
}
ObjectFile libc_wr.a::fdopen.o {
	NAME Object file fdopen.o from archive libc_wr.a
	EXPORTS fdopen
	IMPORTS .TOC. iosFdMap __sflags stdioFpCreate
	DECLARES 
	USES 
}
Module fdopen.o {
	OBJECT += libc_wr.a::fdopen.o
}
ObjectFile libc_wr.a::feof.o {
	NAME Object file feof.o from archive libc_wr.a
	EXPORTS feof
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module feof.o {
	OBJECT += libc_wr.a::feof.o
}
ObjectFile libc_wr.a::ferror.o {
	NAME Object file ferror.o from archive libc_wr.a
	EXPORTS ferror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ferror.o {
	OBJECT += libc_wr.a::ferror.o
}
ObjectFile libc_wr.a::fflush.o {
	NAME Object file fflush.o from archive libc_wr.a
	EXPORTS __sflush fflush
	IMPORTS .TOC. __swrite __errno
	DECLARES 
	USES 
}
Module fflush.o {
	OBJECT += libc_wr.a::fflush.o
}
ObjectFile libc_wr.a::fgetc.o {
	NAME Object file fgetc.o from archive libc_wr.a
	EXPORTS fgetc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module fgetc.o {
	OBJECT += libc_wr.a::fgetc.o
}
ObjectFile libc_wr.a::fgetpos.o {
	NAME Object file fgetpos.o from archive libc_wr.a
	EXPORTS fgetpos
	IMPORTS .TOC. ftell
	DECLARES 
	USES 
}
Module fgetpos.o {
	OBJECT += libc_wr.a::fgetpos.o
}
ObjectFile libc_wr.a::fgets.o {
	NAME Object file fgets.o from archive libc_wr.a
	EXPORTS fgets
	IMPORTS .TOC. __srefill memchr bcopy
	DECLARES 
	USES 
}
Module fgets.o {
	OBJECT += libc_wr.a::fgets.o
}
ObjectFile libc_wr.a::fileno.o {
	NAME Object file fileno.o from archive libc_wr.a
	EXPORTS fileno
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fileno.o {
	OBJECT += libc_wr.a::fileno.o
}
ObjectFile libc_wr.a::flags.o {
	NAME Object file flags.o from archive libc_wr.a
	EXPORTS __sflags
	IMPORTS .TOC. __errno
	DECLARES 
	USES 
}
Module flags.o {
	OBJECT += libc_wr.a::flags.o
}
ObjectFile libc_wr.a::fopen.o {
	NAME Object file fopen.o from archive libc_wr.a
	EXPORTS fopen
	IMPORTS .TOC. __sflags stdioFpCreate open stdioFpDestroy __sseek
	DECLARES 
	USES 
}
Module fopen.o {
	OBJECT += libc_wr.a::fopen.o
}
ObjectFile libc_wr.a::fputc.o {
	NAME Object file fputc.o from archive libc_wr.a
	EXPORTS fputc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module fputc.o {
	OBJECT += libc_wr.a::fputc.o
}
ObjectFile libc_wr.a::fputs.o {
	NAME Object file fputs.o from archive libc_wr.a
	EXPORTS fputs
	IMPORTS .TOC. strlen __sfvwrite
	DECLARES 
	USES 
}
Module fputs.o {
	OBJECT += libc_wr.a::fputs.o
}
ObjectFile libc_wr.a::fread.o {
	NAME Object file fread.o from archive libc_wr.a
	EXPORTS fread
	IMPORTS .TOC. bcopy __srefill
	DECLARES 
	USES 
}
Module fread.o {
	OBJECT += libc_wr.a::fread.o
}
ObjectFile libc_wr.a::fsetpos.o {
	NAME Object file fsetpos.o from archive libc_wr.a
	EXPORTS fsetpos
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module fsetpos.o {
	OBJECT += libc_wr.a::fsetpos.o
}
ObjectFile libc_wr.a::ftell.o {
	NAME Object file ftell.o from archive libc_wr.a
	EXPORTS ftell
	IMPORTS .TOC. __sseek
	DECLARES 
	USES 
}
Module ftell.o {
	OBJECT += libc_wr.a::ftell.o
}
ObjectFile libc_wr.a::fvwrite.o {
	NAME Object file fvwrite.o from archive libc_wr.a
	EXPORTS __sfvwrite
	IMPORTS .TOC. __swsetup __swrite bcopy fflush memchr
	DECLARES 
	USES 
}
Module fvwrite.o {
	OBJECT += libc_wr.a::fvwrite.o
}
ObjectFile libc_wr.a::fwrite.o {
	NAME Object file fwrite.o from archive libc_wr.a
	EXPORTS fwrite
	IMPORTS .TOC. __sfvwrite
	DECLARES 
	USES 
}
Module fwrite.o {
	OBJECT += libc_wr.a::fwrite.o
}
ObjectFile libc_wr.a::getc.o {
	NAME Object file getc.o from archive libc_wr.a
	EXPORTS getc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module getc.o {
	OBJECT += libc_wr.a::getc.o
}
ObjectFile libc_wr.a::getchar.o {
	NAME Object file getchar.o from archive libc_wr.a
	EXPORTS getchar
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module getchar.o {
	OBJECT += libc_wr.a::getchar.o
}
ObjectFile libc_wr.a::gets.o {
	NAME Object file gets.o from archive libc_wr.a
	EXPORTS gets
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module gets.o {
	OBJECT += libc_wr.a::gets.o
}
ObjectFile libc_wr.a::getw.o {
	NAME Object file getw.o from archive libc_wr.a
	EXPORTS getw
	IMPORTS .TOC. fread
	DECLARES 
	USES 
}
Module getw.o {
	OBJECT += libc_wr.a::getw.o
}
ObjectFile libc_wr.a::perror.o {
	NAME Object file perror.o from archive libc_wr.a
	EXPORTS perror
	IMPORTS .TOC. __stderr fprintf __errno strerror
	DECLARES 
	USES 
}
Module perror.o {
	OBJECT += libc_wr.a::perror.o
}
ObjectFile libc_wr.a::putc.o {
	NAME Object file putc.o from archive libc_wr.a
	EXPORTS putc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module putc.o {
	OBJECT += libc_wr.a::putc.o
}
ObjectFile libc_wr.a::putchar.o {
	NAME Object file putchar.o from archive libc_wr.a
	EXPORTS putchar
	IMPORTS .TOC. __stdout __swbuf
	DECLARES 
	USES 
}
Module putchar.o {
	OBJECT += libc_wr.a::putchar.o
}
ObjectFile libc_wr.a::putw.o {
	NAME Object file putw.o from archive libc_wr.a
	EXPORTS putw
	IMPORTS .TOC. fwrite
	DECLARES 
	USES 
}
Module putw.o {
	OBJECT += libc_wr.a::putw.o
}
ObjectFile libc_wr.a::puts.o {
	NAME Object file puts.o from archive libc_wr.a
	EXPORTS puts
	IMPORTS .TOC. strlen __stdout __sfvwrite
	DECLARES 
	USES 
}
Module puts.o {
	OBJECT += libc_wr.a::puts.o
}
ObjectFile libc_wr.a::rewind.o {
	NAME Object file rewind.o from archive libc_wr.a
	EXPORTS rewind
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module rewind.o {
	OBJECT += libc_wr.a::rewind.o
}
ObjectFile libc_wr.a::rget.o {
	NAME Object file rget.o from archive libc_wr.a
	EXPORTS __srget
	IMPORTS .TOC. __srefill
	DECLARES 
	USES 
}
Module rget.o {
	OBJECT += libc_wr.a::rget.o
}
ObjectFile libc_wr.a::setbuf.o {
	NAME Object file setbuf.o from archive libc_wr.a
	EXPORTS setbuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuf.o {
	OBJECT += libc_wr.a::setbuf.o
}
ObjectFile libc_wr.a::setbuffer.o {
	NAME Object file setbuffer.o from archive libc_wr.a
	EXPORTS setbuffer setlinebuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuffer.o {
	OBJECT += libc_wr.a::setbuffer.o
}
ObjectFile libc_wr.a::stdio.o {
	NAME Object file stdio.o from archive libc_wr.a
	EXPORTS __sread __swrite __sseek __sclose
	IMPORTS .TOC. read lseek write close
	DECLARES 
	USES 
}
Module stdio.o {
	OBJECT += libc_wr.a::stdio.o
}
ObjectFile libc_wr.a::tmpnam.o {
	NAME Object file tmpnam.o from archive libc_wr.a
	EXPORTS tmpnam
	IMPORTS .TOC. strcpy strlen
	DECLARES 
	USES 
}
Module tmpnam.o {
	OBJECT += libc_wr.a::tmpnam.o
}
ObjectFile libc_wr.a::tmpfile.o {
	NAME Object file tmpfile.o from archive libc_wr.a
	EXPORTS tmpfile
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module tmpfile.o {
	OBJECT += libc_wr.a::tmpfile.o
}
ObjectFile libc_wr.a::wbuf.o {
	NAME Object file wbuf.o from archive libc_wr.a
	EXPORTS __swbuf
	IMPORTS .TOC. __swsetup fflush
	DECLARES 
	USES 
}
Module wbuf.o {
	OBJECT += libc_wr.a::wbuf.o
}
ObjectFile libc_wr.a::vfprintf.o {
	NAME Object file vfprintf.o from archive libc_wr.a
	EXPORTS vfprintf
	IMPORTS .TOC. __swsetup handleInit fioFormatV fflush handleTerminate __swbuf
	DECLARES 
	USES 
}
Module vfprintf.o {
	OBJECT += libc_wr.a::vfprintf.o
}
ObjectFile libc_wr.a::fprintf.o {
	NAME Object file fprintf.o from archive libc_wr.a
	EXPORTS fprintf
	IMPORTS .TOC. vfprintf
	DECLARES 
	USES 
}
Module fprintf.o {
	OBJECT += libc_wr.a::fprintf.o
}
ObjectFile libc_wr.a::fscanf.o {
	NAME Object file fscanf.o from archive libc_wr.a
	EXPORTS fscanf
	IMPORTS .TOC. fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module fscanf.o {
	OBJECT += libc_wr.a::fscanf.o
}
ObjectFile libc_wr.a::scanf.o {
	NAME Object file scanf.o from archive libc_wr.a
	EXPORTS scanf
	IMPORTS .TOC. __stdin fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module scanf.o {
	OBJECT += libc_wr.a::scanf.o
}
ObjectFile libc_wr.a::stdioFuncBind.o {
	NAME Object file stdioFuncBind.o from archive libc_wr.a
	EXPORTS _func_fclose
	IMPORTS 
	DECLARES 
	USES 
}
Module stdioFuncBind.o {
	OBJECT += libc_wr.a::stdioFuncBind.o
}
ObjectFile libc_wr.a::fclose.o {
	NAME Object file fclose.o from archive libc_wr.a
	EXPORTS fclose
	IMPORTS .TOC. __errno __sflush __sclose free stdioFpDestroy
	DECLARES 
	USES 
}
Module fclose.o {
	OBJECT += libc_wr.a::fclose.o
}
ObjectFile libc_wr.a::freopen.o {
	NAME Object file freopen.o from archive libc_wr.a
	EXPORTS freopen
	IMPORTS .TOC. __sflags fclose __sflush __sclose open __errno free stdioFpDestroy
	DECLARES 
	USES 
}
Module freopen.o {
	OBJECT += libc_wr.a::freopen.o
}
ObjectFile libc_wr.a::fseek.o {
	NAME Object file fseek.o from archive libc_wr.a
	EXPORTS fseek
	IMPORTS .TOC. __sseek __errno __smakebuf ioctl free __srefill __sflush
	DECLARES 
	USES 
}
Module fseek.o {
	OBJECT += libc_wr.a::fseek.o
}
ObjectFile libc_wr.a::makebuf.o {
	NAME Object file makebuf.o from archive libc_wr.a
	EXPORTS __smakebuf
	IMPORTS .TOC. ioctl malloc isatty
	DECLARES 
	USES 
}
Module makebuf.o {
	OBJECT += libc_wr.a::makebuf.o
}
ObjectFile libc_wr.a::refill.o {
	NAME Object file refill.o from archive libc_wr.a
	EXPORTS __srefill
	IMPORTS .TOC. __sflush __errno free __smakebuf __sread
	DECLARES 
	USES 
}
Module refill.o {
	OBJECT += libc_wr.a::refill.o
}
ObjectFile libc_wr.a::setvbuf.o {
	NAME Object file setvbuf.o from archive libc_wr.a
	EXPORTS setvbuf
	IMPORTS .TOC. __sflush free
	DECLARES 
	USES 
}
Module setvbuf.o {
	OBJECT += libc_wr.a::setvbuf.o
}
ObjectFile libc_wr.a::stdioLib.o {
	NAME Object file stdioLib.o from archive libc_wr.a
	EXPORTS stdioInit stdioFpCreate stdioFpDestroy __stdin __stdout __stderr stdioFp
	IMPORTS .TOC. fclose _func_fclose malloc taskIdSelf handleInit handleTerminate free _func_taskDeleteHookAdd taskCreateHookInit taskDeleteHookAdd
	DECLARES 
	USES 
}
Module stdioLib.o {
	OBJECT += libc_wr.a::stdioLib.o
}
ObjectFile libc_wr.a::stdioShow.o {
	NAME Object file stdioShow.o from archive libc_wr.a
	EXPORTS stdioShowInit stdioShow
	IMPORTS .TOC. handleShowConnect printf
	DECLARES 
	USES 
}
Module stdioShow.o {
	OBJECT += libc_wr.a::stdioShow.o
}
ObjectFile libc_wr.a::ungetc.o {
	NAME Object file ungetc.o from archive libc_wr.a
	EXPORTS ungetc
	IMPORTS .TOC. malloc realloc bcopy __sflush
	DECLARES 
	USES 
}
Module ungetc.o {
	OBJECT += libc_wr.a::ungetc.o
}
ObjectFile libc_wr.a::wsetup.o {
	NAME Object file wsetup.o from archive libc_wr.a
	EXPORTS __swsetup
	IMPORTS .TOC. free __smakebuf
	DECLARES 
	USES 
}
Module wsetup.o {
	OBJECT += libc_wr.a::wsetup.o
}
ObjectFile libc_wr.a::abort.o {
	NAME Object file abort.o from archive libc_wr.a
	EXPORTS abort
	IMPORTS .TOC. raise exit
	DECLARES 
	USES 
}
Module abort.o {
	OBJECT += libc_wr.a::abort.o
}
ObjectFile libc_wr.a::abs.o {
	NAME Object file abs.o from archive libc_wr.a
	EXPORTS abs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module abs.o {
	OBJECT += libc_wr.a::abs.o
}
ObjectFile libc_wr.a::atexit.o {
	NAME Object file atexit.o from archive libc_wr.a
	EXPORTS atexit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module atexit.o {
	OBJECT += libc_wr.a::atexit.o
}
ObjectFile libc_wr.a::atof.o {
	NAME Object file atof.o from archive libc_wr.a
	EXPORTS atof
	IMPORTS .TOC. strtod
	DECLARES 
	USES 
}
Module atof.o {
	OBJECT += libc_wr.a::atof.o
}
ObjectFile libc_wr.a::atoi.o {
	NAME Object file atoi.o from archive libc_wr.a
	EXPORTS atoi
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atoi.o {
	OBJECT += libc_wr.a::atoi.o
}
ObjectFile libc_wr.a::atol.o {
	NAME Object file atol.o from archive libc_wr.a
	EXPORTS atol
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atol.o {
	OBJECT += libc_wr.a::atol.o
}
ObjectFile libc_wr.a::bsearch.o {
	NAME Object file bsearch.o from archive libc_wr.a
	EXPORTS bsearch
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module bsearch.o {
	OBJECT += libc_wr.a::bsearch.o
}
ObjectFile libc_wr.a::div.o {
	NAME Object file div.o from archive libc_wr.a
	EXPORTS div_r div
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module div.o {
	OBJECT += libc_wr.a::div.o
}
ObjectFile libc_wr.a::labs.o {
	NAME Object file labs.o from archive libc_wr.a
	EXPORTS labs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module labs.o {
	OBJECT += libc_wr.a::labs.o
}
ObjectFile libc_wr.a::ldiv.o {
	NAME Object file ldiv.o from archive libc_wr.a
	EXPORTS ldiv_r ldiv
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ldiv.o {
	OBJECT += libc_wr.a::ldiv.o
}
ObjectFile libc_wr.a::multibyte.o {
	NAME Object file multibyte.o from archive libc_wr.a
	EXPORTS mblen mbtowc wctomb mbstowcs wcstombs
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module multibyte.o {
	OBJECT += libc_wr.a::multibyte.o
}
ObjectFile libc_wr.a::qsort.o {
	NAME Object file qsort.o from archive libc_wr.a
	EXPORTS qsort
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module qsort.o {
	OBJECT += libc_wr.a::qsort.o
}
ObjectFile libc_wr.a::stdrand.o {
	NAME Object file stdrand.o from archive libc_wr.a
	EXPORTS rand _Randseed srand
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module stdrand.o {
	OBJECT += libc_wr.a::stdrand.o
}
ObjectFile libc_wr.a::strtol.o {
	NAME Object file strtol.o from archive libc_wr.a
	EXPORTS strtol
	IMPORTS .TOC. __errno __ctype
	DECLARES 
	USES 
}
Module strtol.o {
	OBJECT += libc_wr.a::strtol.o
}
ObjectFile libc_wr.a::strtoul.o {
	NAME Object file strtoul.o from archive libc_wr.a
	EXPORTS strtoul
	IMPORTS .TOC. __ctype __errno
	DECLARES 
	USES 
}
Module strtoul.o {
	OBJECT += libc_wr.a::strtoul.o
}
ObjectFile libc_wr.a::system.o {
	NAME Object file system.o from archive libc_wr.a
	EXPORTS system
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module system.o {
	OBJECT += libc_wr.a::system.o
}
ObjectFile libc_wr.a::strtod.o {
	NAME Object file strtod.o from archive libc_wr.a
	EXPORTS strtod
	IMPORTS .TOC. __ctype ldexp
	DECLARES 
	USES 
}
Module strtod.o {
	OBJECT += libc_wr.a::strtod.o
}
ObjectFile libc_wr.a::strtoll.o {
	NAME Object file strtoll.o from archive libc_wr.a
	EXPORTS strtoll
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoll.o {
	OBJECT += libc_wr.a::strtoll.o
}
ObjectFile libc_wr.a::strtoull.o {
	NAME Object file strtoull.o from archive libc_wr.a
	EXPORTS strtoull
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoull.o {
	OBJECT += libc_wr.a::strtoull.o
}
ObjectFile libc_wr.a::memchr.o {
	NAME Object file memchr.o from archive libc_wr.a
	EXPORTS memchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memchr.o {
	OBJECT += libc_wr.a::memchr.o
}
ObjectFile libc_wr.a::memcmp.o {
	NAME Object file memcmp.o from archive libc_wr.a
	EXPORTS memcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memcmp.o {
	OBJECT += libc_wr.a::memcmp.o
}
ObjectFile libc_wr.a::memcpy.o {
	NAME Object file memcpy.o from archive libc_wr.a
	EXPORTS memcpy
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memcpy.o {
	OBJECT += libc_wr.a::memcpy.o
}
ObjectFile libc_wr.a::memmove.o {
	NAME Object file memmove.o from archive libc_wr.a
	EXPORTS memmove
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memmove.o {
	OBJECT += libc_wr.a::memmove.o
}
ObjectFile libc_wr.a::memset.o {
	NAME Object file memset.o from archive libc_wr.a
	EXPORTS memset
	IMPORTS .TOC. bfill
	DECLARES 
	USES 
}
Module memset.o {
	OBJECT += libc_wr.a::memset.o
}
ObjectFile libc_wr.a::memset_s.o {
	NAME Object file memset_s.o from archive libc_wr.a
	EXPORTS __internal_memset_s memset_s _memset_s_func
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memset_s.o {
	OBJECT += libc_wr.a::memset_s.o
}
ObjectFile libc_wr.a::strcat.o {
	NAME Object file strcat.o from archive libc_wr.a
	EXPORTS strcat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcat.o {
	OBJECT += libc_wr.a::strcat.o
}
ObjectFile libc_wr.a::strchr.o {
	NAME Object file strchr.o from archive libc_wr.a
	EXPORTS strchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strchr.o {
	OBJECT += libc_wr.a::strchr.o
}
ObjectFile libc_wr.a::strcmp.o {
	NAME Object file strcmp.o from archive libc_wr.a
	EXPORTS strcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcmp.o {
	OBJECT += libc_wr.a::strcmp.o
}
ObjectFile libc_wr.a::strcoll.o {
	NAME Object file strcoll.o from archive libc_wr.a
	EXPORTS strcoll
	IMPORTS .TOC. __strxfrm memcmp
	DECLARES 
	USES 
}
Module strcoll.o {
	OBJECT += libc_wr.a::strcoll.o
}
ObjectFile libc_wr.a::strcpy.o {
	NAME Object file strcpy.o from archive libc_wr.a
	EXPORTS strcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcpy.o {
	OBJECT += libc_wr.a::strcpy.o
}
ObjectFile libc_wr.a::strcspn.o {
	NAME Object file strcspn.o from archive libc_wr.a
	EXPORTS strcspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcspn.o {
	OBJECT += libc_wr.a::strcspn.o
}
ObjectFile libc_wr.a::strerror.o {
	NAME Object file strerror.o from archive libc_wr.a
	EXPORTS strerrorIf strerror_r strerror
	IMPORTS .TOC. _func_symFindSymbol statSymTbl _func_symNameGet _func_symValueGet strlcpy snprintf
	DECLARES 
	USES 
}
Module strerror.o {
	OBJECT += libc_wr.a::strerror.o
}
ObjectFile libc_wr.a::strlen.o {
	NAME Object file strlen.o from archive libc_wr.a
	EXPORTS strlen
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlen.o {
	OBJECT += libc_wr.a::strlen.o
}
ObjectFile libc_wr.a::strncat.o {
	NAME Object file strncat.o from archive libc_wr.a
	EXPORTS strncat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncat.o {
	OBJECT += libc_wr.a::strncat.o
}
ObjectFile libc_wr.a::strncmp.o {
	NAME Object file strncmp.o from archive libc_wr.a
	EXPORTS strncmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncmp.o {
	OBJECT += libc_wr.a::strncmp.o
}
ObjectFile libc_wr.a::strncpy.o {
	NAME Object file strncpy.o from archive libc_wr.a
	EXPORTS strncpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncpy.o {
	OBJECT += libc_wr.a::strncpy.o
}
ObjectFile libc_wr.a::strpbrk.o {
	NAME Object file strpbrk.o from archive libc_wr.a
	EXPORTS strpbrk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strpbrk.o {
	OBJECT += libc_wr.a::strpbrk.o
}
ObjectFile libc_wr.a::strrchr.o {
	NAME Object file strrchr.o from archive libc_wr.a
	EXPORTS strrchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strrchr.o {
	OBJECT += libc_wr.a::strrchr.o
}
ObjectFile libc_wr.a::strspn.o {
	NAME Object file strspn.o from archive libc_wr.a
	EXPORTS strspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strspn.o {
	OBJECT += libc_wr.a::strspn.o
}
ObjectFile libc_wr.a::strstr.o {
	NAME Object file strstr.o from archive libc_wr.a
	EXPORTS strstr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strstr.o {
	OBJECT += libc_wr.a::strstr.o
}
ObjectFile libc_wr.a::strtok.o {
	NAME Object file strtok.o from archive libc_wr.a
	EXPORTS strtok
	IMPORTS .TOC. strtok_r
	DECLARES 
	USES 
}
Module strtok.o {
	OBJECT += libc_wr.a::strtok.o
}
ObjectFile libc_wr.a::strtok_r.o {
	NAME Object file strtok_r.o from archive libc_wr.a
	EXPORTS strtok_r
	IMPORTS .TOC. strspn strpbrk
	DECLARES 
	USES 
}
Module strtok_r.o {
	OBJECT += libc_wr.a::strtok_r.o
}
ObjectFile libc_wr.a::strxfrm.o {
	NAME Object file strxfrm.o from archive libc_wr.a
	EXPORTS __strxfrm strxfrm
	IMPORTS .TOC. __costate
	DECLARES 
	USES 
}
Module strxfrm.o {
	OBJECT += libc_wr.a::strxfrm.o
}
ObjectFile libc_wr.a::xstate.o {
	NAME Object file xstate.o from archive libc_wr.a
	EXPORTS __costate
	IMPORTS 
	DECLARES 
	USES 
}
Module xstate.o {
	OBJECT += libc_wr.a::xstate.o
}
ObjectFile libc_wr.a::strlcat.o {
	NAME Object file strlcat.o from archive libc_wr.a
	EXPORTS strlcat
	IMPORTS .TOC. strlen
	DECLARES 
	USES 
}
Module strlcat.o {
	OBJECT += libc_wr.a::strlcat.o
}
ObjectFile libc_wr.a::strlcpy.o {
	NAME Object file strlcpy.o from archive libc_wr.a
	EXPORTS strlcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlcpy.o {
	OBJECT += libc_wr.a::strlcpy.o
}
ObjectFile libc_wr.a::strcasecmp.o {
	NAME Object file strcasecmp.o from archive libc_wr.a
	EXPORTS strcasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strcasecmp.o {
	OBJECT += libc_wr.a::strcasecmp.o
}
ObjectFile libc_wr.a::strncasecmp.o {
	NAME Object file strncasecmp.o from archive libc_wr.a
	EXPORTS strncasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strncasecmp.o {
	OBJECT += libc_wr.a::strncasecmp.o
}
ObjectFile libc_wr.a::strdup.o {
	NAME Object file strdup.o from archive libc_wr.a
	EXPORTS strdup
	IMPORTS .TOC. strlen malloc strcpy
	DECLARES 
	USES 
}
Module strdup.o {
	OBJECT += libc_wr.a::strdup.o
}
ObjectFile libc_wr.a::locTime.o {
	NAME Object file locTime.o from archive libc_wr.a
	EXPORTS __loctime
	IMPORTS 
	DECLARES 
	USES 
}
Module locTime.o {
	OBJECT += libc_wr.a::locTime.o
}
ObjectFile libc_wr.a::asctime.o {
	NAME Object file asctime.o from archive libc_wr.a
	EXPORTS asctime_r asctime _vxworks_asctime_r
	IMPORTS .TOC. strftime
	DECLARES 
	USES 
}
Module asctime.o {
	OBJECT += libc_wr.a::asctime.o
}
ObjectFile libc_wr.a::clock.o {
	NAME Object file clock.o from archive libc_wr.a
	EXPORTS clock
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clock.o {
	OBJECT += libc_wr.a::clock.o
}
ObjectFile libc_wr.a::ctime.o {
	NAME Object file ctime.o from archive libc_wr.a
	EXPORTS ctime_r ctime _vxworks_ctime_r
	IMPORTS .TOC. localtime asctime_r _vxworks_asctime_r
	DECLARES 
	USES 
}
Module ctime.o {
	OBJECT += libc_wr.a::ctime.o
}
ObjectFile libc_wr.a::gmtime.o {
	NAME Object file gmtime.o from archive libc_wr.a
	EXPORTS __daysSinceEpoch __julday __getTime gmtime_r gmtime _vxworks_gmtime_r
	IMPORTS .TOC. ldiv_r
	DECLARES 
	USES 
}
Module gmtime.o {
	OBJECT += libc_wr.a::gmtime.o
}
ObjectFile libc_wr.a::localtime.o {
	NAME Object file localtime.o from archive libc_wr.a
	EXPORTS localtime_r localtime _vxworks_localtime_r
	IMPORTS .TOC. __loctime __getZoneInfo atoi __getTime __getDstInfoSub
	DECLARES 
	USES 
}
Module localtime.o {
	OBJECT += libc_wr.a::localtime.o
}
ObjectFile libc_wr.a::mktime.o {
	NAME Object file mktime.o from archive libc_wr.a
	EXPORTS mktime
	IMPORTS .TOC. __julday __daysSinceEpoch __loctime __getDstInfoSub __getZoneInfo atoi
	DECLARES 
	USES 
}
Module mktime.o {
	OBJECT += libc_wr.a::mktime.o
}
ObjectFile libc_wr.a::strftime.o {
	NAME Object file strftime.o from archive libc_wr.a
	EXPORTS __getZoneInfo strftime __getDstInfoSub __getDstInfo
	IMPORTS .TOC. getenv_s strpbrk strncpy strcmp strlen memcpy abs __loctime strtok_r bzero atoi
	DECLARES 
	USES 
}
Module strftime.o {
	OBJECT += libc_wr.a::strftime.o
}
ObjectFile libc_wr.a::time.o {
	NAME Object file time.o from archive libc_wr.a
	EXPORTS time
	IMPORTS .TOC. clock_gettime
	DECLARES 
	USES 
}
Module time.o {
	OBJECT += libc_wr.a::time.o
}
ObjectFile libc_wr.a::difftime.o {
	NAME Object file difftime.o from archive libc_wr.a
	EXPORTS difftime
	IMPORTS .TOC. __ulltod
	DECLARES 
	USES 
}
Module difftime.o {
	OBJECT += libc_wr.a::difftime.o
}
Library libc_wr.a {
	MODULES libc_wr.a::assert.o libc_wr.a::__ctype_tab.o libc_wr.a::isalnum.o libc_wr.a::isalpha.o libc_wr.a::iscntrl.o libc_wr.a::isdigit.o libc_wr.a::isgraph.o libc_wr.a::islower.o libc_wr.a::isprint.o libc_wr.a::ispunct.o libc_wr.a::isspace.o libc_wr.a::isupper.o libc_wr.a::isxdigit.o libc_wr.a::tolower.o libc_wr.a::toupper.o libc_wr.a::localeconv.o libc_wr.a::setlocale.o libc_wr.a::longjmp.o libc_wr.a::clearerr.o libc_wr.a::fdopen.o libc_wr.a::feof.o libc_wr.a::ferror.o libc_wr.a::fflush.o libc_wr.a::fgetc.o libc_wr.a::fgetpos.o libc_wr.a::fgets.o libc_wr.a::fileno.o libc_wr.a::flags.o libc_wr.a::fopen.o libc_wr.a::fputc.o libc_wr.a::fputs.o libc_wr.a::fread.o libc_wr.a::fsetpos.o libc_wr.a::ftell.o libc_wr.a::fvwrite.o libc_wr.a::fwrite.o libc_wr.a::getc.o libc_wr.a::getchar.o libc_wr.a::gets.o libc_wr.a::getw.o libc_wr.a::perror.o libc_wr.a::putc.o libc_wr.a::putchar.o libc_wr.a::putw.o libc_wr.a::puts.o libc_wr.a::rewind.o libc_wr.a::rget.o libc_wr.a::setbuf.o libc_wr.a::setbuffer.o libc_wr.a::stdio.o libc_wr.a::tmpnam.o libc_wr.a::tmpfile.o libc_wr.a::wbuf.o libc_wr.a::vfprintf.o libc_wr.a::fprintf.o libc_wr.a::fscanf.o libc_wr.a::scanf.o libc_wr.a::stdioFuncBind.o libc_wr.a::fclose.o libc_wr.a::freopen.o libc_wr.a::fseek.o libc_wr.a::makebuf.o libc_wr.a::refill.o libc_wr.a::setvbuf.o libc_wr.a::stdioLib.o libc_wr.a::stdioShow.o libc_wr.a::ungetc.o libc_wr.a::wsetup.o libc_wr.a::abort.o libc_wr.a::abs.o libc_wr.a::atexit.o libc_wr.a::atof.o libc_wr.a::atoi.o libc_wr.a::atol.o libc_wr.a::bsearch.o libc_wr.a::div.o libc_wr.a::labs.o libc_wr.a::ldiv.o libc_wr.a::multibyte.o libc_wr.a::qsort.o libc_wr.a::stdrand.o libc_wr.a::strtol.o libc_wr.a::strtoul.o libc_wr.a::system.o libc_wr.a::strtod.o libc_wr.a::strtoll.o libc_wr.a::strtoull.o libc_wr.a::memchr.o libc_wr.a::memcmp.o libc_wr.a::memcpy.o libc_wr.a::memmove.o libc_wr.a::memset.o libc_wr.a::memset_s.o libc_wr.a::strcat.o libc_wr.a::strchr.o libc_wr.a::strcmp.o libc_wr.a::strcoll.o libc_wr.a::strcpy.o libc_wr.a::strcspn.o libc_wr.a::strerror.o libc_wr.a::strlen.o libc_wr.a::strncat.o libc_wr.a::strncmp.o libc_wr.a::strncpy.o libc_wr.a::strpbrk.o libc_wr.a::strrchr.o libc_wr.a::strspn.o libc_wr.a::strstr.o libc_wr.a::strtok.o libc_wr.a::strtok_r.o libc_wr.a::strxfrm.o libc_wr.a::xstate.o libc_wr.a::strlcat.o libc_wr.a::strlcpy.o libc_wr.a::strcasecmp.o libc_wr.a::strncasecmp.o libc_wr.a::strdup.o libc_wr.a::locTime.o libc_wr.a::asctime.o libc_wr.a::clock.o libc_wr.a::ctime.o libc_wr.a::gmtime.o libc_wr.a::localtime.o libc_wr.a::mktime.o libc_wr.a::strftime.o libc_wr.a::time.o libc_wr.a::difftime.o
}
Symbol __assert {
}
Symbol .TOC. {
}
Symbol fdprintf {
}
Symbol abort {
}
Symbol __ctype {
}
Symbol __ctype_tolower {
}
Symbol __ctype_toupper {
}
Symbol isalnum {
}
Symbol isalpha {
}
Symbol iscntrl {
}
Symbol isdigit {
}
Symbol isgraph {
}
Symbol islower {
}
Symbol isprint {
}
Symbol ispunct {
}
Symbol isspace {
}
Symbol isupper {
}
Symbol isxdigit {
}
Symbol tolower {
}
Symbol toupper {
}
Symbol localeconv {
}
Symbol __locale {
}
Symbol setlocale {
}
Symbol strcmp {
}
Symbol __clocale {
}
Symbol _setjmpSetup {
}
Symbol taskIdSelf {
}
Symbol kernelId {
}
Symbol _func_rtpSigprocmask {
}
Symbol longjmp {
}
Symbol taskSuspend {
}
Symbol __rta_longjmp {
}
Symbol _func_sigprocmask {
}
Symbol _sigCtxRtnValSet {
}
Symbol _sigCtxLoad {
}
Symbol clearerr {
}
Symbol fdopen {
}
Symbol iosFdMap {
}
Symbol __sflags {
}
Symbol stdioFpCreate {
}
Symbol feof {
}
Symbol ferror {
}
Symbol __sflush {
}
Symbol __swrite {
}
Symbol fflush {
}
Symbol __errno {
}
Symbol fgetc {
}
Symbol __srget {
}
Symbol fgetpos {
}
Symbol ftell {
}
Symbol fgets {
}
Symbol __srefill {
}
Symbol memchr {
}
Symbol bcopy {
}
Symbol fileno {
}
Symbol fopen {
}
Symbol open {
}
Symbol stdioFpDestroy {
}
Symbol __sseek {
}
Symbol fputc {
}
Symbol __swbuf {
}
Symbol fputs {
}
Symbol strlen {
}
Symbol __sfvwrite {
}
Symbol fread {
}
Symbol fsetpos {
}
Symbol fseek {
}
Symbol __swsetup {
}
Symbol fwrite {
}
Symbol getc {
}
Symbol getchar {
}
Symbol __stdin {
}
Symbol gets {
}
Symbol getw {
}
Symbol perror {
}
Symbol __stderr {
}
Symbol fprintf {
}
Symbol strerror {
}
Symbol putc {
}
Symbol putchar {
}
Symbol __stdout {
}
Symbol putw {
}
Symbol puts {
}
Symbol rewind {
}
Symbol setbuf {
}
Symbol setvbuf {
}
Symbol setbuffer {
}
Symbol setlinebuf {
}
Symbol __sread {
}
Symbol read {
}
Symbol lseek {
}
Symbol write {
}
Symbol __sclose {
}
Symbol close {
}
Symbol tmpnam {
}
Symbol strcpy {
}
Symbol tmpfile {
}
Symbol vfprintf {
}
Symbol handleInit {
}
Symbol fioFormatV {
}
Symbol handleTerminate {
}
Symbol fscanf {
}
Symbol fioScanV {
}
Symbol ungetc {
}
Symbol scanf {
}
Symbol _func_fclose {
}
Symbol fclose {
}
Symbol free {
}
Symbol freopen {
}
Symbol __smakebuf {
}
Symbol ioctl {
}
Symbol malloc {
}
Symbol isatty {
}
Symbol stdioInit {
}
Symbol _func_taskDeleteHookAdd {
}
Symbol taskCreateHookInit {
}
Symbol taskDeleteHookAdd {
}
Symbol stdioFp {
}
Symbol stdioShowInit {
}
Symbol stdioShow {
}
Symbol handleShowConnect {
}
Symbol printf {
}
Symbol realloc {
}
Symbol raise {
}
Symbol exit {
}
Symbol abs {
}
Symbol atexit {
}
Symbol atof {
}
Symbol strtod {
}
Symbol atoi {
}
Symbol strtol {
}
Symbol atol {
}
Symbol bsearch {
}
Symbol div_r {
}
Symbol div {
}
Symbol labs {
}
Symbol ldiv_r {
}
Symbol ldiv {
}
Symbol mblen {
}
Symbol mbtowc {
}
Symbol wctomb {
}
Symbol mbstowcs {
}
Symbol wcstombs {
}
Symbol qsort {
}
Symbol rand {
}
Symbol _Randseed {
}
Symbol srand {
}
Symbol strtoul {
}
Symbol system {
}
Symbol ldexp {
}
Symbol strtoll {
}
Symbol errnoSet {
}
Symbol strtoull {
}
Symbol memcmp {
}
Symbol memcpy {
}
Symbol memmove {
}
Symbol memset {
}
Symbol bfill {
}
Symbol __internal_memset_s {
}
Symbol memset_s {
}
Symbol _memset_s_func {
}
Symbol strcat {
}
Symbol strchr {
}
Symbol __strxfrm {
}
Symbol strcoll {
}
Symbol strcspn {
}
Symbol strerrorIf {
}
Symbol _func_symFindSymbol {
}
Symbol statSymTbl {
}
Symbol _func_symNameGet {
}
Symbol _func_symValueGet {
}
Symbol strerror_r {
}
Symbol strlcpy {
}
Symbol snprintf {
}
Symbol strncat {
}
Symbol strncmp {
}
Symbol strncpy {
}
Symbol strpbrk {
}
Symbol strrchr {
}
Symbol strspn {
}
Symbol strstr {
}
Symbol strtok {
}
Symbol strtok_r {
}
Symbol __costate {
}
Symbol strxfrm {
}
Symbol strlcat {
}
Symbol strcasecmp {
}
Symbol strncasecmp {
}
Symbol strdup {
}
Symbol __loctime {
}
Symbol asctime_r {
}
Symbol strftime {
}
Symbol asctime {
}
Symbol _vxworks_asctime_r {
}
Symbol clock {
}
Symbol ctime_r {
}
Symbol localtime {
}
Symbol ctime {
}
Symbol _vxworks_ctime_r {
}
Symbol __daysSinceEpoch {
}
Symbol __julday {
}
Symbol __getTime {
}
Symbol gmtime_r {
}
Symbol gmtime {
}
Symbol _vxworks_gmtime_r {
}
Symbol localtime_r {
}
Symbol __getZoneInfo {
}
Symbol __getDstInfoSub {
}
Symbol _vxworks_localtime_r {
}
Symbol mktime {
}
Symbol getenv_s {
}
Symbol bzero {
}
Symbol __getDstInfo {
}
Symbol time {
}
Symbol clock_gettime {
}
Symbol difftime {
}
Symbol __ulltod {
}
ObjectFile libc_wr.a::assert.o {
	NAME Object file assert.o from archive libc_wr.a
	EXPORTS __assert
	IMPORTS .TOC. fdprintf abort
	DECLARES 
	USES 
}
Module assert.o {
	OBJECT += libc_wr.a::assert.o
}
ObjectFile libc_wr.a::__ctype_tab.o {
	NAME Object file __ctype_tab.o from archive libc_wr.a
	EXPORTS __ctype __ctype_tolower __ctype_toupper
	IMPORTS 
	DECLARES 
	USES 
}
Module __ctype_tab.o {
	OBJECT += libc_wr.a::__ctype_tab.o
}
ObjectFile libc_wr.a::isalnum.o {
	NAME Object file isalnum.o from archive libc_wr.a
	EXPORTS isalnum
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalnum.o {
	OBJECT += libc_wr.a::isalnum.o
}
ObjectFile libc_wr.a::isalpha.o {
	NAME Object file isalpha.o from archive libc_wr.a
	EXPORTS isalpha
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isalpha.o {
	OBJECT += libc_wr.a::isalpha.o
}
ObjectFile libc_wr.a::iscntrl.o {
	NAME Object file iscntrl.o from archive libc_wr.a
	EXPORTS iscntrl
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module iscntrl.o {
	OBJECT += libc_wr.a::iscntrl.o
}
ObjectFile libc_wr.a::isdigit.o {
	NAME Object file isdigit.o from archive libc_wr.a
	EXPORTS isdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isdigit.o {
	OBJECT += libc_wr.a::isdigit.o
}
ObjectFile libc_wr.a::isgraph.o {
	NAME Object file isgraph.o from archive libc_wr.a
	EXPORTS isgraph
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isgraph.o {
	OBJECT += libc_wr.a::isgraph.o
}
ObjectFile libc_wr.a::islower.o {
	NAME Object file islower.o from archive libc_wr.a
	EXPORTS islower
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module islower.o {
	OBJECT += libc_wr.a::islower.o
}
ObjectFile libc_wr.a::isprint.o {
	NAME Object file isprint.o from archive libc_wr.a
	EXPORTS isprint
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isprint.o {
	OBJECT += libc_wr.a::isprint.o
}
ObjectFile libc_wr.a::ispunct.o {
	NAME Object file ispunct.o from archive libc_wr.a
	EXPORTS ispunct
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module ispunct.o {
	OBJECT += libc_wr.a::ispunct.o
}
ObjectFile libc_wr.a::isspace.o {
	NAME Object file isspace.o from archive libc_wr.a
	EXPORTS isspace
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isspace.o {
	OBJECT += libc_wr.a::isspace.o
}
ObjectFile libc_wr.a::isupper.o {
	NAME Object file isupper.o from archive libc_wr.a
	EXPORTS isupper
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isupper.o {
	OBJECT += libc_wr.a::isupper.o
}
ObjectFile libc_wr.a::isxdigit.o {
	NAME Object file isxdigit.o from archive libc_wr.a
	EXPORTS isxdigit
	IMPORTS .TOC. __ctype
	DECLARES 
	USES 
}
Module isxdigit.o {
	OBJECT += libc_wr.a::isxdigit.o
}
ObjectFile libc_wr.a::tolower.o {
	NAME Object file tolower.o from archive libc_wr.a
	EXPORTS tolower
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module tolower.o {
	OBJECT += libc_wr.a::tolower.o
}
ObjectFile libc_wr.a::toupper.o {
	NAME Object file toupper.o from archive libc_wr.a
	EXPORTS toupper
	IMPORTS .TOC. __ctype_toupper
	DECLARES 
	USES 
}
Module toupper.o {
	OBJECT += libc_wr.a::toupper.o
}
ObjectFile libc_wr.a::localeconv.o {
	NAME Object file localeconv.o from archive libc_wr.a
	EXPORTS localeconv __locale
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module localeconv.o {
	OBJECT += libc_wr.a::localeconv.o
}
ObjectFile libc_wr.a::setlocale.o {
	NAME Object file setlocale.o from archive libc_wr.a
	EXPORTS setlocale __clocale
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module setlocale.o {
	OBJECT += libc_wr.a::setlocale.o
}
ObjectFile libc_wr.a::longjmp.o {
	NAME Object file longjmp.o from archive libc_wr.a
	EXPORTS _setjmpSetup longjmp
	IMPORTS .TOC. taskIdSelf kernelId _func_rtpSigprocmask taskSuspend __rta_longjmp _func_sigprocmask _sigCtxRtnValSet _sigCtxLoad
	DECLARES 
	USES 
}
Module longjmp.o {
	OBJECT += libc_wr.a::longjmp.o
}
ObjectFile libc_wr.a::clearerr.o {
	NAME Object file clearerr.o from archive libc_wr.a
	EXPORTS clearerr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clearerr.o {
	OBJECT += libc_wr.a::clearerr.o
}
ObjectFile libc_wr.a::fdopen.o {
	NAME Object file fdopen.o from archive libc_wr.a
	EXPORTS fdopen
	IMPORTS .TOC. iosFdMap __sflags stdioFpCreate
	DECLARES 
	USES 
}
Module fdopen.o {
	OBJECT += libc_wr.a::fdopen.o
}
ObjectFile libc_wr.a::feof.o {
	NAME Object file feof.o from archive libc_wr.a
	EXPORTS feof
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module feof.o {
	OBJECT += libc_wr.a::feof.o
}
ObjectFile libc_wr.a::ferror.o {
	NAME Object file ferror.o from archive libc_wr.a
	EXPORTS ferror
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ferror.o {
	OBJECT += libc_wr.a::ferror.o
}
ObjectFile libc_wr.a::fflush.o {
	NAME Object file fflush.o from archive libc_wr.a
	EXPORTS __sflush fflush
	IMPORTS .TOC. __swrite __errno
	DECLARES 
	USES 
}
Module fflush.o {
	OBJECT += libc_wr.a::fflush.o
}
ObjectFile libc_wr.a::fgetc.o {
	NAME Object file fgetc.o from archive libc_wr.a
	EXPORTS fgetc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module fgetc.o {
	OBJECT += libc_wr.a::fgetc.o
}
ObjectFile libc_wr.a::fgetpos.o {
	NAME Object file fgetpos.o from archive libc_wr.a
	EXPORTS fgetpos
	IMPORTS .TOC. ftell
	DECLARES 
	USES 
}
Module fgetpos.o {
	OBJECT += libc_wr.a::fgetpos.o
}
ObjectFile libc_wr.a::fgets.o {
	NAME Object file fgets.o from archive libc_wr.a
	EXPORTS fgets
	IMPORTS .TOC. __srefill memchr bcopy
	DECLARES 
	USES 
}
Module fgets.o {
	OBJECT += libc_wr.a::fgets.o
}
ObjectFile libc_wr.a::fileno.o {
	NAME Object file fileno.o from archive libc_wr.a
	EXPORTS fileno
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fileno.o {
	OBJECT += libc_wr.a::fileno.o
}
ObjectFile libc_wr.a::flags.o {
	NAME Object file flags.o from archive libc_wr.a
	EXPORTS __sflags
	IMPORTS .TOC. __errno
	DECLARES 
	USES 
}
Module flags.o {
	OBJECT += libc_wr.a::flags.o
}
ObjectFile libc_wr.a::fopen.o {
	NAME Object file fopen.o from archive libc_wr.a
	EXPORTS fopen
	IMPORTS .TOC. __sflags stdioFpCreate open stdioFpDestroy __sseek
	DECLARES 
	USES 
}
Module fopen.o {
	OBJECT += libc_wr.a::fopen.o
}
ObjectFile libc_wr.a::fputc.o {
	NAME Object file fputc.o from archive libc_wr.a
	EXPORTS fputc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module fputc.o {
	OBJECT += libc_wr.a::fputc.o
}
ObjectFile libc_wr.a::fputs.o {
	NAME Object file fputs.o from archive libc_wr.a
	EXPORTS fputs
	IMPORTS .TOC. strlen __sfvwrite
	DECLARES 
	USES 
}
Module fputs.o {
	OBJECT += libc_wr.a::fputs.o
}
ObjectFile libc_wr.a::fread.o {
	NAME Object file fread.o from archive libc_wr.a
	EXPORTS fread
	IMPORTS .TOC. bcopy __srefill
	DECLARES 
	USES 
}
Module fread.o {
	OBJECT += libc_wr.a::fread.o
}
ObjectFile libc_wr.a::fsetpos.o {
	NAME Object file fsetpos.o from archive libc_wr.a
	EXPORTS fsetpos
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module fsetpos.o {
	OBJECT += libc_wr.a::fsetpos.o
}
ObjectFile libc_wr.a::ftell.o {
	NAME Object file ftell.o from archive libc_wr.a
	EXPORTS ftell
	IMPORTS .TOC. __sseek
	DECLARES 
	USES 
}
Module ftell.o {
	OBJECT += libc_wr.a::ftell.o
}
ObjectFile libc_wr.a::fvwrite.o {
	NAME Object file fvwrite.o from archive libc_wr.a
	EXPORTS __sfvwrite
	IMPORTS .TOC. __swsetup __swrite bcopy fflush memchr
	DECLARES 
	USES 
}
Module fvwrite.o {
	OBJECT += libc_wr.a::fvwrite.o
}
ObjectFile libc_wr.a::fwrite.o {
	NAME Object file fwrite.o from archive libc_wr.a
	EXPORTS fwrite
	IMPORTS .TOC. __sfvwrite
	DECLARES 
	USES 
}
Module fwrite.o {
	OBJECT += libc_wr.a::fwrite.o
}
ObjectFile libc_wr.a::getc.o {
	NAME Object file getc.o from archive libc_wr.a
	EXPORTS getc
	IMPORTS .TOC. __srget
	DECLARES 
	USES 
}
Module getc.o {
	OBJECT += libc_wr.a::getc.o
}
ObjectFile libc_wr.a::getchar.o {
	NAME Object file getchar.o from archive libc_wr.a
	EXPORTS getchar
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module getchar.o {
	OBJECT += libc_wr.a::getchar.o
}
ObjectFile libc_wr.a::gets.o {
	NAME Object file gets.o from archive libc_wr.a
	EXPORTS gets
	IMPORTS .TOC. __stdin __srget
	DECLARES 
	USES 
}
Module gets.o {
	OBJECT += libc_wr.a::gets.o
}
ObjectFile libc_wr.a::getw.o {
	NAME Object file getw.o from archive libc_wr.a
	EXPORTS getw
	IMPORTS .TOC. fread
	DECLARES 
	USES 
}
Module getw.o {
	OBJECT += libc_wr.a::getw.o
}
ObjectFile libc_wr.a::perror.o {
	NAME Object file perror.o from archive libc_wr.a
	EXPORTS perror
	IMPORTS .TOC. __stderr fprintf __errno strerror
	DECLARES 
	USES 
}
Module perror.o {
	OBJECT += libc_wr.a::perror.o
}
ObjectFile libc_wr.a::putc.o {
	NAME Object file putc.o from archive libc_wr.a
	EXPORTS putc
	IMPORTS .TOC. __swbuf
	DECLARES 
	USES 
}
Module putc.o {
	OBJECT += libc_wr.a::putc.o
}
ObjectFile libc_wr.a::putchar.o {
	NAME Object file putchar.o from archive libc_wr.a
	EXPORTS putchar
	IMPORTS .TOC. __stdout __swbuf
	DECLARES 
	USES 
}
Module putchar.o {
	OBJECT += libc_wr.a::putchar.o
}
ObjectFile libc_wr.a::putw.o {
	NAME Object file putw.o from archive libc_wr.a
	EXPORTS putw
	IMPORTS .TOC. fwrite
	DECLARES 
	USES 
}
Module putw.o {
	OBJECT += libc_wr.a::putw.o
}
ObjectFile libc_wr.a::puts.o {
	NAME Object file puts.o from archive libc_wr.a
	EXPORTS puts
	IMPORTS .TOC. strlen __stdout __sfvwrite
	DECLARES 
	USES 
}
Module puts.o {
	OBJECT += libc_wr.a::puts.o
}
ObjectFile libc_wr.a::rewind.o {
	NAME Object file rewind.o from archive libc_wr.a
	EXPORTS rewind
	IMPORTS .TOC. fseek
	DECLARES 
	USES 
}
Module rewind.o {
	OBJECT += libc_wr.a::rewind.o
}
ObjectFile libc_wr.a::rget.o {
	NAME Object file rget.o from archive libc_wr.a
	EXPORTS __srget
	IMPORTS .TOC. __srefill
	DECLARES 
	USES 
}
Module rget.o {
	OBJECT += libc_wr.a::rget.o
}
ObjectFile libc_wr.a::setbuf.o {
	NAME Object file setbuf.o from archive libc_wr.a
	EXPORTS setbuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuf.o {
	OBJECT += libc_wr.a::setbuf.o
}
ObjectFile libc_wr.a::setbuffer.o {
	NAME Object file setbuffer.o from archive libc_wr.a
	EXPORTS setbuffer setlinebuf
	IMPORTS .TOC. setvbuf
	DECLARES 
	USES 
}
Module setbuffer.o {
	OBJECT += libc_wr.a::setbuffer.o
}
ObjectFile libc_wr.a::stdio.o {
	NAME Object file stdio.o from archive libc_wr.a
	EXPORTS __sread __swrite __sseek __sclose
	IMPORTS .TOC. read lseek write close
	DECLARES 
	USES 
}
Module stdio.o {
	OBJECT += libc_wr.a::stdio.o
}
ObjectFile libc_wr.a::tmpnam.o {
	NAME Object file tmpnam.o from archive libc_wr.a
	EXPORTS tmpnam
	IMPORTS .TOC. strcpy strlen
	DECLARES 
	USES 
}
Module tmpnam.o {
	OBJECT += libc_wr.a::tmpnam.o
}
ObjectFile libc_wr.a::tmpfile.o {
	NAME Object file tmpfile.o from archive libc_wr.a
	EXPORTS tmpfile
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module tmpfile.o {
	OBJECT += libc_wr.a::tmpfile.o
}
ObjectFile libc_wr.a::wbuf.o {
	NAME Object file wbuf.o from archive libc_wr.a
	EXPORTS __swbuf
	IMPORTS .TOC. __swsetup fflush
	DECLARES 
	USES 
}
Module wbuf.o {
	OBJECT += libc_wr.a::wbuf.o
}
ObjectFile libc_wr.a::vfprintf.o {
	NAME Object file vfprintf.o from archive libc_wr.a
	EXPORTS vfprintf
	IMPORTS .TOC. __swsetup handleInit fioFormatV fflush handleTerminate __swbuf
	DECLARES 
	USES 
}
Module vfprintf.o {
	OBJECT += libc_wr.a::vfprintf.o
}
ObjectFile libc_wr.a::fprintf.o {
	NAME Object file fprintf.o from archive libc_wr.a
	EXPORTS fprintf
	IMPORTS .TOC. vfprintf
	DECLARES 
	USES 
}
Module fprintf.o {
	OBJECT += libc_wr.a::fprintf.o
}
ObjectFile libc_wr.a::fscanf.o {
	NAME Object file fscanf.o from archive libc_wr.a
	EXPORTS fscanf
	IMPORTS .TOC. fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module fscanf.o {
	OBJECT += libc_wr.a::fscanf.o
}
ObjectFile libc_wr.a::scanf.o {
	NAME Object file scanf.o from archive libc_wr.a
	EXPORTS scanf
	IMPORTS .TOC. __stdin fgetc fioScanV ungetc
	DECLARES 
	USES 
}
Module scanf.o {
	OBJECT += libc_wr.a::scanf.o
}
ObjectFile libc_wr.a::stdioFuncBind.o {
	NAME Object file stdioFuncBind.o from archive libc_wr.a
	EXPORTS _func_fclose
	IMPORTS 
	DECLARES 
	USES 
}
Module stdioFuncBind.o {
	OBJECT += libc_wr.a::stdioFuncBind.o
}
ObjectFile libc_wr.a::fclose.o {
	NAME Object file fclose.o from archive libc_wr.a
	EXPORTS fclose
	IMPORTS .TOC. __errno __sflush __sclose free stdioFpDestroy
	DECLARES 
	USES 
}
Module fclose.o {
	OBJECT += libc_wr.a::fclose.o
}
ObjectFile libc_wr.a::freopen.o {
	NAME Object file freopen.o from archive libc_wr.a
	EXPORTS freopen
	IMPORTS .TOC. __sflags fclose __sflush __sclose open __errno free stdioFpDestroy
	DECLARES 
	USES 
}
Module freopen.o {
	OBJECT += libc_wr.a::freopen.o
}
ObjectFile libc_wr.a::fseek.o {
	NAME Object file fseek.o from archive libc_wr.a
	EXPORTS fseek
	IMPORTS .TOC. __sseek __errno __smakebuf ioctl free __srefill __sflush
	DECLARES 
	USES 
}
Module fseek.o {
	OBJECT += libc_wr.a::fseek.o
}
ObjectFile libc_wr.a::makebuf.o {
	NAME Object file makebuf.o from archive libc_wr.a
	EXPORTS __smakebuf
	IMPORTS .TOC. ioctl malloc isatty
	DECLARES 
	USES 
}
Module makebuf.o {
	OBJECT += libc_wr.a::makebuf.o
}
ObjectFile libc_wr.a::refill.o {
	NAME Object file refill.o from archive libc_wr.a
	EXPORTS __srefill
	IMPORTS .TOC. __sflush __errno free __smakebuf __sread
	DECLARES 
	USES 
}
Module refill.o {
	OBJECT += libc_wr.a::refill.o
}
ObjectFile libc_wr.a::setvbuf.o {
	NAME Object file setvbuf.o from archive libc_wr.a
	EXPORTS setvbuf
	IMPORTS .TOC. __sflush free
	DECLARES 
	USES 
}
Module setvbuf.o {
	OBJECT += libc_wr.a::setvbuf.o
}
ObjectFile libc_wr.a::stdioLib.o {
	NAME Object file stdioLib.o from archive libc_wr.a
	EXPORTS stdioInit stdioFpCreate stdioFpDestroy __stdin __stdout __stderr stdioFp
	IMPORTS .TOC. fclose _func_fclose malloc taskIdSelf handleInit handleTerminate free _func_taskDeleteHookAdd taskCreateHookInit taskDeleteHookAdd
	DECLARES 
	USES 
}
Module stdioLib.o {
	OBJECT += libc_wr.a::stdioLib.o
}
ObjectFile libc_wr.a::stdioShow.o {
	NAME Object file stdioShow.o from archive libc_wr.a
	EXPORTS stdioShowInit stdioShow
	IMPORTS .TOC. handleShowConnect printf
	DECLARES 
	USES 
}
Module stdioShow.o {
	OBJECT += libc_wr.a::stdioShow.o
}
ObjectFile libc_wr.a::ungetc.o {
	NAME Object file ungetc.o from archive libc_wr.a
	EXPORTS ungetc
	IMPORTS .TOC. malloc realloc bcopy __sflush
	DECLARES 
	USES 
}
Module ungetc.o {
	OBJECT += libc_wr.a::ungetc.o
}
ObjectFile libc_wr.a::wsetup.o {
	NAME Object file wsetup.o from archive libc_wr.a
	EXPORTS __swsetup
	IMPORTS .TOC. free __smakebuf
	DECLARES 
	USES 
}
Module wsetup.o {
	OBJECT += libc_wr.a::wsetup.o
}
ObjectFile libc_wr.a::abort.o {
	NAME Object file abort.o from archive libc_wr.a
	EXPORTS abort
	IMPORTS .TOC. raise exit
	DECLARES 
	USES 
}
Module abort.o {
	OBJECT += libc_wr.a::abort.o
}
ObjectFile libc_wr.a::abs.o {
	NAME Object file abs.o from archive libc_wr.a
	EXPORTS abs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module abs.o {
	OBJECT += libc_wr.a::abs.o
}
ObjectFile libc_wr.a::atexit.o {
	NAME Object file atexit.o from archive libc_wr.a
	EXPORTS atexit
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module atexit.o {
	OBJECT += libc_wr.a::atexit.o
}
ObjectFile libc_wr.a::atof.o {
	NAME Object file atof.o from archive libc_wr.a
	EXPORTS atof
	IMPORTS .TOC. strtod
	DECLARES 
	USES 
}
Module atof.o {
	OBJECT += libc_wr.a::atof.o
}
ObjectFile libc_wr.a::atoi.o {
	NAME Object file atoi.o from archive libc_wr.a
	EXPORTS atoi
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atoi.o {
	OBJECT += libc_wr.a::atoi.o
}
ObjectFile libc_wr.a::atol.o {
	NAME Object file atol.o from archive libc_wr.a
	EXPORTS atol
	IMPORTS .TOC. strtol
	DECLARES 
	USES 
}
Module atol.o {
	OBJECT += libc_wr.a::atol.o
}
ObjectFile libc_wr.a::bsearch.o {
	NAME Object file bsearch.o from archive libc_wr.a
	EXPORTS bsearch
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module bsearch.o {
	OBJECT += libc_wr.a::bsearch.o
}
ObjectFile libc_wr.a::div.o {
	NAME Object file div.o from archive libc_wr.a
	EXPORTS div_r div
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module div.o {
	OBJECT += libc_wr.a::div.o
}
ObjectFile libc_wr.a::labs.o {
	NAME Object file labs.o from archive libc_wr.a
	EXPORTS labs
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module labs.o {
	OBJECT += libc_wr.a::labs.o
}
ObjectFile libc_wr.a::ldiv.o {
	NAME Object file ldiv.o from archive libc_wr.a
	EXPORTS ldiv_r ldiv
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module ldiv.o {
	OBJECT += libc_wr.a::ldiv.o
}
ObjectFile libc_wr.a::multibyte.o {
	NAME Object file multibyte.o from archive libc_wr.a
	EXPORTS mblen mbtowc wctomb mbstowcs wcstombs
	IMPORTS .TOC. strcmp
	DECLARES 
	USES 
}
Module multibyte.o {
	OBJECT += libc_wr.a::multibyte.o
}
ObjectFile libc_wr.a::qsort.o {
	NAME Object file qsort.o from archive libc_wr.a
	EXPORTS qsort
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module qsort.o {
	OBJECT += libc_wr.a::qsort.o
}
ObjectFile libc_wr.a::stdrand.o {
	NAME Object file stdrand.o from archive libc_wr.a
	EXPORTS rand _Randseed srand
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module stdrand.o {
	OBJECT += libc_wr.a::stdrand.o
}
ObjectFile libc_wr.a::strtol.o {
	NAME Object file strtol.o from archive libc_wr.a
	EXPORTS strtol
	IMPORTS .TOC. __errno __ctype
	DECLARES 
	USES 
}
Module strtol.o {
	OBJECT += libc_wr.a::strtol.o
}
ObjectFile libc_wr.a::strtoul.o {
	NAME Object file strtoul.o from archive libc_wr.a
	EXPORTS strtoul
	IMPORTS .TOC. __ctype __errno
	DECLARES 
	USES 
}
Module strtoul.o {
	OBJECT += libc_wr.a::strtoul.o
}
ObjectFile libc_wr.a::system.o {
	NAME Object file system.o from archive libc_wr.a
	EXPORTS system
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module system.o {
	OBJECT += libc_wr.a::system.o
}
ObjectFile libc_wr.a::strtod.o {
	NAME Object file strtod.o from archive libc_wr.a
	EXPORTS strtod
	IMPORTS .TOC. __ctype ldexp
	DECLARES 
	USES 
}
Module strtod.o {
	OBJECT += libc_wr.a::strtod.o
}
ObjectFile libc_wr.a::strtoll.o {
	NAME Object file strtoll.o from archive libc_wr.a
	EXPORTS strtoll
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoll.o {
	OBJECT += libc_wr.a::strtoll.o
}
ObjectFile libc_wr.a::strtoull.o {
	NAME Object file strtoull.o from archive libc_wr.a
	EXPORTS strtoull
	IMPORTS .TOC. __ctype errnoSet
	DECLARES 
	USES 
}
Module strtoull.o {
	OBJECT += libc_wr.a::strtoull.o
}
ObjectFile libc_wr.a::memchr.o {
	NAME Object file memchr.o from archive libc_wr.a
	EXPORTS memchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memchr.o {
	OBJECT += libc_wr.a::memchr.o
}
ObjectFile libc_wr.a::memcmp.o {
	NAME Object file memcmp.o from archive libc_wr.a
	EXPORTS memcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memcmp.o {
	OBJECT += libc_wr.a::memcmp.o
}
ObjectFile libc_wr.a::memcpy.o {
	NAME Object file memcpy.o from archive libc_wr.a
	EXPORTS memcpy
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memcpy.o {
	OBJECT += libc_wr.a::memcpy.o
}
ObjectFile libc_wr.a::memmove.o {
	NAME Object file memmove.o from archive libc_wr.a
	EXPORTS memmove
	IMPORTS .TOC. bcopy
	DECLARES 
	USES 
}
Module memmove.o {
	OBJECT += libc_wr.a::memmove.o
}
ObjectFile libc_wr.a::memset.o {
	NAME Object file memset.o from archive libc_wr.a
	EXPORTS memset
	IMPORTS .TOC. bfill
	DECLARES 
	USES 
}
Module memset.o {
	OBJECT += libc_wr.a::memset.o
}
ObjectFile libc_wr.a::memset_s.o {
	NAME Object file memset_s.o from archive libc_wr.a
	EXPORTS __internal_memset_s memset_s _memset_s_func
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module memset_s.o {
	OBJECT += libc_wr.a::memset_s.o
}
ObjectFile libc_wr.a::strcat.o {
	NAME Object file strcat.o from archive libc_wr.a
	EXPORTS strcat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcat.o {
	OBJECT += libc_wr.a::strcat.o
}
ObjectFile libc_wr.a::strchr.o {
	NAME Object file strchr.o from archive libc_wr.a
	EXPORTS strchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strchr.o {
	OBJECT += libc_wr.a::strchr.o
}
ObjectFile libc_wr.a::strcmp.o {
	NAME Object file strcmp.o from archive libc_wr.a
	EXPORTS strcmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcmp.o {
	OBJECT += libc_wr.a::strcmp.o
}
ObjectFile libc_wr.a::strcoll.o {
	NAME Object file strcoll.o from archive libc_wr.a
	EXPORTS strcoll
	IMPORTS .TOC. __strxfrm memcmp
	DECLARES 
	USES 
}
Module strcoll.o {
	OBJECT += libc_wr.a::strcoll.o
}
ObjectFile libc_wr.a::strcpy.o {
	NAME Object file strcpy.o from archive libc_wr.a
	EXPORTS strcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcpy.o {
	OBJECT += libc_wr.a::strcpy.o
}
ObjectFile libc_wr.a::strcspn.o {
	NAME Object file strcspn.o from archive libc_wr.a
	EXPORTS strcspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strcspn.o {
	OBJECT += libc_wr.a::strcspn.o
}
ObjectFile libc_wr.a::strerror.o {
	NAME Object file strerror.o from archive libc_wr.a
	EXPORTS strerrorIf strerror_r strerror
	IMPORTS .TOC. _func_symFindSymbol statSymTbl _func_symNameGet _func_symValueGet strlcpy snprintf
	DECLARES 
	USES 
}
Module strerror.o {
	OBJECT += libc_wr.a::strerror.o
}
ObjectFile libc_wr.a::strlen.o {
	NAME Object file strlen.o from archive libc_wr.a
	EXPORTS strlen
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlen.o {
	OBJECT += libc_wr.a::strlen.o
}
ObjectFile libc_wr.a::strncat.o {
	NAME Object file strncat.o from archive libc_wr.a
	EXPORTS strncat
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncat.o {
	OBJECT += libc_wr.a::strncat.o
}
ObjectFile libc_wr.a::strncmp.o {
	NAME Object file strncmp.o from archive libc_wr.a
	EXPORTS strncmp
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncmp.o {
	OBJECT += libc_wr.a::strncmp.o
}
ObjectFile libc_wr.a::strncpy.o {
	NAME Object file strncpy.o from archive libc_wr.a
	EXPORTS strncpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strncpy.o {
	OBJECT += libc_wr.a::strncpy.o
}
ObjectFile libc_wr.a::strpbrk.o {
	NAME Object file strpbrk.o from archive libc_wr.a
	EXPORTS strpbrk
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strpbrk.o {
	OBJECT += libc_wr.a::strpbrk.o
}
ObjectFile libc_wr.a::strrchr.o {
	NAME Object file strrchr.o from archive libc_wr.a
	EXPORTS strrchr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strrchr.o {
	OBJECT += libc_wr.a::strrchr.o
}
ObjectFile libc_wr.a::strspn.o {
	NAME Object file strspn.o from archive libc_wr.a
	EXPORTS strspn
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strspn.o {
	OBJECT += libc_wr.a::strspn.o
}
ObjectFile libc_wr.a::strstr.o {
	NAME Object file strstr.o from archive libc_wr.a
	EXPORTS strstr
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strstr.o {
	OBJECT += libc_wr.a::strstr.o
}
ObjectFile libc_wr.a::strtok.o {
	NAME Object file strtok.o from archive libc_wr.a
	EXPORTS strtok
	IMPORTS .TOC. strtok_r
	DECLARES 
	USES 
}
Module strtok.o {
	OBJECT += libc_wr.a::strtok.o
}
ObjectFile libc_wr.a::strtok_r.o {
	NAME Object file strtok_r.o from archive libc_wr.a
	EXPORTS strtok_r
	IMPORTS .TOC. strspn strpbrk
	DECLARES 
	USES 
}
Module strtok_r.o {
	OBJECT += libc_wr.a::strtok_r.o
}
ObjectFile libc_wr.a::strxfrm.o {
	NAME Object file strxfrm.o from archive libc_wr.a
	EXPORTS __strxfrm strxfrm
	IMPORTS .TOC. __costate
	DECLARES 
	USES 
}
Module strxfrm.o {
	OBJECT += libc_wr.a::strxfrm.o
}
ObjectFile libc_wr.a::xstate.o {
	NAME Object file xstate.o from archive libc_wr.a
	EXPORTS __costate
	IMPORTS 
	DECLARES 
	USES 
}
Module xstate.o {
	OBJECT += libc_wr.a::xstate.o
}
ObjectFile libc_wr.a::strlcat.o {
	NAME Object file strlcat.o from archive libc_wr.a
	EXPORTS strlcat
	IMPORTS .TOC. strlen
	DECLARES 
	USES 
}
Module strlcat.o {
	OBJECT += libc_wr.a::strlcat.o
}
ObjectFile libc_wr.a::strlcpy.o {
	NAME Object file strlcpy.o from archive libc_wr.a
	EXPORTS strlcpy
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module strlcpy.o {
	OBJECT += libc_wr.a::strlcpy.o
}
ObjectFile libc_wr.a::strcasecmp.o {
	NAME Object file strcasecmp.o from archive libc_wr.a
	EXPORTS strcasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strcasecmp.o {
	OBJECT += libc_wr.a::strcasecmp.o
}
ObjectFile libc_wr.a::strncasecmp.o {
	NAME Object file strncasecmp.o from archive libc_wr.a
	EXPORTS strncasecmp
	IMPORTS .TOC. __ctype_tolower
	DECLARES 
	USES 
}
Module strncasecmp.o {
	OBJECT += libc_wr.a::strncasecmp.o
}
ObjectFile libc_wr.a::strdup.o {
	NAME Object file strdup.o from archive libc_wr.a
	EXPORTS strdup
	IMPORTS .TOC. strlen malloc strcpy
	DECLARES 
	USES 
}
Module strdup.o {
	OBJECT += libc_wr.a::strdup.o
}
ObjectFile libc_wr.a::locTime.o {
	NAME Object file locTime.o from archive libc_wr.a
	EXPORTS __loctime
	IMPORTS 
	DECLARES 
	USES 
}
Module locTime.o {
	OBJECT += libc_wr.a::locTime.o
}
ObjectFile libc_wr.a::asctime.o {
	NAME Object file asctime.o from archive libc_wr.a
	EXPORTS asctime_r asctime _vxworks_asctime_r
	IMPORTS .TOC. strftime
	DECLARES 
	USES 
}
Module asctime.o {
	OBJECT += libc_wr.a::asctime.o
}
ObjectFile libc_wr.a::clock.o {
	NAME Object file clock.o from archive libc_wr.a
	EXPORTS clock
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module clock.o {
	OBJECT += libc_wr.a::clock.o
}
ObjectFile libc_wr.a::ctime.o {
	NAME Object file ctime.o from archive libc_wr.a
	EXPORTS ctime_r ctime _vxworks_ctime_r
	IMPORTS .TOC. localtime asctime_r _vxworks_asctime_r
	DECLARES 
	USES 
}
Module ctime.o {
	OBJECT += libc_wr.a::ctime.o
}
ObjectFile libc_wr.a::gmtime.o {
	NAME Object file gmtime.o from archive libc_wr.a
	EXPORTS __daysSinceEpoch __julday __getTime gmtime_r gmtime _vxworks_gmtime_r
	IMPORTS .TOC. ldiv_r
	DECLARES 
	USES 
}
Module gmtime.o {
	OBJECT += libc_wr.a::gmtime.o
}
ObjectFile libc_wr.a::localtime.o {
	NAME Object file localtime.o from archive libc_wr.a
	EXPORTS localtime_r localtime _vxworks_localtime_r
	IMPORTS .TOC. __loctime __getZoneInfo atoi __getTime __getDstInfoSub
	DECLARES 
	USES 
}
Module localtime.o {
	OBJECT += libc_wr.a::localtime.o
}
ObjectFile libc_wr.a::mktime.o {
	NAME Object file mktime.o from archive libc_wr.a
	EXPORTS mktime
	IMPORTS .TOC. __julday __daysSinceEpoch __loctime __getDstInfoSub __getZoneInfo atoi
	DECLARES 
	USES 
}
Module mktime.o {
	OBJECT += libc_wr.a::mktime.o
}
ObjectFile libc_wr.a::strftime.o {
	NAME Object file strftime.o from archive libc_wr.a
	EXPORTS __getZoneInfo strftime __getDstInfoSub __getDstInfo
	IMPORTS .TOC. getenv_s strpbrk strncpy strcmp strlen memcpy abs __loctime strtok_r bzero atoi
	DECLARES 
	USES 
}
Module strftime.o {
	OBJECT += libc_wr.a::strftime.o
}
ObjectFile libc_wr.a::time.o {
	NAME Object file time.o from archive libc_wr.a
	EXPORTS time
	IMPORTS .TOC. clock_gettime
	DECLARES 
	USES 
}
Module time.o {
	OBJECT += libc_wr.a::time.o
}
ObjectFile libc_wr.a::difftime.o {
	NAME Object file difftime.o from archive libc_wr.a
	EXPORTS difftime
	IMPORTS .TOC. __ulltod
	DECLARES 
	USES 
}
Module difftime.o {
	OBJECT += libc_wr.a::difftime.o
}
Library libc_wr.a {
	MODULES libc_wr.a::assert.o libc_wr.a::__ctype_tab.o libc_wr.a::isalnum.o libc_wr.a::isalpha.o libc_wr.a::iscntrl.o libc_wr.a::isdigit.o libc_wr.a::isgraph.o libc_wr.a::islower.o libc_wr.a::isprint.o libc_wr.a::ispunct.o libc_wr.a::isspace.o libc_wr.a::isupper.o libc_wr.a::isxdigit.o libc_wr.a::tolower.o libc_wr.a::toupper.o libc_wr.a::localeconv.o libc_wr.a::setlocale.o libc_wr.a::longjmp.o libc_wr.a::clearerr.o libc_wr.a::fdopen.o libc_wr.a::feof.o libc_wr.a::ferror.o libc_wr.a::fflush.o libc_wr.a::fgetc.o libc_wr.a::fgetpos.o libc_wr.a::fgets.o libc_wr.a::fileno.o libc_wr.a::flags.o libc_wr.a::fopen.o libc_wr.a::fputc.o libc_wr.a::fputs.o libc_wr.a::fread.o libc_wr.a::fsetpos.o libc_wr.a::ftell.o libc_wr.a::fvwrite.o libc_wr.a::fwrite.o libc_wr.a::getc.o libc_wr.a::getchar.o libc_wr.a::gets.o libc_wr.a::getw.o libc_wr.a::perror.o libc_wr.a::putc.o libc_wr.a::putchar.o libc_wr.a::putw.o libc_wr.a::puts.o libc_wr.a::rewind.o libc_wr.a::rget.o libc_wr.a::setbuf.o libc_wr.a::setbuffer.o libc_wr.a::stdio.o libc_wr.a::tmpnam.o libc_wr.a::tmpfile.o libc_wr.a::wbuf.o libc_wr.a::vfprintf.o libc_wr.a::fprintf.o libc_wr.a::fscanf.o libc_wr.a::scanf.o libc_wr.a::stdioFuncBind.o libc_wr.a::fclose.o libc_wr.a::freopen.o libc_wr.a::fseek.o libc_wr.a::makebuf.o libc_wr.a::refill.o libc_wr.a::setvbuf.o libc_wr.a::stdioLib.o libc_wr.a::stdioShow.o libc_wr.a::ungetc.o libc_wr.a::wsetup.o libc_wr.a::abort.o libc_wr.a::abs.o libc_wr.a::atexit.o libc_wr.a::atof.o libc_wr.a::atoi.o libc_wr.a::atol.o libc_wr.a::bsearch.o libc_wr.a::div.o libc_wr.a::labs.o libc_wr.a::ldiv.o libc_wr.a::multibyte.o libc_wr.a::qsort.o libc_wr.a::stdrand.o libc_wr.a::strtol.o libc_wr.a::strtoul.o libc_wr.a::system.o libc_wr.a::strtod.o libc_wr.a::strtoll.o libc_wr.a::strtoull.o libc_wr.a::memchr.o libc_wr.a::memcmp.o libc_wr.a::memcpy.o libc_wr.a::memmove.o libc_wr.a::memset.o libc_wr.a::memset_s.o libc_wr.a::strcat.o libc_wr.a::strchr.o libc_wr.a::strcmp.o libc_wr.a::strcoll.o libc_wr.a::strcpy.o libc_wr.a::strcspn.o libc_wr.a::strerror.o libc_wr.a::strlen.o libc_wr.a::strncat.o libc_wr.a::strncmp.o libc_wr.a::strncpy.o libc_wr.a::strpbrk.o libc_wr.a::strrchr.o libc_wr.a::strspn.o libc_wr.a::strstr.o libc_wr.a::strtok.o libc_wr.a::strtok_r.o libc_wr.a::strxfrm.o libc_wr.a::xstate.o libc_wr.a::strlcat.o libc_wr.a::strlcpy.o libc_wr.a::strcasecmp.o libc_wr.a::strncasecmp.o libc_wr.a::strdup.o libc_wr.a::locTime.o libc_wr.a::asctime.o libc_wr.a::clock.o libc_wr.a::ctime.o libc_wr.a::gmtime.o libc_wr.a::localtime.o libc_wr.a::mktime.o libc_wr.a::strftime.o libc_wr.a::time.o libc_wr.a::difftime.o
}
