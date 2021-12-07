#
# This file is the apppocketsonata recipe.
#

SUMMARY = "Simple apppocketsonata application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI =	"file://cmain.cpp \
			file://cmain.h \
			file://stdafx.h \
			file://NetMem \
			file://Utils \
			file://Thread \
			file://SQLite \
			file://System \
			file://MinIni \
			file://Include \
			file://Anal \
			file://CGI-BIN/Qdecoder \
			file://CGI-BIN/bit_cgi/main.cpp \
			file://CGI-BIN/download_cgi/download_cgi.cpp \
			file://CGI-BIN/fetch_cgi/main.cpp \
			file://CGI-BIN/system_cgi/system_cgi.cpp \
			file://CGI-BIN/upload_cgi/main.cpp \
			file://CGI-BIN/listallchannel_cgi/main.cpp \
			file://Makefile \
			file://bootscript \
			file://.profile \
			file://Web \
			file://SQLite3.DB \
			file://sysconfig.ini \
			file://Test \
			"


S = "${WORKDIR}"
T = "${TMPDIR}"

RDEPENDS_${PN} += "readline boost-system"



inherit update-rc.d

INITSCRIPT_NAME = "bootscript"
INITSCRIPT_PARAMS = "start 99 S ."
INITSCRIPT_PACKAGES = "${PN}"




do_compile() {
	     oe_runmake TMPDIR=${T}
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 apppocketsonata ${D}${bindir}
	     install -m 0755 apptest ${D}${bindir}
		 
		 install -d ${D}/home/root
		 install -m 0644 ${S}/.profile ${D}/home/root/.profile
		 install -m 0644 ${S}/sysconfig.ini ${D}/home/root/sysconfig.ini
		 
		 install -d ${D}/var/log/LOG
		 install -m 0644 ${S}/sysconfig.ini ${D}/var/log/LOG/sysconfig.ini
		 install -m 0644 ${S}/sysconfig.ini ${D}/home/root/sysconfig.ini
		 
		 #install -d ${D}/home/root/SQLite3.DB
		 install -m 0644 ${S}/SQLite3.DB/emitter.sqlite3 ${D}/home/root/emitter.sqlite3
		 install -m 0644 ${S}/SQLite3.DB/cedeob.sqlite3 ${D}/home/root/cedeob.sqlite3
		 
		 install -d ${D}/srv/www
		 install -m 0644 ${S}/Web/web.tar.gz ${D}/srv/www/web.tar.gz
		 
		 install -d ${D}/srv/www/cgi-bin
		 install -m 0755 system.cgi ${D}/srv/www/cgi-bin/system.cgi
		 install -m 0755 fetch.cgi ${D}/srv/www/cgi-bin/fetch.cgi
		 install -m 0755 upload.cgi ${D}/srv/www/cgi-bin/upload.cgi
		 install -m 0755 download.cgi ${D}/srv/www/cgi-bin/download.cgi
		 install -m 0755 listallchannel.cgi ${D}/srv/www/cgi-bin/listallchannel.cgi
		 #install -m 0755 bit.cgi ${D}/srv/www/cgi-bin/bit.cgi
		 
		 #install -d ${D}/srv/www/cgi-bin
		 #install -d ${D}/srv/www/graphics
		 #install -m 0666 ${S}/Web/* ${D}/srv/www
		 #cp --preserve=mode,timestamps -R ${S}/Web ${D}/srv/www
		 #install -m 0755 ${S}/Web/* ${D}/srv/www
		 #chmod 0666 -R ${S}/Web ${D}/srv/www
		 #tar xvf ${S}/Web/web.tar.gz -C ${D}/srv/www
		 
		 install -d ${D}${sysconfdir}/init.d
		 install -m 0755 ${S}/bootscript ${D}${sysconfdir}/init.d/bootscript
		 
}

FILES_${PN} += "srv/www/*"
FILES_${PN} += "home/*"
FILES_${PN} += "${sysconfdir}/*"


