#
# This file is the apppocketsonata recipe.
#

SUMMARY = "Simple apppocketsonata application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://cmain.cpp \
		   file://cmain.h \
		   file://Collect/ccollectbank/ccollectbank.cpp \
		   file://Collect/ccollectbank/ccollectbank.h \
		   file://NetMem/client/ClientMemoryPage.cpp \
		   file://NetMem/client/ClientMemoryPage.h \		   
           file://NetMem/client/NetworkMemory.cpp \
		   file://NetMem/client/NetworkMemory.h \
           file://NetMem/server/ClientSocket.cpp \
		   file://NetMem/server/ClientSocket.h \
           file://NetMem/server/MemoryPage.cpp \
		   file://NetMem/server/MemoryPage.h \
           file://NetMem/server/ServerSocket.cpp \
		   file://NetMem/server/ServerSocket.h \
           file://NetMem/utils/ApiNetMem.cpp \
		   file://NetMem/utils/ApiNetMem.h \
		   file://NetMem/utils/PortableSocket.h \
		   file://Utils/cthread.cpp \
		   file://Utils/cthread.h \
		   file://Utils/cgpio.cpp \		   
		   file://Utils/cgpio.h \
		   file://Utils/clog.cpp \
		   file://Utils/clog.h \		   
		   file://Utils/csingleserver.cpp \
		   file://Utils/csingleserver.h \
		   file://Utils/cmultiserver.cpp \
		   file://Utils/cmultiserver.h \		   
		   file://Utils/ccommonutils.cpp \
		   file://Utils/ccommonutils.h \		   
		   file://Utils/cqueue.h \		   		   
		   file://Thread/cdetectanalysis.cpp \
		   file://Thread/cdetectanalysis.h \
		   file://Thread/ctrackanalysis.cpp \
		   file://Thread/ctrackanalysis.h \
		   file://Thread/cscananalysis.cpp \
		   file://Thread/cscananalysis.h \
		   file://Thread/cprompt.cpp \
		   file://Thread/cprompt.h \
		   file://Thread/cpulsetrk.cpp \
		   file://Thread/cpulsetrk.h \
		   file://Thread/creclan.cpp \
		   file://Thread/creclan.h \ 
		   file://Thread/cjamtech.cpp \
		   file://Thread/cjamtech.h \		   
		   file://Thread/csignalcollect.cpp \		   
		   file://Thread/csignalcollect.h \		   		   		   
		   file://Thread/ctaskmngr.cpp \
		   file://Thread/ctaskmngr.h \		   
		   file://Thread/curbit.cpp \
		   file://Thread/curbit.h \
		   file://System/csysconfig.cpp \
		   file://System/csysconfig.h \
		   file://MinIni/minIni.cpp \
		   file://MinIni/minIni.h \
		   file://MinIni/minGlue.h \
		   file://Include/system.h \
		   file://Include/sysmsg.h \
		   file://Include/defines.h \
		   file://Include/struct.h \
		   file://Include/thrmsg.h \
		   file://Include/global.h \
		   file://Include/SONATAPIP/_sysmsg.h \
           file://Makefile \
		   file://.profile \
		   file://Web/web.tar.gz;unpack=0 \
		   "

S = "${WORKDIR}"
T = "${TMPDIR}"

do_compile() {
	     oe_runmake TMPDIR=${T}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 apppocketsonata ${D}${bindir}
		 
		 install -d ${D}/home/root
		 install -m 0644 ${S}/.profile ${D}/home/root/.profile
		 
		 install -d ${D}/srv/www
		 #install -d ${D}/srv/www/cgi-bin
		 #install -d ${D}/srv/www/graphics
		 #install -m 0666 ${S}/Web/* ${D}/srv/www
		 #cp --preserve=mode,timestamps -R ${S}/Web ${D}/srv/www
		 #install -m 0755 ${S}/Web/* ${D}/srv/www
		 #chmod 0666 -R ${S}/Web ${D}/srv/www
		 install -m 0666 ${S}/Web/web.tar.gz ${D}/srv/www/web.tar.gz
		 #tar xvf ${S}/Web/web.tar.gz -C ${D}/srv/www
}

#do_unpack() {
#		 tar xvf ${D}/srv/www/web.tar.gz -C ${D}/srv/www		
#}

FILES_${PN} += "srv/www/*"
FILES_${PN} += "home/*"

