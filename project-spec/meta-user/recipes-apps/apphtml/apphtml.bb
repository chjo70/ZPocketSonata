#
# This file is the apphtml recipe.
#

SUMMARY = "Simple apphtml application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://index.html \
	   file://bashrc \
		  "

S = "${WORKDIR}"

#do_compile() {
#	     oe_runmake
#}

do_install() {
		 install -d ${D}/home/root
		 install -m 0666 ${S}/bashrc ${D}/home/root/.bashrc
		 
		 install -d ${D}/srv/www
		 install -m 0666 ${S}/index.html ${D}/srv/www/index.html
}

FILES_${PN} += "home/*"
FILES_${PN} += "srv/www/*"