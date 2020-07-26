#
# This file is the apppocketsonata recipe.
#

SUMMARY = "Simple apppocketsonata application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://cmain.cpp \
		   file://cmain.h \
		   file://clog.cpp \
		   file://clog.h \
		   file://Thread/cprompt.cpp \
		   file://Thread/cprompt.h \		   
		   file://Thread/cjamtech.cpp \
		   file://Thread/cjamtech.h \	
		   file://Thread/cpulsetrk.cpp \		   
		   file://Thread/cpulsetrk.h \		   
		   file://Thread/csignalcollect.cpp \		   
		   file://Thread/csignalcollect.h \		   		   
		   file://Utils/cthread.cpp \
		   file://Utils/cthread.h \
		   file://Utils/cgpio.cpp \		   
		   file://Utils/cgpio.h \
		   file://mysocket.cpp \
		   file://mysocket.h \
		   file://Thread/creclan.cpp \
		   file://Thread/creclan.h \ 
		   file://Thread/curbit.cpp \
		   file://Thread/curbit.h \
		   file://MinIni/minIni.c \
		   file://MinIni/minIni.h \
		   file://MinIni/minGlue.h \
		   file://Include/_system.h \
		   file://Include/_sysmsg.h \
		   file://Include/_defines.h \
		   file://Include/_struct.h \
		   file://Include/_thrmsg.h \
           file://Makefile \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 apppocketsonata ${D}${bindir}
}
