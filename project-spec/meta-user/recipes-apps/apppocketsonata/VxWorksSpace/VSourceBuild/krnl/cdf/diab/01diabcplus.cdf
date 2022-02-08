/*
   Copyright (c) 2001-2002, 2007, 2010, 2016-2017 Wind River Systems, Inc.

   The right to copy, distribute, modify or otherwise make use of this software
   may be licensed only pursuant to the terms of an applicable Wind River
   license agreement.

modification history
--------------------
13apr17,jla  Enhance synopsis clarity. (F8862)
19apr16,lau  removed strtoll and strtoull from INCLUDE_CPLUS_IOSTREAMS (V7COR-2551)
05aug10,sn   Diab switching to C++ IA64 ABI
21aug07,gvm  WIND00100489 - _x_diab_xgetptimes.o and _x_diab_nomemory.o
                 are no longer part of the archive
20mar02,sn   SPR 74555 - removed empty components
13mar02,sn   SPR 73984, 73342 - added MODULES info
06nov01,sn   wrote

DESCRIPTION

This file contains descriptions for the Diab toolchain specific C++
compiler support and standard library components.
*/

Component INCLUDE_CPLUS_LANG {
	CONFIGLETTES	cplusdiabLang.c
        MODULES         _x_diab_array_del.o \
                        _x_diab_array_new.o \
                        _x_diab_array_nodel.o \
                        _x_diab_array_nonew.o \
                        _x_diab_array_pdel.o \
                        _x_diab_cppalloc.o \
                        _x_diab_cxa_eh.o \
                        _x_diab_cxa_except_tab.o \
                        _x_diab_delete.o \
                        _x_diab_delnothrow.o \
                        _x_diab_error.o \
                        _x_diab_frameadd.o \
                        _x_diab_framedb.o \
                        _x_diab_frameinfo.o \
                        _x_diab_guard.o \
                        _x_diab_newhandler.o \
                        _x_diab_newnothrow.o \
                        _x_diab_new.o \
                        _x_diab_nothrow.o \
                        _x_diab_placedel.o \
			_x_diab_pure_virt.o \
                        _x_diab_rtti.o \
                        _x_diab_set_new.o \
                        _x_diab_setterm.o \
                        _x_diab_setunexp.o \
                        _x_diab_terminate.o \
                        _x_diab_typeinfo.o \
                        _x_diab_unexpected.o \
                        _x_diab_unwind_fi.o \
                        _x_diab_vec_newdel.o
}

Component INCLUDE_CPLUS_IOSTREAMS {
	NAME		Standard library facilities
	SYNOPSIS	This component includes C++ standard library support \
                        in your VxWorks project.
	REQUIRES        INCLUDE_CPLUS
	CONFIGLETTES    cplusdiabIos.c
	MODULES         _x_diab_fiopen.o \
			_x_diab_iomanip.o \
			_x_diab_ios.o \
			_x_diab_iostream.o \
			_x_diab_limits.o \
			_x_diab_locale0.o \
			_x_diab_locale.o \
			_x_diab_string.o \
         		_x_diab_strstrea.o \
         		_x_diab_throw.o \
         		_x_diab_wcslen.o \
         		_x_diab_wiostrea.o \
         		_x_diab_wlocale.o \
         		_x_diab_wmemchr.o \
         		_x_diab_wmemcmp.o \
         		_x_diab_wmemcpy.o \
         		_x_diab_wmemmove.o \
         		_x_diab_wmemset.o \
         		_x_diab_xfvalues.o \
         		_x_diab_xgetglob.o \
         		_x_diab_xlocale.o \
         		_x_diab_xlvalues.o \
         		_x_diab_xstart.o \
         		_x_diab_xsyslock.o \
         		_x_diab_xvalues.o

}
