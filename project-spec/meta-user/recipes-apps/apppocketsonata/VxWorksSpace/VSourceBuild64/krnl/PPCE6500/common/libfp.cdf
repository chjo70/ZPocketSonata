Symbol frexp {
}
Symbol .TOC. {
}
Symbol fpTypeGet {
}
Symbol __errno {
}
Symbol fabs {
}
Symbol ldexp {
}
Symbol getNan {
}
Symbol modf {
}
Symbol acosh {
}
Symbol log1p {
}
Symbol sqrt {
}
Symbol asin {
}
Symbol copysign {
}
Symbol atan2 {
}
Symbol acos {
}
Symbol asinh {
}
Symbol atan {
}
Symbol _savefpr_25 {
}
Symbol finite {
}
Symbol logb {
}
Symbol scalb {
}
Symbol _Raise_Inexact {
}
Symbol _restfpr_25 {
}
Symbol atanh {
}
Symbol ceil {
}
Symbol cosh {
}
Symbol exp__E {
}
Symbol exp {
}
Symbol expm1 {
}
Symbol floor {
}
Symbol fmod {
}
Symbol errnoSet {
}
Symbol log {
}
Symbol _savefpr_27 {
}
Symbol log__L {
}
Symbol _restfpr_27 {
}
Symbol log10 {
}
Symbol pow_p {
}
Symbol pow {
}
Symbol drem {
}
Symbol sin {
}
Symbol cos {
}
Symbol sinh {
}
Symbol tan {
}
Symbol tanh {
}
Symbol getInf {
}
Symbol hypot {
}
Symbol _savefpr_28 {
}
Symbol _restfpr_28 {
}
Symbol cabs {
}
Symbol z_abs {
}
Symbol malloc {
}
Symbol memset {
}
Symbol realloc {
}
Symbol _Jv_Balloc {
}
Symbol __assert {
}
Symbol _Jv_Bfree {
}
Symbol _Jv_multadd {
}
Symbol memcpy {
}
Symbol _Jv_s2b {
}
Symbol _Jv_hi0bits {
}
Symbol _Jv_lo0bits {
}
Symbol _Jv_i2b {
}
Symbol _Jv_mult {
}
Symbol _Jv_pow5mult {
}
Symbol _Jv_lshift {
}
Symbol _Jv__mcmp {
}
Symbol _Jv__mdiff {
}
Symbol _Jv_ulp {
}
Symbol _Jv_b2d {
}
Symbol _Jv_d2b {
}
Symbol _Jv_ratio {
}
Symbol _mprec_log10 {
}
Symbol _Jv__mprec_tens {
}
Symbol _Jv__mprec_bigtens {
}
Symbol _Jv__mprec_tinytens {
}
Symbol _Jv_dtoa_r {
}
Symbol free_Bigints {
}
Symbol free {
}
Symbol __dtoa {
}
Symbol strncpy {
}
Symbol setAlt {
}
Symbol setFpt {
}
Symbol bsd_cvt {
}
Symbol fioBaseLibInit {
}
Symbol printErr {
}
Symbol _func_printErr {
}
Symbol sprintf {
}
Symbol fioBufPut {
}
Symbol fioFormatV {
}
Symbol _func_altivecProbeRtn {
}
Symbol memchr {
}
Symbol strlen {
}
Symbol _func_fioFltFormatRtn {
}
Symbol fieldSzIncludeSign {
}
Symbol printf {
}
Symbol fioBufPrint {
}
Symbol oprintf {
}
Symbol printExc {
}
Symbol intContext {
}
Symbol taskIdSelf {
}
Symbol kernelLockOwnedByMe {
}
Symbol _func_printExcPrintHook {
}
Symbol _func_excJobAdd {
}
Symbol vmLibInfo {
}
Symbol sysExcMsg {
}
Symbol evtAction {
}
Symbol vxAtomic32Add {
}
Symbol edrBufLock {
}
Symbol edrBufUnlock {
}
Symbol taskUnsafe {
}
Symbol _func_shellExcPrint {
}
Symbol taskClassId {
}
Symbol eventPointSwHandle {
}
Symbol snprintf {
}
Symbol fioSnBufPut {
}
Symbol bcopy {
}
Symbol _func_consoleOut {
}
Symbol _func_kwrite {
}
Symbol fioFltInstall {
}
Symbol _func_fioFltScanRtn {
}
Symbol floatInit {
}
Symbol __ctype_tolower {
}
Symbol strcpy {
}
Symbol __ieee754_fmod {
}
Symbol __ieee754_pow {
}
Symbol __ieee754_sqrt {
}
Symbol scalbn {
}
Symbol __ieee754_remainder {
}
Symbol rint {
}
Symbol fioLibInit {
}
Symbol voprintf {
}
Symbol fdprintf {
}
Symbol vprintf {
}
Symbol vfdprintf {
}
Symbol vsprintf {
}
Symbol vsnprintf {
}
Symbol fioRead {
}
Symbol read {
}
Symbol fioRdString {
}
Symbol __ctype {
}
Symbol scanCharSet {
}
Symbol scanField {
}
Symbol fioScanV {
}
Symbol sscanf {
}
ObjectFile libfp.a::frexp.o {
	NAME Object file frexp.o from archive libfp.a
	EXPORTS frexp
	IMPORTS .TOC. fpTypeGet __errno fabs
	DECLARES 
	USES 
}
Module frexp.o {
	OBJECT += libfp.a::frexp.o
}
ObjectFile libfp.a::ldexp.o {
	NAME Object file ldexp.o from archive libfp.a
	EXPORTS ldexp
	IMPORTS .TOC. fpTypeGet __errno getNan
	DECLARES 
	USES 
}
Module ldexp.o {
	OBJECT += libfp.a::ldexp.o
}
ObjectFile libfp.a::modf.o {
	NAME Object file modf.o from archive libfp.a
	EXPORTS modf
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module modf.o {
	OBJECT += libfp.a::modf.o
}
ObjectFile libfp.a::acosh.o {
	NAME Object file acosh.o from archive libfp.a
	EXPORTS acosh
	IMPORTS .TOC. log1p sqrt
	DECLARES 
	USES 
}
Module acosh.o {
	OBJECT += libfp.a::acosh.o
}
ObjectFile libfp.a::asincos.o {
	NAME Object file asincos.o from archive libfp.a
	EXPORTS asin acos
	IMPORTS .TOC. __errno getNan copysign sqrt atan2
	DECLARES 
	USES 
}
Module asincos.o {
	OBJECT += libfp.a::asincos.o
}
ObjectFile libfp.a::asinh.o {
	NAME Object file asinh.o from archive libfp.a
	EXPORTS asinh
	IMPORTS .TOC. copysign sqrt log1p
	DECLARES 
	USES 
}
Module asinh.o {
	OBJECT += libfp.a::asinh.o
}
ObjectFile libfp.a::atan.o {
	NAME Object file atan.o from archive libfp.a
	EXPORTS atan
	IMPORTS .TOC. atan2
	DECLARES 
	USES 
}
Module atan.o {
	OBJECT += libfp.a::atan.o
}
ObjectFile libfp.a::atan2.o {
	NAME Object file atan2.o from archive libfp.a
	EXPORTS atan2
	IMPORTS .TOC. _savefpr_25 copysign finite logb scalb _Raise_Inexact _restfpr_25
	DECLARES 
	USES 
}
Module atan2.o {
	OBJECT += libfp.a::atan2.o
}
ObjectFile libfp.a::atanh.o {
	NAME Object file atanh.o from archive libfp.a
	EXPORTS atanh
	IMPORTS .TOC. copysign log1p
	DECLARES 
	USES 
}
Module atanh.o {
	OBJECT += libfp.a::atanh.o
}
ObjectFile libfp.a::ceil.o {
	NAME Object file ceil.o from archive libfp.a
	EXPORTS ceil
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module ceil.o {
	OBJECT += libfp.a::ceil.o
}
ObjectFile libfp.a::cosh.o {
	NAME Object file cosh.o from archive libfp.a
	EXPORTS cosh
	IMPORTS .TOC. copysign exp__E exp scalb
	DECLARES 
	USES 
}
Module cosh.o {
	OBJECT += libfp.a::cosh.o
}
ObjectFile libfp.a::exp.o {
	NAME Object file exp.o from archive libfp.a
	EXPORTS exp
	IMPORTS .TOC. copysign scalb finite __errno
	DECLARES 
	USES 
}
Module exp.o {
	OBJECT += libfp.a::exp.o
}
ObjectFile libfp.a::exp__E.o {
	NAME Object file exp__E.o from archive libfp.a
	EXPORTS exp__E
	IMPORTS .TOC. copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module exp__E.o {
	OBJECT += libfp.a::exp__E.o
}
ObjectFile libfp.a::expm1.o {
	NAME Object file expm1.o from archive libfp.a
	EXPORTS expm1
	IMPORTS .TOC. copysign exp__E scalb finite _Raise_Inexact
	DECLARES 
	USES 
}
Module expm1.o {
	OBJECT += libfp.a::expm1.o
}
ObjectFile libfp.a::floor.o {
	NAME Object file floor.o from archive libfp.a
	EXPORTS floor
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module floor.o {
	OBJECT += libfp.a::floor.o
}
ObjectFile libfp.a::fmod.o {
	NAME Object file fmod.o from archive libfp.a
	EXPORTS fmod
	IMPORTS .TOC. fpTypeGet errnoSet
	DECLARES 
	USES 
}
Module fmod.o {
	OBJECT += libfp.a::fmod.o
}
ObjectFile libfp.a::log.o {
	NAME Object file log.o from archive libfp.a
	EXPORTS log
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L __errno _restfpr_27
	DECLARES 
	USES 
}
Module log.o {
	OBJECT += libfp.a::log.o
}
ObjectFile libfp.a::log10.o {
	NAME Object file log10.o from archive libfp.a
	EXPORTS log10
	IMPORTS .TOC. log
	DECLARES 
	USES 
}
Module log10.o {
	OBJECT += libfp.a::log10.o
}
ObjectFile libfp.a::log1p.o {
	NAME Object file log1p.o from archive libfp.a
	EXPORTS log1p
	IMPORTS .TOC. _savefpr_27 finite copysign logb scalb log__L _restfpr_27
	DECLARES 
	USES 
}
Module log1p.o {
	OBJECT += libfp.a::log1p.o
}
ObjectFile libfp.a::log__L.o {
	NAME Object file log__L.o from archive libfp.a
	EXPORTS log__L
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module log__L.o {
	OBJECT += libfp.a::log__L.o
}
ObjectFile libfp.a::pow.o {
	NAME Object file pow.o from archive libfp.a
	EXPORTS pow_p pow
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L copysign exp__E _Raise_Inexact _restfpr_27 drem __errno
	DECLARES 
	USES 
}
Module pow.o {
	OBJECT += libfp.a::pow.o
}
ObjectFile libfp.a::sincos.o {
	NAME Object file sincos.o from archive libfp.a
	EXPORTS sin cos
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module sincos.o {
	OBJECT += libfp.a::sincos.o
}
ObjectFile libfp.a::sinh.o {
	NAME Object file sinh.o from archive libfp.a
	EXPORTS sinh
	IMPORTS .TOC. copysign expm1 scalb __errno
	DECLARES 
	USES 
}
Module sinh.o {
	OBJECT += libfp.a::sinh.o
}
ObjectFile libfp.a::sqrt.o {
	NAME Object file sqrt.o from archive libfp.a
	EXPORTS sqrt
	IMPORTS .TOC. _savefpr_27 __errno finite logb scalb _Raise_Inexact _restfpr_27
	DECLARES 
	USES 
}
Module sqrt.o {
	OBJECT += libfp.a::sqrt.o
}
ObjectFile libfp.a::support.o {
	NAME Object file support.o from archive libfp.a
	EXPORTS copysign logb finite scalb drem _Raise_Inexact
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module support.o {
	OBJECT += libfp.a::support.o
}
ObjectFile libfp.a::tan.o {
	NAME Object file tan.o from archive libfp.a
	EXPORTS tan
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module tan.o {
	OBJECT += libfp.a::tan.o
}
ObjectFile libfp.a::tanh.o {
	NAME Object file tanh.o from archive libfp.a
	EXPORTS tanh
	IMPORTS .TOC. copysign expm1 _Raise_Inexact finite
	DECLARES 
	USES 
}
Module tanh.o {
	OBJECT += libfp.a::tanh.o
}
ObjectFile libfp.a::fabs.o {
	NAME Object file fabs.o from archive libfp.a
	EXPORTS fabs
	IMPORTS .TOC. fpTypeGet __errno
	DECLARES 
	USES 
}
Module fabs.o {
	OBJECT += libfp.a::fabs.o
}
ObjectFile libfp.a::fpType.o {
	NAME Object file fpType.o from archive libfp.a
	EXPORTS fpTypeGet getInf getNan
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fpType.o {
	OBJECT += libfp.a::fpType.o
}
ObjectFile libfp.a::cabs.o {
	NAME Object file cabs.o from archive libfp.a
	EXPORTS hypot cabs z_abs
	IMPORTS .TOC. _savefpr_28 finite copysign logb _Raise_Inexact sqrt _restfpr_28
	DECLARES 
	USES 
}
Module cabs.o {
	OBJECT += libfp.a::cabs.o
}
ObjectFile libfp.a::mprec.o {
	NAME Object file mprec.o from archive libfp.a
	EXPORTS _Jv_Balloc _Jv_Bfree _Jv_multadd _Jv_s2b _Jv_hi0bits _Jv_lo0bits _Jv_i2b _Jv_mult _Jv_pow5mult _Jv_lshift _Jv__mcmp _Jv__mdiff _Jv_ulp _Jv_b2d _Jv_d2b _Jv_ratio _mprec_log10 _Jv__mprec_tens _Jv__mprec_bigtens _Jv__mprec_tinytens
	IMPORTS .TOC. malloc memset realloc __assert memcpy
	DECLARES 
	USES 
}
Module mprec.o {
	OBJECT += libfp.a::mprec.o
}
ObjectFile libfp.a::dtoa.o {
	NAME Object file dtoa.o from archive libfp.a
	EXPORTS _Jv_dtoa_r free_Bigints __dtoa
	IMPORTS .TOC. _Jv__mcmp _Jv_Bfree _Jv_d2b _Jv__mprec_tens _Jv_Balloc _Jv__mprec_bigtens _Jv_i2b _Jv_pow5mult _Jv_mult _Jv_hi0bits _Jv_lshift _Jv_multadd memcpy _Jv__mdiff free memset strncpy
	DECLARES 
	USES 
}
Module dtoa.o {
	OBJECT += libfp.a::dtoa.o
}
ObjectFile libfp.a::bsd_cvt.o {
	NAME Object file bsd_cvt.o from archive libfp.a
	EXPORTS setAlt setFpt bsd_cvt
	IMPORTS .TOC. __dtoa
	DECLARES 
	USES 
}
Module bsd_cvt.o {
	OBJECT += libfp.a::bsd_cvt.o
}
ObjectFile libfp.a::fioBaseLib.o {
	NAME Object file fioBaseLib.o from archive libfp.a
	EXPORTS fioBaseLibInit printErr sprintf fioBufPut fioFormatV fieldSzIncludeSign printf fioBufPrint oprintf printExc snprintf fioSnBufPut
	IMPORTS .TOC. _func_printErr _func_altivecProbeRtn malloc memchr strlen free _func_fioFltFormatRtn intContext taskIdSelf kernelLockOwnedByMe _func_excJobAdd vmLibInfo sysExcMsg evtAction vxAtomic32Add edrBufLock edrBufUnlock taskUnsafe _func_shellExcPrint taskClassId eventPointSwHandle bcopy _func_consoleOut _func_kwrite
	DECLARES _func_printExcPrintHook
	USES 
}
Module fioBaseLib.o {
	OBJECT += libfp.a::fioBaseLib.o
}
ObjectFile libfp.a::floatLib.o {
	NAME Object file floatLib.o from archive libfp.a
	EXPORTS fioFltInstall floatInit
	IMPORTS .TOC. _func_fioFltFormatRtn _func_fioFltScanRtn bsd_cvt __ctype_tolower fabs fpTypeGet strcpy ldexp
	DECLARES 
	USES 
}
Module floatLib.o {
	OBJECT += libfp.a::floatLib.o
}
ObjectFile libfp.a::floatFuncBind.o {
	NAME Object file floatFuncBind.o from archive libfp.a
	EXPORTS _func_fioFltFormatRtn _func_fioFltScanRtn
	IMPORTS 
	DECLARES 
	USES 
}
Module floatFuncBind.o {
	OBJECT += libfp.a::floatFuncBind.o
}
ObjectFile libfp.a::fioFuncBind.o {
	NAME Object file fioFuncBind.o from archive libfp.a
	EXPORTS 
	IMPORTS 
	DECLARES _func_printErr
	USES 
}
Module fioFuncBind.o {
	OBJECT += libfp.a::fioFuncBind.o
}
ObjectFile libfp.a::e_fmod.o {
	NAME Object file e_fmod.o from archive libfp.a
	EXPORTS __ieee754_fmod
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module e_fmod.o {
	OBJECT += libfp.a::e_fmod.o
}
ObjectFile libfp.a::e_pow.o {
	NAME Object file e_pow.o from archive libfp.a
	EXPORTS __ieee754_pow
	IMPORTS .TOC. _savefpr_28 __ieee754_sqrt fabs getNan scalbn _restfpr_28
	DECLARES 
	USES 
}
Module e_pow.o {
	OBJECT += libfp.a::e_pow.o
}
ObjectFile libfp.a::e_remainder.o {
	NAME Object file e_remainder.o from archive libfp.a
	EXPORTS __ieee754_remainder
	IMPORTS .TOC. __ieee754_fmod fabs
	DECLARES 
	USES 
}
Module e_remainder.o {
	OBJECT += libfp.a::e_remainder.o
}
ObjectFile libfp.a::s_rint.o {
	NAME Object file s_rint.o from archive libfp.a
	EXPORTS rint
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module s_rint.o {
	OBJECT += libfp.a::s_rint.o
}
ObjectFile libfp.a::s_scalbn.o {
	NAME Object file s_scalbn.o from archive libfp.a
	EXPORTS scalbn
	IMPORTS .TOC. copysign
	DECLARES 
	USES 
}
Module s_scalbn.o {
	OBJECT += libfp.a::s_scalbn.o
}
ObjectFile libfp.a::e_sqrt.o {
	NAME Object file e_sqrt.o from archive libfp.a
	EXPORTS __ieee754_sqrt
	IMPORTS .TOC. getNan
	DECLARES 
	USES 
}
Module e_sqrt.o {
	OBJECT += libfp.a::e_sqrt.o
}
ObjectFile libfp.a::fioLib.o {
	NAME Object file fioLib.o from archive libfp.a
	EXPORTS fioLibInit voprintf fdprintf vprintf vfdprintf vsprintf vsnprintf fioRead fioRdString scanCharSet scanField fioScanV sscanf
	IMPORTS .TOC. printErr _func_printErr fioBufPrint fioFormatV fioBufPut fioSnBufPut read __ctype _func_altivecProbeRtn _func_fioFltScanRtn
	DECLARES 
	USES 
}
Module fioLib.o {
	OBJECT += libfp.a::fioLib.o
}
Library libfp.a {
	MODULES libfp.a::frexp.o libfp.a::ldexp.o libfp.a::modf.o libfp.a::acosh.o libfp.a::asincos.o libfp.a::asinh.o libfp.a::atan.o libfp.a::atan2.o libfp.a::atanh.o libfp.a::ceil.o libfp.a::cosh.o libfp.a::exp.o libfp.a::exp__E.o libfp.a::expm1.o libfp.a::floor.o libfp.a::fmod.o libfp.a::log.o libfp.a::log10.o libfp.a::log1p.o libfp.a::log__L.o libfp.a::pow.o libfp.a::sincos.o libfp.a::sinh.o libfp.a::sqrt.o libfp.a::support.o libfp.a::tan.o libfp.a::tanh.o libfp.a::fabs.o libfp.a::fpType.o libfp.a::cabs.o libfp.a::mprec.o libfp.a::dtoa.o libfp.a::bsd_cvt.o libfp.a::fioBaseLib.o libfp.a::floatLib.o libfp.a::floatFuncBind.o libfp.a::fioFuncBind.o libfp.a::e_fmod.o libfp.a::e_pow.o libfp.a::e_remainder.o libfp.a::s_rint.o libfp.a::s_scalbn.o libfp.a::e_sqrt.o libfp.a::fioLib.o
}
Symbol frexp {
}
Symbol .TOC. {
}
Symbol fpTypeGet {
}
Symbol __errno {
}
Symbol fabs {
}
Symbol ldexp {
}
Symbol getNan {
}
Symbol modf {
}
Symbol acosh {
}
Symbol log1p {
}
Symbol sqrt {
}
Symbol asin {
}
Symbol copysign {
}
Symbol atan2 {
}
Symbol acos {
}
Symbol asinh {
}
Symbol atan {
}
Symbol _savefpr_25 {
}
Symbol finite {
}
Symbol logb {
}
Symbol scalb {
}
Symbol _Raise_Inexact {
}
Symbol _restfpr_25 {
}
Symbol atanh {
}
Symbol ceil {
}
Symbol cosh {
}
Symbol exp__E {
}
Symbol exp {
}
Symbol expm1 {
}
Symbol floor {
}
Symbol fmod {
}
Symbol errnoSet {
}
Symbol log {
}
Symbol _savefpr_27 {
}
Symbol log__L {
}
Symbol _restfpr_27 {
}
Symbol log10 {
}
Symbol pow_p {
}
Symbol pow {
}
Symbol drem {
}
Symbol sin {
}
Symbol cos {
}
Symbol sinh {
}
Symbol tan {
}
Symbol tanh {
}
Symbol getInf {
}
Symbol hypot {
}
Symbol _savefpr_28 {
}
Symbol _restfpr_28 {
}
Symbol cabs {
}
Symbol z_abs {
}
Symbol malloc {
}
Symbol memset {
}
Symbol realloc {
}
Symbol _Jv_Balloc {
}
Symbol __assert {
}
Symbol _Jv_Bfree {
}
Symbol _Jv_multadd {
}
Symbol memcpy {
}
Symbol _Jv_s2b {
}
Symbol _Jv_hi0bits {
}
Symbol _Jv_lo0bits {
}
Symbol _Jv_i2b {
}
Symbol _Jv_mult {
}
Symbol _Jv_pow5mult {
}
Symbol _Jv_lshift {
}
Symbol _Jv__mcmp {
}
Symbol _Jv__mdiff {
}
Symbol _Jv_ulp {
}
Symbol _Jv_b2d {
}
Symbol _Jv_d2b {
}
Symbol _Jv_ratio {
}
Symbol _mprec_log10 {
}
Symbol _Jv__mprec_tens {
}
Symbol _Jv__mprec_bigtens {
}
Symbol _Jv__mprec_tinytens {
}
Symbol _Jv_dtoa_r {
}
Symbol free_Bigints {
}
Symbol free {
}
Symbol __dtoa {
}
Symbol strncpy {
}
Symbol setAlt {
}
Symbol setFpt {
}
Symbol bsd_cvt {
}
Symbol fioBaseLibInit {
}
Symbol printErr {
}
Symbol _func_printErr {
}
Symbol sprintf {
}
Symbol fioBufPut {
}
Symbol fioFormatV {
}
Symbol _func_altivecProbeRtn {
}
Symbol memchr {
}
Symbol strlen {
}
Symbol _func_fioFltFormatRtn {
}
Symbol fieldSzIncludeSign {
}
Symbol printf {
}
Symbol fioBufPrint {
}
Symbol oprintf {
}
Symbol printExc {
}
Symbol intContext {
}
Symbol taskIdSelf {
}
Symbol kernelLockOwnedByMe {
}
Symbol _func_printExcPrintHook {
}
Symbol _func_excJobAdd {
}
Symbol vmLibInfo {
}
Symbol sysExcMsg {
}
Symbol evtAction {
}
Symbol vxAtomic32Add {
}
Symbol edrBufLock {
}
Symbol edrBufUnlock {
}
Symbol taskUnsafe {
}
Symbol _func_shellExcPrint {
}
Symbol taskClassId {
}
Symbol eventPointSwHandle {
}
Symbol snprintf {
}
Symbol fioSnBufPut {
}
Symbol bcopy {
}
Symbol _func_consoleOut {
}
Symbol _func_kwrite {
}
Symbol fioFltInstall {
}
Symbol _func_fioFltScanRtn {
}
Symbol floatInit {
}
Symbol __ctype_tolower {
}
Symbol strcpy {
}
Symbol __ieee754_fmod {
}
Symbol __ieee754_pow {
}
Symbol __ieee754_sqrt {
}
Symbol scalbn {
}
Symbol __ieee754_remainder {
}
Symbol rint {
}
Symbol fioLibInit {
}
Symbol voprintf {
}
Symbol fdprintf {
}
Symbol vprintf {
}
Symbol vfdprintf {
}
Symbol vsprintf {
}
Symbol vsnprintf {
}
Symbol fioRead {
}
Symbol read {
}
Symbol fioRdString {
}
Symbol __ctype {
}
Symbol scanCharSet {
}
Symbol scanField {
}
Symbol fioScanV {
}
Symbol sscanf {
}
ObjectFile libfp.a::frexp.o {
	NAME Object file frexp.o from archive libfp.a
	EXPORTS frexp
	IMPORTS .TOC. fpTypeGet __errno fabs
	DECLARES 
	USES 
}
Module frexp.o {
	OBJECT += libfp.a::frexp.o
}
ObjectFile libfp.a::ldexp.o {
	NAME Object file ldexp.o from archive libfp.a
	EXPORTS ldexp
	IMPORTS .TOC. fpTypeGet __errno getNan
	DECLARES 
	USES 
}
Module ldexp.o {
	OBJECT += libfp.a::ldexp.o
}
ObjectFile libfp.a::modf.o {
	NAME Object file modf.o from archive libfp.a
	EXPORTS modf
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module modf.o {
	OBJECT += libfp.a::modf.o
}
ObjectFile libfp.a::acosh.o {
	NAME Object file acosh.o from archive libfp.a
	EXPORTS acosh
	IMPORTS .TOC. log1p sqrt
	DECLARES 
	USES 
}
Module acosh.o {
	OBJECT += libfp.a::acosh.o
}
ObjectFile libfp.a::asincos.o {
	NAME Object file asincos.o from archive libfp.a
	EXPORTS asin acos
	IMPORTS .TOC. __errno getNan copysign sqrt atan2
	DECLARES 
	USES 
}
Module asincos.o {
	OBJECT += libfp.a::asincos.o
}
ObjectFile libfp.a::asinh.o {
	NAME Object file asinh.o from archive libfp.a
	EXPORTS asinh
	IMPORTS .TOC. copysign sqrt log1p
	DECLARES 
	USES 
}
Module asinh.o {
	OBJECT += libfp.a::asinh.o
}
ObjectFile libfp.a::atan.o {
	NAME Object file atan.o from archive libfp.a
	EXPORTS atan
	IMPORTS .TOC. atan2
	DECLARES 
	USES 
}
Module atan.o {
	OBJECT += libfp.a::atan.o
}
ObjectFile libfp.a::atan2.o {
	NAME Object file atan2.o from archive libfp.a
	EXPORTS atan2
	IMPORTS .TOC. _savefpr_25 copysign finite logb scalb _Raise_Inexact _restfpr_25
	DECLARES 
	USES 
}
Module atan2.o {
	OBJECT += libfp.a::atan2.o
}
ObjectFile libfp.a::atanh.o {
	NAME Object file atanh.o from archive libfp.a
	EXPORTS atanh
	IMPORTS .TOC. copysign log1p
	DECLARES 
	USES 
}
Module atanh.o {
	OBJECT += libfp.a::atanh.o
}
ObjectFile libfp.a::ceil.o {
	NAME Object file ceil.o from archive libfp.a
	EXPORTS ceil
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module ceil.o {
	OBJECT += libfp.a::ceil.o
}
ObjectFile libfp.a::cosh.o {
	NAME Object file cosh.o from archive libfp.a
	EXPORTS cosh
	IMPORTS .TOC. copysign exp__E exp scalb
	DECLARES 
	USES 
}
Module cosh.o {
	OBJECT += libfp.a::cosh.o
}
ObjectFile libfp.a::exp.o {
	NAME Object file exp.o from archive libfp.a
	EXPORTS exp
	IMPORTS .TOC. copysign scalb finite __errno
	DECLARES 
	USES 
}
Module exp.o {
	OBJECT += libfp.a::exp.o
}
ObjectFile libfp.a::exp__E.o {
	NAME Object file exp__E.o from archive libfp.a
	EXPORTS exp__E
	IMPORTS .TOC. copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module exp__E.o {
	OBJECT += libfp.a::exp__E.o
}
ObjectFile libfp.a::expm1.o {
	NAME Object file expm1.o from archive libfp.a
	EXPORTS expm1
	IMPORTS .TOC. copysign exp__E scalb finite _Raise_Inexact
	DECLARES 
	USES 
}
Module expm1.o {
	OBJECT += libfp.a::expm1.o
}
ObjectFile libfp.a::floor.o {
	NAME Object file floor.o from archive libfp.a
	EXPORTS floor
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module floor.o {
	OBJECT += libfp.a::floor.o
}
ObjectFile libfp.a::fmod.o {
	NAME Object file fmod.o from archive libfp.a
	EXPORTS fmod
	IMPORTS .TOC. fpTypeGet errnoSet
	DECLARES 
	USES 
}
Module fmod.o {
	OBJECT += libfp.a::fmod.o
}
ObjectFile libfp.a::log.o {
	NAME Object file log.o from archive libfp.a
	EXPORTS log
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L __errno _restfpr_27
	DECLARES 
	USES 
}
Module log.o {
	OBJECT += libfp.a::log.o
}
ObjectFile libfp.a::log10.o {
	NAME Object file log10.o from archive libfp.a
	EXPORTS log10
	IMPORTS .TOC. log
	DECLARES 
	USES 
}
Module log10.o {
	OBJECT += libfp.a::log10.o
}
ObjectFile libfp.a::log1p.o {
	NAME Object file log1p.o from archive libfp.a
	EXPORTS log1p
	IMPORTS .TOC. _savefpr_27 finite copysign logb scalb log__L _restfpr_27
	DECLARES 
	USES 
}
Module log1p.o {
	OBJECT += libfp.a::log1p.o
}
ObjectFile libfp.a::log__L.o {
	NAME Object file log__L.o from archive libfp.a
	EXPORTS log__L
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module log__L.o {
	OBJECT += libfp.a::log__L.o
}
ObjectFile libfp.a::pow.o {
	NAME Object file pow.o from archive libfp.a
	EXPORTS pow_p pow
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L copysign exp__E _Raise_Inexact _restfpr_27 drem __errno
	DECLARES 
	USES 
}
Module pow.o {
	OBJECT += libfp.a::pow.o
}
ObjectFile libfp.a::sincos.o {
	NAME Object file sincos.o from archive libfp.a
	EXPORTS sin cos
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module sincos.o {
	OBJECT += libfp.a::sincos.o
}
ObjectFile libfp.a::sinh.o {
	NAME Object file sinh.o from archive libfp.a
	EXPORTS sinh
	IMPORTS .TOC. copysign expm1 scalb __errno
	DECLARES 
	USES 
}
Module sinh.o {
	OBJECT += libfp.a::sinh.o
}
ObjectFile libfp.a::sqrt.o {
	NAME Object file sqrt.o from archive libfp.a
	EXPORTS sqrt
	IMPORTS .TOC. _savefpr_27 __errno finite logb scalb _Raise_Inexact _restfpr_27
	DECLARES 
	USES 
}
Module sqrt.o {
	OBJECT += libfp.a::sqrt.o
}
ObjectFile libfp.a::support.o {
	NAME Object file support.o from archive libfp.a
	EXPORTS copysign logb finite scalb drem _Raise_Inexact
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module support.o {
	OBJECT += libfp.a::support.o
}
ObjectFile libfp.a::tan.o {
	NAME Object file tan.o from archive libfp.a
	EXPORTS tan
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module tan.o {
	OBJECT += libfp.a::tan.o
}
ObjectFile libfp.a::tanh.o {
	NAME Object file tanh.o from archive libfp.a
	EXPORTS tanh
	IMPORTS .TOC. copysign expm1 _Raise_Inexact finite
	DECLARES 
	USES 
}
Module tanh.o {
	OBJECT += libfp.a::tanh.o
}
ObjectFile libfp.a::fabs.o {
	NAME Object file fabs.o from archive libfp.a
	EXPORTS fabs
	IMPORTS .TOC. fpTypeGet __errno
	DECLARES 
	USES 
}
Module fabs.o {
	OBJECT += libfp.a::fabs.o
}
ObjectFile libfp.a::fpType.o {
	NAME Object file fpType.o from archive libfp.a
	EXPORTS fpTypeGet getInf getNan
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fpType.o {
	OBJECT += libfp.a::fpType.o
}
ObjectFile libfp.a::cabs.o {
	NAME Object file cabs.o from archive libfp.a
	EXPORTS hypot cabs z_abs
	IMPORTS .TOC. _savefpr_28 finite copysign logb _Raise_Inexact sqrt _restfpr_28
	DECLARES 
	USES 
}
Module cabs.o {
	OBJECT += libfp.a::cabs.o
}
ObjectFile libfp.a::mprec.o {
	NAME Object file mprec.o from archive libfp.a
	EXPORTS _Jv_Balloc _Jv_Bfree _Jv_multadd _Jv_s2b _Jv_hi0bits _Jv_lo0bits _Jv_i2b _Jv_mult _Jv_pow5mult _Jv_lshift _Jv__mcmp _Jv__mdiff _Jv_ulp _Jv_b2d _Jv_d2b _Jv_ratio _mprec_log10 _Jv__mprec_tens _Jv__mprec_bigtens _Jv__mprec_tinytens
	IMPORTS .TOC. malloc memset realloc __assert memcpy
	DECLARES 
	USES 
}
Module mprec.o {
	OBJECT += libfp.a::mprec.o
}
ObjectFile libfp.a::dtoa.o {
	NAME Object file dtoa.o from archive libfp.a
	EXPORTS _Jv_dtoa_r free_Bigints __dtoa
	IMPORTS .TOC. _Jv__mcmp _Jv_Bfree _Jv_d2b _Jv__mprec_tens _Jv_Balloc _Jv__mprec_bigtens _Jv_i2b _Jv_pow5mult _Jv_mult _Jv_hi0bits _Jv_lshift _Jv_multadd memcpy _Jv__mdiff free memset strncpy
	DECLARES 
	USES 
}
Module dtoa.o {
	OBJECT += libfp.a::dtoa.o
}
ObjectFile libfp.a::bsd_cvt.o {
	NAME Object file bsd_cvt.o from archive libfp.a
	EXPORTS setAlt setFpt bsd_cvt
	IMPORTS .TOC. __dtoa
	DECLARES 
	USES 
}
Module bsd_cvt.o {
	OBJECT += libfp.a::bsd_cvt.o
}
ObjectFile libfp.a::fioBaseLib.o {
	NAME Object file fioBaseLib.o from archive libfp.a
	EXPORTS fioBaseLibInit printErr sprintf fioBufPut fioFormatV fieldSzIncludeSign printf fioBufPrint oprintf printExc snprintf fioSnBufPut
	IMPORTS .TOC. _func_printErr _func_altivecProbeRtn malloc memchr strlen free _func_fioFltFormatRtn intContext taskIdSelf kernelLockOwnedByMe _func_excJobAdd vmLibInfo sysExcMsg evtAction vxAtomic32Add edrBufLock edrBufUnlock taskUnsafe _func_shellExcPrint taskClassId eventPointSwHandle bcopy _func_consoleOut _func_kwrite
	DECLARES _func_printExcPrintHook
	USES 
}
Module fioBaseLib.o {
	OBJECT += libfp.a::fioBaseLib.o
}
ObjectFile libfp.a::floatLib.o {
	NAME Object file floatLib.o from archive libfp.a
	EXPORTS fioFltInstall floatInit
	IMPORTS .TOC. _func_fioFltFormatRtn _func_fioFltScanRtn bsd_cvt __ctype_tolower fabs fpTypeGet strcpy ldexp
	DECLARES 
	USES 
}
Module floatLib.o {
	OBJECT += libfp.a::floatLib.o
}
ObjectFile libfp.a::floatFuncBind.o {
	NAME Object file floatFuncBind.o from archive libfp.a
	EXPORTS _func_fioFltFormatRtn _func_fioFltScanRtn
	IMPORTS 
	DECLARES 
	USES 
}
Module floatFuncBind.o {
	OBJECT += libfp.a::floatFuncBind.o
}
ObjectFile libfp.a::fioFuncBind.o {
	NAME Object file fioFuncBind.o from archive libfp.a
	EXPORTS 
	IMPORTS 
	DECLARES _func_printErr
	USES 
}
Module fioFuncBind.o {
	OBJECT += libfp.a::fioFuncBind.o
}
ObjectFile libfp.a::e_fmod.o {
	NAME Object file e_fmod.o from archive libfp.a
	EXPORTS __ieee754_fmod
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module e_fmod.o {
	OBJECT += libfp.a::e_fmod.o
}
ObjectFile libfp.a::e_pow.o {
	NAME Object file e_pow.o from archive libfp.a
	EXPORTS __ieee754_pow
	IMPORTS .TOC. _savefpr_28 __ieee754_sqrt fabs getNan scalbn _restfpr_28
	DECLARES 
	USES 
}
Module e_pow.o {
	OBJECT += libfp.a::e_pow.o
}
ObjectFile libfp.a::e_remainder.o {
	NAME Object file e_remainder.o from archive libfp.a
	EXPORTS __ieee754_remainder
	IMPORTS .TOC. __ieee754_fmod fabs
	DECLARES 
	USES 
}
Module e_remainder.o {
	OBJECT += libfp.a::e_remainder.o
}
ObjectFile libfp.a::s_rint.o {
	NAME Object file s_rint.o from archive libfp.a
	EXPORTS rint
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module s_rint.o {
	OBJECT += libfp.a::s_rint.o
}
ObjectFile libfp.a::s_scalbn.o {
	NAME Object file s_scalbn.o from archive libfp.a
	EXPORTS scalbn
	IMPORTS .TOC. copysign
	DECLARES 
	USES 
}
Module s_scalbn.o {
	OBJECT += libfp.a::s_scalbn.o
}
ObjectFile libfp.a::e_sqrt.o {
	NAME Object file e_sqrt.o from archive libfp.a
	EXPORTS __ieee754_sqrt
	IMPORTS .TOC. getNan
	DECLARES 
	USES 
}
Module e_sqrt.o {
	OBJECT += libfp.a::e_sqrt.o
}
ObjectFile libfp.a::fioLib.o {
	NAME Object file fioLib.o from archive libfp.a
	EXPORTS fioLibInit voprintf fdprintf vprintf vfdprintf vsprintf vsnprintf fioRead fioRdString scanCharSet scanField fioScanV sscanf
	IMPORTS .TOC. printErr _func_printErr fioBufPrint fioFormatV fioBufPut fioSnBufPut read __ctype _func_altivecProbeRtn _func_fioFltScanRtn
	DECLARES 
	USES 
}
Module fioLib.o {
	OBJECT += libfp.a::fioLib.o
}
Library libfp.a {
	MODULES libfp.a::frexp.o libfp.a::ldexp.o libfp.a::modf.o libfp.a::acosh.o libfp.a::asincos.o libfp.a::asinh.o libfp.a::atan.o libfp.a::atan2.o libfp.a::atanh.o libfp.a::ceil.o libfp.a::cosh.o libfp.a::exp.o libfp.a::exp__E.o libfp.a::expm1.o libfp.a::floor.o libfp.a::fmod.o libfp.a::log.o libfp.a::log10.o libfp.a::log1p.o libfp.a::log__L.o libfp.a::pow.o libfp.a::sincos.o libfp.a::sinh.o libfp.a::sqrt.o libfp.a::support.o libfp.a::tan.o libfp.a::tanh.o libfp.a::fabs.o libfp.a::fpType.o libfp.a::cabs.o libfp.a::mprec.o libfp.a::dtoa.o libfp.a::bsd_cvt.o libfp.a::fioBaseLib.o libfp.a::floatLib.o libfp.a::floatFuncBind.o libfp.a::fioFuncBind.o libfp.a::e_fmod.o libfp.a::e_pow.o libfp.a::e_remainder.o libfp.a::s_rint.o libfp.a::s_scalbn.o libfp.a::e_sqrt.o libfp.a::fioLib.o
}
Symbol frexp {
}
Symbol .TOC. {
}
Symbol fpTypeGet {
}
Symbol __errno {
}
Symbol fabs {
}
Symbol ldexp {
}
Symbol getNan {
}
Symbol modf {
}
Symbol acosh {
}
Symbol log1p {
}
Symbol sqrt {
}
Symbol asin {
}
Symbol copysign {
}
Symbol atan2 {
}
Symbol acos {
}
Symbol asinh {
}
Symbol atan {
}
Symbol _savefpr_25 {
}
Symbol finite {
}
Symbol logb {
}
Symbol scalb {
}
Symbol _Raise_Inexact {
}
Symbol _restfpr_25 {
}
Symbol atanh {
}
Symbol ceil {
}
Symbol cosh {
}
Symbol exp__E {
}
Symbol exp {
}
Symbol expm1 {
}
Symbol floor {
}
Symbol fmod {
}
Symbol errnoSet {
}
Symbol log {
}
Symbol _savefpr_27 {
}
Symbol log__L {
}
Symbol _restfpr_27 {
}
Symbol log10 {
}
Symbol pow_p {
}
Symbol pow {
}
Symbol drem {
}
Symbol sin {
}
Symbol cos {
}
Symbol sinh {
}
Symbol tan {
}
Symbol tanh {
}
Symbol getInf {
}
Symbol hypot {
}
Symbol _savefpr_28 {
}
Symbol _restfpr_28 {
}
Symbol cabs {
}
Symbol z_abs {
}
Symbol malloc {
}
Symbol memset {
}
Symbol realloc {
}
Symbol _Jv_Balloc {
}
Symbol __assert {
}
Symbol _Jv_Bfree {
}
Symbol _Jv_multadd {
}
Symbol memcpy {
}
Symbol _Jv_s2b {
}
Symbol _Jv_hi0bits {
}
Symbol _Jv_lo0bits {
}
Symbol _Jv_i2b {
}
Symbol _Jv_mult {
}
Symbol _Jv_pow5mult {
}
Symbol _Jv_lshift {
}
Symbol _Jv__mcmp {
}
Symbol _Jv__mdiff {
}
Symbol _Jv_ulp {
}
Symbol _Jv_b2d {
}
Symbol _Jv_d2b {
}
Symbol _Jv_ratio {
}
Symbol _mprec_log10 {
}
Symbol _Jv__mprec_tens {
}
Symbol _Jv__mprec_bigtens {
}
Symbol _Jv__mprec_tinytens {
}
Symbol _Jv_dtoa_r {
}
Symbol free_Bigints {
}
Symbol free {
}
Symbol __dtoa {
}
Symbol strncpy {
}
Symbol setAlt {
}
Symbol setFpt {
}
Symbol bsd_cvt {
}
Symbol fioBaseLibInit {
}
Symbol printErr {
}
Symbol _func_printErr {
}
Symbol sprintf {
}
Symbol fioBufPut {
}
Symbol fioFormatV {
}
Symbol _func_altivecProbeRtn {
}
Symbol memchr {
}
Symbol strlen {
}
Symbol _func_fioFltFormatRtn {
}
Symbol fieldSzIncludeSign {
}
Symbol printf {
}
Symbol fioBufPrint {
}
Symbol oprintf {
}
Symbol printExc {
}
Symbol intContext {
}
Symbol taskIdSelf {
}
Symbol kernelLockOwnedByMe {
}
Symbol _func_printExcPrintHook {
}
Symbol _func_excJobAdd {
}
Symbol vmLibInfo {
}
Symbol sysExcMsg {
}
Symbol evtAction {
}
Symbol vxAtomic32Add {
}
Symbol edrBufLock {
}
Symbol edrBufUnlock {
}
Symbol taskUnsafe {
}
Symbol _func_shellExcPrint {
}
Symbol taskClassId {
}
Symbol eventPointSwHandle {
}
Symbol snprintf {
}
Symbol fioSnBufPut {
}
Symbol bcopy {
}
Symbol _func_consoleOut {
}
Symbol _func_kwrite {
}
Symbol fioFltInstall {
}
Symbol _func_fioFltScanRtn {
}
Symbol floatInit {
}
Symbol __ctype_tolower {
}
Symbol strcpy {
}
Symbol __ieee754_fmod {
}
Symbol __ieee754_pow {
}
Symbol __ieee754_sqrt {
}
Symbol scalbn {
}
Symbol __ieee754_remainder {
}
Symbol rint {
}
Symbol fioLibInit {
}
Symbol voprintf {
}
Symbol fdprintf {
}
Symbol vprintf {
}
Symbol vfdprintf {
}
Symbol vsprintf {
}
Symbol vsnprintf {
}
Symbol fioRead {
}
Symbol read {
}
Symbol fioRdString {
}
Symbol __ctype {
}
Symbol scanCharSet {
}
Symbol scanField {
}
Symbol fioScanV {
}
Symbol sscanf {
}
ObjectFile libfp.a::frexp.o {
	NAME Object file frexp.o from archive libfp.a
	EXPORTS frexp
	IMPORTS .TOC. fpTypeGet __errno fabs
	DECLARES 
	USES 
}
Module frexp.o {
	OBJECT += libfp.a::frexp.o
}
ObjectFile libfp.a::ldexp.o {
	NAME Object file ldexp.o from archive libfp.a
	EXPORTS ldexp
	IMPORTS .TOC. fpTypeGet __errno getNan
	DECLARES 
	USES 
}
Module ldexp.o {
	OBJECT += libfp.a::ldexp.o
}
ObjectFile libfp.a::modf.o {
	NAME Object file modf.o from archive libfp.a
	EXPORTS modf
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module modf.o {
	OBJECT += libfp.a::modf.o
}
ObjectFile libfp.a::acosh.o {
	NAME Object file acosh.o from archive libfp.a
	EXPORTS acosh
	IMPORTS .TOC. log1p sqrt
	DECLARES 
	USES 
}
Module acosh.o {
	OBJECT += libfp.a::acosh.o
}
ObjectFile libfp.a::asincos.o {
	NAME Object file asincos.o from archive libfp.a
	EXPORTS asin acos
	IMPORTS .TOC. __errno getNan copysign sqrt atan2
	DECLARES 
	USES 
}
Module asincos.o {
	OBJECT += libfp.a::asincos.o
}
ObjectFile libfp.a::asinh.o {
	NAME Object file asinh.o from archive libfp.a
	EXPORTS asinh
	IMPORTS .TOC. copysign sqrt log1p
	DECLARES 
	USES 
}
Module asinh.o {
	OBJECT += libfp.a::asinh.o
}
ObjectFile libfp.a::atan.o {
	NAME Object file atan.o from archive libfp.a
	EXPORTS atan
	IMPORTS .TOC. atan2
	DECLARES 
	USES 
}
Module atan.o {
	OBJECT += libfp.a::atan.o
}
ObjectFile libfp.a::atan2.o {
	NAME Object file atan2.o from archive libfp.a
	EXPORTS atan2
	IMPORTS .TOC. _savefpr_25 copysign finite logb scalb _Raise_Inexact _restfpr_25
	DECLARES 
	USES 
}
Module atan2.o {
	OBJECT += libfp.a::atan2.o
}
ObjectFile libfp.a::atanh.o {
	NAME Object file atanh.o from archive libfp.a
	EXPORTS atanh
	IMPORTS .TOC. copysign log1p
	DECLARES 
	USES 
}
Module atanh.o {
	OBJECT += libfp.a::atanh.o
}
ObjectFile libfp.a::ceil.o {
	NAME Object file ceil.o from archive libfp.a
	EXPORTS ceil
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module ceil.o {
	OBJECT += libfp.a::ceil.o
}
ObjectFile libfp.a::cosh.o {
	NAME Object file cosh.o from archive libfp.a
	EXPORTS cosh
	IMPORTS .TOC. copysign exp__E exp scalb
	DECLARES 
	USES 
}
Module cosh.o {
	OBJECT += libfp.a::cosh.o
}
ObjectFile libfp.a::exp.o {
	NAME Object file exp.o from archive libfp.a
	EXPORTS exp
	IMPORTS .TOC. copysign scalb finite __errno
	DECLARES 
	USES 
}
Module exp.o {
	OBJECT += libfp.a::exp.o
}
ObjectFile libfp.a::exp__E.o {
	NAME Object file exp__E.o from archive libfp.a
	EXPORTS exp__E
	IMPORTS .TOC. copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module exp__E.o {
	OBJECT += libfp.a::exp__E.o
}
ObjectFile libfp.a::expm1.o {
	NAME Object file expm1.o from archive libfp.a
	EXPORTS expm1
	IMPORTS .TOC. copysign exp__E scalb finite _Raise_Inexact
	DECLARES 
	USES 
}
Module expm1.o {
	OBJECT += libfp.a::expm1.o
}
ObjectFile libfp.a::floor.o {
	NAME Object file floor.o from archive libfp.a
	EXPORTS floor
	IMPORTS .TOC. fpTypeGet
	DECLARES 
	USES 
}
Module floor.o {
	OBJECT += libfp.a::floor.o
}
ObjectFile libfp.a::fmod.o {
	NAME Object file fmod.o from archive libfp.a
	EXPORTS fmod
	IMPORTS .TOC. fpTypeGet errnoSet
	DECLARES 
	USES 
}
Module fmod.o {
	OBJECT += libfp.a::fmod.o
}
ObjectFile libfp.a::log.o {
	NAME Object file log.o from archive libfp.a
	EXPORTS log
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L __errno _restfpr_27
	DECLARES 
	USES 
}
Module log.o {
	OBJECT += libfp.a::log.o
}
ObjectFile libfp.a::log10.o {
	NAME Object file log10.o from archive libfp.a
	EXPORTS log10
	IMPORTS .TOC. log
	DECLARES 
	USES 
}
Module log10.o {
	OBJECT += libfp.a::log10.o
}
ObjectFile libfp.a::log1p.o {
	NAME Object file log1p.o from archive libfp.a
	EXPORTS log1p
	IMPORTS .TOC. _savefpr_27 finite copysign logb scalb log__L _restfpr_27
	DECLARES 
	USES 
}
Module log1p.o {
	OBJECT += libfp.a::log1p.o
}
ObjectFile libfp.a::log__L.o {
	NAME Object file log__L.o from archive libfp.a
	EXPORTS log__L
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module log__L.o {
	OBJECT += libfp.a::log__L.o
}
ObjectFile libfp.a::pow.o {
	NAME Object file pow.o from archive libfp.a
	EXPORTS pow_p pow
	IMPORTS .TOC. _savefpr_27 finite logb scalb log__L copysign exp__E _Raise_Inexact _restfpr_27 drem __errno
	DECLARES 
	USES 
}
Module pow.o {
	OBJECT += libfp.a::pow.o
}
ObjectFile libfp.a::sincos.o {
	NAME Object file sincos.o from archive libfp.a
	EXPORTS sin cos
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module sincos.o {
	OBJECT += libfp.a::sincos.o
}
ObjectFile libfp.a::sinh.o {
	NAME Object file sinh.o from archive libfp.a
	EXPORTS sinh
	IMPORTS .TOC. copysign expm1 scalb __errno
	DECLARES 
	USES 
}
Module sinh.o {
	OBJECT += libfp.a::sinh.o
}
ObjectFile libfp.a::sqrt.o {
	NAME Object file sqrt.o from archive libfp.a
	EXPORTS sqrt
	IMPORTS .TOC. _savefpr_27 __errno finite logb scalb _Raise_Inexact _restfpr_27
	DECLARES 
	USES 
}
Module sqrt.o {
	OBJECT += libfp.a::sqrt.o
}
ObjectFile libfp.a::support.o {
	NAME Object file support.o from archive libfp.a
	EXPORTS copysign logb finite scalb drem _Raise_Inexact
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module support.o {
	OBJECT += libfp.a::support.o
}
ObjectFile libfp.a::tan.o {
	NAME Object file tan.o from archive libfp.a
	EXPORTS tan
	IMPORTS .TOC. finite drem copysign _Raise_Inexact
	DECLARES 
	USES 
}
Module tan.o {
	OBJECT += libfp.a::tan.o
}
ObjectFile libfp.a::tanh.o {
	NAME Object file tanh.o from archive libfp.a
	EXPORTS tanh
	IMPORTS .TOC. copysign expm1 _Raise_Inexact finite
	DECLARES 
	USES 
}
Module tanh.o {
	OBJECT += libfp.a::tanh.o
}
ObjectFile libfp.a::fabs.o {
	NAME Object file fabs.o from archive libfp.a
	EXPORTS fabs
	IMPORTS .TOC. fpTypeGet __errno
	DECLARES 
	USES 
}
Module fabs.o {
	OBJECT += libfp.a::fabs.o
}
ObjectFile libfp.a::fpType.o {
	NAME Object file fpType.o from archive libfp.a
	EXPORTS fpTypeGet getInf getNan
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module fpType.o {
	OBJECT += libfp.a::fpType.o
}
ObjectFile libfp.a::cabs.o {
	NAME Object file cabs.o from archive libfp.a
	EXPORTS hypot cabs z_abs
	IMPORTS .TOC. _savefpr_28 finite copysign logb _Raise_Inexact sqrt _restfpr_28
	DECLARES 
	USES 
}
Module cabs.o {
	OBJECT += libfp.a::cabs.o
}
ObjectFile libfp.a::mprec.o {
	NAME Object file mprec.o from archive libfp.a
	EXPORTS _Jv_Balloc _Jv_Bfree _Jv_multadd _Jv_s2b _Jv_hi0bits _Jv_lo0bits _Jv_i2b _Jv_mult _Jv_pow5mult _Jv_lshift _Jv__mcmp _Jv__mdiff _Jv_ulp _Jv_b2d _Jv_d2b _Jv_ratio _mprec_log10 _Jv__mprec_tens _Jv__mprec_bigtens _Jv__mprec_tinytens
	IMPORTS .TOC. malloc memset realloc __assert memcpy
	DECLARES 
	USES 
}
Module mprec.o {
	OBJECT += libfp.a::mprec.o
}
ObjectFile libfp.a::dtoa.o {
	NAME Object file dtoa.o from archive libfp.a
	EXPORTS _Jv_dtoa_r free_Bigints __dtoa
	IMPORTS .TOC. _Jv__mcmp _Jv_Bfree _Jv_d2b _Jv__mprec_tens _Jv_Balloc _Jv__mprec_bigtens _Jv_i2b _Jv_pow5mult _Jv_mult _Jv_hi0bits _Jv_lshift _Jv_multadd memcpy _Jv__mdiff free memset strncpy
	DECLARES 
	USES 
}
Module dtoa.o {
	OBJECT += libfp.a::dtoa.o
}
ObjectFile libfp.a::bsd_cvt.o {
	NAME Object file bsd_cvt.o from archive libfp.a
	EXPORTS setAlt setFpt bsd_cvt
	IMPORTS .TOC. __dtoa
	DECLARES 
	USES 
}
Module bsd_cvt.o {
	OBJECT += libfp.a::bsd_cvt.o
}
ObjectFile libfp.a::fioBaseLib.o {
	NAME Object file fioBaseLib.o from archive libfp.a
	EXPORTS fioBaseLibInit printErr sprintf fioBufPut fioFormatV fieldSzIncludeSign printf fioBufPrint oprintf printExc snprintf fioSnBufPut
	IMPORTS .TOC. _func_printErr _func_altivecProbeRtn malloc memchr strlen free _func_fioFltFormatRtn intContext taskIdSelf kernelLockOwnedByMe _func_excJobAdd vmLibInfo sysExcMsg evtAction vxAtomic32Add edrBufLock edrBufUnlock taskUnsafe _func_shellExcPrint taskClassId eventPointSwHandle bcopy _func_consoleOut _func_kwrite
	DECLARES _func_printExcPrintHook
	USES 
}
Module fioBaseLib.o {
	OBJECT += libfp.a::fioBaseLib.o
}
ObjectFile libfp.a::floatLib.o {
	NAME Object file floatLib.o from archive libfp.a
	EXPORTS fioFltInstall floatInit
	IMPORTS .TOC. _func_fioFltFormatRtn _func_fioFltScanRtn bsd_cvt __ctype_tolower fabs fpTypeGet strcpy ldexp
	DECLARES 
	USES 
}
Module floatLib.o {
	OBJECT += libfp.a::floatLib.o
}
ObjectFile libfp.a::floatFuncBind.o {
	NAME Object file floatFuncBind.o from archive libfp.a
	EXPORTS _func_fioFltFormatRtn _func_fioFltScanRtn
	IMPORTS 
	DECLARES 
	USES 
}
Module floatFuncBind.o {
	OBJECT += libfp.a::floatFuncBind.o
}
ObjectFile libfp.a::fioFuncBind.o {
	NAME Object file fioFuncBind.o from archive libfp.a
	EXPORTS 
	IMPORTS 
	DECLARES _func_printErr
	USES 
}
Module fioFuncBind.o {
	OBJECT += libfp.a::fioFuncBind.o
}
ObjectFile libfp.a::e_fmod.o {
	NAME Object file e_fmod.o from archive libfp.a
	EXPORTS __ieee754_fmod
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module e_fmod.o {
	OBJECT += libfp.a::e_fmod.o
}
ObjectFile libfp.a::e_pow.o {
	NAME Object file e_pow.o from archive libfp.a
	EXPORTS __ieee754_pow
	IMPORTS .TOC. _savefpr_28 __ieee754_sqrt fabs getNan scalbn _restfpr_28
	DECLARES 
	USES 
}
Module e_pow.o {
	OBJECT += libfp.a::e_pow.o
}
ObjectFile libfp.a::e_remainder.o {
	NAME Object file e_remainder.o from archive libfp.a
	EXPORTS __ieee754_remainder
	IMPORTS .TOC. __ieee754_fmod fabs
	DECLARES 
	USES 
}
Module e_remainder.o {
	OBJECT += libfp.a::e_remainder.o
}
ObjectFile libfp.a::s_rint.o {
	NAME Object file s_rint.o from archive libfp.a
	EXPORTS rint
	IMPORTS .TOC.
	DECLARES 
	USES 
}
Module s_rint.o {
	OBJECT += libfp.a::s_rint.o
}
ObjectFile libfp.a::s_scalbn.o {
	NAME Object file s_scalbn.o from archive libfp.a
	EXPORTS scalbn
	IMPORTS .TOC. copysign
	DECLARES 
	USES 
}
Module s_scalbn.o {
	OBJECT += libfp.a::s_scalbn.o
}
ObjectFile libfp.a::e_sqrt.o {
	NAME Object file e_sqrt.o from archive libfp.a
	EXPORTS __ieee754_sqrt
	IMPORTS .TOC. getNan
	DECLARES 
	USES 
}
Module e_sqrt.o {
	OBJECT += libfp.a::e_sqrt.o
}
ObjectFile libfp.a::fioLib.o {
	NAME Object file fioLib.o from archive libfp.a
	EXPORTS fioLibInit voprintf fdprintf vprintf vfdprintf vsprintf vsnprintf fioRead fioRdString scanCharSet scanField fioScanV sscanf
	IMPORTS .TOC. printErr _func_printErr fioBufPrint fioFormatV fioBufPut fioSnBufPut read __ctype _func_altivecProbeRtn _func_fioFltScanRtn
	DECLARES 
	USES 
}
Module fioLib.o {
	OBJECT += libfp.a::fioLib.o
}
Library libfp.a {
	MODULES libfp.a::frexp.o libfp.a::ldexp.o libfp.a::modf.o libfp.a::acosh.o libfp.a::asincos.o libfp.a::asinh.o libfp.a::atan.o libfp.a::atan2.o libfp.a::atanh.o libfp.a::ceil.o libfp.a::cosh.o libfp.a::exp.o libfp.a::exp__E.o libfp.a::expm1.o libfp.a::floor.o libfp.a::fmod.o libfp.a::log.o libfp.a::log10.o libfp.a::log1p.o libfp.a::log__L.o libfp.a::pow.o libfp.a::sincos.o libfp.a::sinh.o libfp.a::sqrt.o libfp.a::support.o libfp.a::tan.o libfp.a::tanh.o libfp.a::fabs.o libfp.a::fpType.o libfp.a::cabs.o libfp.a::mprec.o libfp.a::dtoa.o libfp.a::bsd_cvt.o libfp.a::fioBaseLib.o libfp.a::floatLib.o libfp.a::floatFuncBind.o libfp.a::fioFuncBind.o libfp.a::e_fmod.o libfp.a::e_pow.o libfp.a::e_remainder.o libfp.a::s_rint.o libfp.a::s_scalbn.o libfp.a::e_sqrt.o libfp.a::fioLib.o
}
