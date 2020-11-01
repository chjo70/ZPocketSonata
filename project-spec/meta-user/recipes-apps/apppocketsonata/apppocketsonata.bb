#
# This file is the apppocketsonata recipe.
#

SUMMARY = "Simple apppocketsonata application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI =	"file://cmain.cpp \
			file://cmain.h \
			file://Collect/DataFile \
			file://Collect/ccollectbank \
			file://NetMem \
			file://Utils \
			file://Thread \
			file://SQLite \
			file://System \
			file://MinIni \
			file://Include \
			file://Anal \
			file://Makefile \
			file://bootscript \
			file://.profile \
			file://Web \
			file://SQLite3.DB \
			file://sysconfig.ini \
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
		 
		 install -d ${D}/home/root
		 install -m 0644 ${S}/.profile ${D}/home/root/.profile
		 
		 install -d ${D}/home/root/SQLite3.DB
		 install -m 0644 ${S}/SQLite3.DB/emitter.sqlite3 ${D}/home/root/SQLite3.DB/emitter.sqlite3
		 install -m 0644 ${S}/SQLite3.DB/cedeob.sqlite3 ${D}/home/root/SQLite3.DB/cedeob.sqlite3
		 
		 install -d ${D}/srv/www
		 install -m 0644 ${S}/Web/web.tar.gz ${D}/srv/www/web.tar.gz
		 
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

