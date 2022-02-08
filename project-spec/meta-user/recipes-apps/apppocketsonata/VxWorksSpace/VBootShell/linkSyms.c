/* linkSyms.c - dynamically generated configuration file */


/*
GENERATED: Sun Jan 23 18:39:07 +0900 2022
DO NOT EDIT - file is regenerated whenever the project changes
*/

typedef int (*FUNC) ();
extern int __assert ();
extern int __ctype ();
extern int abort ();
extern int abs ();
extern int absSymbols_Common ();
extern int acos ();
extern int asctime ();
extern int asin ();
extern int atan ();
extern int atan2 ();
extern int atexit ();
extern int atof ();
extern int atoi ();
extern int atol ();
extern int bitFirstGet ();
extern int bmanDrv ();
extern int bportalDrv ();
extern int bsearch ();
extern int cafe_ep_spec_print ();
extern int cafe_script_run ();
extern int ceil ();
extern int checksum ();
extern int clearerr ();
extern int clock ();
extern int cos ();
extern int cosh ();
extern int ctime ();
extern int difftime ();
extern int div ();
extern int dllInit ();
extern int etherMultiAdd ();
extern int exp ();
extern int fabs ();
extern int fclose ();
extern int fdopen ();
extern int feof ();
extern int ferror ();
extern int fflush ();
extern int fgetc ();
extern int fgetpos ();
extern int fgets ();
extern int fileno ();
extern int floor ();
extern int fmanDrv ();
extern int fmod ();
extern int fopen ();
extern int fprintf ();
extern int fputc ();
extern int fputs ();
extern int fread ();
extern int freopen ();
extern int frexp ();
extern int fscanf ();
extern int fseek ();
extern int fsetpos ();
extern int ftell ();
extern int ftpCommand ();
extern int ftruncate ();
extern int fwrite ();
extern int genPhyDrv ();
extern int getaddrinfo ();
extern int getc ();
extern int getchar ();
extern int getifaddrs ();
extern int getoptInit ();
extern int gets ();
extern int getservbyname ();
extern int getservbyport ();
extern int getw ();
extern int gmtime ();
extern int hashTblInit ();
extern int hookAddToTail ();
extern int hookShow ();
extern int hypot ();
extern int inet_aton ();
extern int inet_network ();
extern int ini_cafe_config_service ();
extern int ioHelp ();
extern int ipAttach ();
extern int ipcom_cfgfile_parse ();
extern int ipcom_register_dev_name_mapping ();
extern int ipcom_start_shell_native ();
extern int ipnet_cmd_ping ();
extern int ipnet_eth_add_hdr ();
extern int ipnet_ip4_input ();
extern int ipnet_ip4_mcast_input ();
extern int ipnet_ip6_input ();
extern int ipnet_ip6_mcast_input ();
extern int ipnet_sock_netlink_register ();
extern int ipnet_sock_route_register ();
extern int ipnet_vlan_if_init ();
extern int isalnum ();
extern int isalpha ();
extern int iscntrl ();
extern int isdigit ();
extern int isgraph ();
extern int islower ();
extern int isprint ();
extern int ispunct ();
extern int isspace ();
extern int isupper ();
extern int isxdigit ();
extern int jobAdd ();
extern int labs ();
extern int ldexp ();
extern int ldiv ();
extern int localeconv ();
extern int localtime ();
extern int log ();
extern int log10 ();
extern int longjmp ();
extern int lstInit ();
extern int m_prepend ();
extern int mblen ();
extern int memacDrv ();
extern int memchr ();
extern int memcmp ();
extern int memcpy ();
extern int memmove ();
extern int memset ();
extern int memset_s ();
extern int mktime ();
extern int modf ();
extern int msgQEvStart ();
extern int nanosleep ();
extern int objShowAll ();
extern int opendir ();
extern int perror ();
extern int ping ();
extern int pow ();
extern int putc ();
extern int putchar ();
extern int puts ();
extern int putw ();
extern int qmanDrv ();
extern int qoriqLawDrv ();
extern int qportalDrv ();
extern int qsort ();
extern int rand ();
extern int randBytes ();
extern int rewind ();
extern int rngCreate ();
extern int scanf ();
extern int sched_setparam ();
extern int semEvStart ();
extern int semExchange ();
extern int semInfo ();
extern int setbuf ();
extern int setbuffer ();
extern int setlocale ();
extern int setvbuf ();
extern int sin ();
extern int sinh ();
extern int sllInit ();
extern int spinLockIsrNdInit ();
extern int spinLockIsrNdTake ();
extern int sqrt ();
extern int strcasecmp ();
extern int strcat ();
extern int strchr ();
extern int strcmp ();
extern int strcoll ();
extern int strcpy ();
extern int strcspn ();
extern int strdup ();
extern int strerror ();
extern int strftime ();
extern int strlcat ();
extern int strlcpy ();
extern int strlen ();
extern int strncasecmp ();
extern int strncat ();
extern int strncmp ();
extern int strncpy ();
extern int strpbrk ();
extern int strrchr ();
extern int strspn ();
extern int strstr ();
extern int strtod ();
extern int strtok ();
extern int strtok_r ();
extern int strtol ();
extern int strtoll ();
extern int strtoul ();
extern int strtoull ();
extern int strxfrm ();
extern int system ();
extern int tan ();
extern int tanh ();
extern int taskIdListGet ();
extern int taskOptionsGet ();
extern int taskRestart ();
extern int taskStatusString ();
extern int taskSwapHookAdd ();
extern int taskSwitchHookAdd ();
extern int time ();
extern int tipStart ();
extern int tmpfile ();
extern int tmpnam ();
extern int tolower ();
extern int toupper ();
extern int ungetc ();
extern int unldByModuleId ();
extern int vfprintf ();
extern int vxAtomicAdd ();
extern int vxbCoreNetL2CacheDrv ();
extern int vxbDtsecMdioDrv ();
extern int vxbFdtBusDrv ();
extern int vxbFdtFslQoriqFpgaDrv ();
extern int vxbFdtNorFlashDrv ();
extern int vxbFdtNs16550Drv ();
extern int vxbFslBookeTimerDrv ();
extern int vxbFslQoriqClockDrv ();
extern int vxbFslSgmiiDrv ();
extern int vxbMemacMdioDrv ();
extern int vxbMmdDrv ();
extern int vxbMpicIntCtlrDrv ();
extern int vxbOpenPicTimerDrv ();
extern int vxbQoriqL3CacheDrv ();
extern int vxbRootDrv ();
extern int vxbSimpleBusDrv ();

FUNC linkSyms [] = {
    __assert,
    __ctype,
    abort,
    abs,
    absSymbols_Common,
    acos,
    asctime,
    asin,
    atan,
    atan2,
    atexit,
    atof,
    atoi,
    atol,
    bitFirstGet,
    bmanDrv,
    bportalDrv,
    bsearch,
    cafe_ep_spec_print,
    cafe_script_run,
    ceil,
    checksum,
    clearerr,
    clock,
    cos,
    cosh,
    ctime,
    difftime,
    div,
    dllInit,
    etherMultiAdd,
    exp,
    fabs,
    fclose,
    fdopen,
    feof,
    ferror,
    fflush,
    fgetc,
    fgetpos,
    fgets,
    fileno,
    floor,
    fmanDrv,
    fmod,
    fopen,
    fprintf,
    fputc,
    fputs,
    fread,
    freopen,
    frexp,
    fscanf,
    fseek,
    fsetpos,
    ftell,
    ftpCommand,
    ftruncate,
    fwrite,
    genPhyDrv,
    getaddrinfo,
    getc,
    getchar,
    getifaddrs,
    getoptInit,
    gets,
    getservbyname,
    getservbyport,
    getw,
    gmtime,
    hashTblInit,
    hookAddToTail,
    hookShow,
    hypot,
    inet_aton,
    inet_network,
    ini_cafe_config_service,
    ioHelp,
    ipAttach,
    ipcom_cfgfile_parse,
    ipcom_register_dev_name_mapping,
    ipcom_start_shell_native,
    ipnet_cmd_ping,
    ipnet_eth_add_hdr,
    ipnet_ip4_input,
    ipnet_ip4_mcast_input,
    ipnet_ip6_input,
    ipnet_ip6_mcast_input,
    ipnet_sock_netlink_register,
    ipnet_sock_route_register,
    ipnet_vlan_if_init,
    isalnum,
    isalpha,
    iscntrl,
    isdigit,
    isgraph,
    islower,
    isprint,
    ispunct,
    isspace,
    isupper,
    isxdigit,
    jobAdd,
    labs,
    ldexp,
    ldiv,
    localeconv,
    localtime,
    log,
    log10,
    longjmp,
    lstInit,
    m_prepend,
    mblen,
    memacDrv,
    memchr,
    memcmp,
    memcpy,
    memmove,
    memset,
    memset_s,
    mktime,
    modf,
    msgQEvStart,
    nanosleep,
    objShowAll,
    opendir,
    perror,
    ping,
    pow,
    putc,
    putchar,
    puts,
    putw,
    qmanDrv,
    qoriqLawDrv,
    qportalDrv,
    qsort,
    rand,
    randBytes,
    rewind,
    rngCreate,
    scanf,
    sched_setparam,
    semEvStart,
    semExchange,
    semInfo,
    setbuf,
    setbuffer,
    setlocale,
    setvbuf,
    sin,
    sinh,
    sllInit,
    spinLockIsrNdInit,
    spinLockIsrNdTake,
    sqrt,
    strcasecmp,
    strcat,
    strchr,
    strcmp,
    strcoll,
    strcpy,
    strcspn,
    strdup,
    strerror,
    strftime,
    strlcat,
    strlcpy,
    strlen,
    strncasecmp,
    strncat,
    strncmp,
    strncpy,
    strpbrk,
    strrchr,
    strspn,
    strstr,
    strtod,
    strtok,
    strtok_r,
    strtol,
    strtoll,
    strtoul,
    strtoull,
    strxfrm,
    system,
    tan,
    tanh,
    taskIdListGet,
    taskOptionsGet,
    taskRestart,
    taskStatusString,
    taskSwapHookAdd,
    taskSwitchHookAdd,
    time,
    tipStart,
    tmpfile,
    tmpnam,
    tolower,
    toupper,
    ungetc,
    unldByModuleId,
    vfprintf,
    vxAtomicAdd,
    vxbCoreNetL2CacheDrv,
    vxbDtsecMdioDrv,
    vxbFdtBusDrv,
    vxbFdtFslQoriqFpgaDrv,
    vxbFdtNorFlashDrv,
    vxbFdtNs16550Drv,
    vxbFslBookeTimerDrv,
    vxbFslQoriqClockDrv,
    vxbFslSgmiiDrv,
    vxbMemacMdioDrv,
    vxbMmdDrv,
    vxbMpicIntCtlrDrv,
    vxbOpenPicTimerDrv,
    vxbQoriqL3CacheDrv,
    vxbRootDrv,
    vxbSimpleBusDrv,
    0
};


int * linkDataSyms [] = {
    0
};

