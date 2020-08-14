#
# This file is the apppocketsonata recipe.
#

SUMMARY = "Simple apppocketsonata application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI =	"file://cmain.cpp \
			file://cmain.h \
			file://Collect/DataFile/CRWRCommonVariables.h \
			file://Collect/DataFile/DataFile.cpp \
			file://Collect/DataFile/DataFile.h \
			file://Collect/DataFile/_iq.h \
			file://Collect/DataFile/_macro.h \
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
			file://Utils/cfile.cpp \
			file://Utils/cfile.h \
			file://Utils/carraymsgdata.cpp \
			file://Utils/carraymsgdata.h \
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
			file://Thread/cemittermerge.cpp \
			file://Thread/cemittermerge.h \
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
			file://Anal/OFP_Main.h \
			file://Anal/EmitterMerge/DistanceLeastSquare/DistanceLeastSquare.h \
			file://Anal/EmitterMerge/ELEmitterDataType.h \
			file://Anal/EmitterMerge/ELEnvironVariableMngr.h \
			file://Anal/EmitterMerge/ELGMIMsgDefn.h \
			file://Anal/EmitterMerge/ELMsgDefn.h \	
			file://Anal/EmitterMerge/ELOperationCtrlDataType.h \
			file://Anal/EmitterMerge/ELPosEstDataType.h \
			file://Anal/EmitterMerge/ELThreat.h \	
			file://Anal/EmitterMerge/ElintRsltDataTypedb.h \
			file://Anal/EmitterMerge/ElintTaskDataTypedb.h \
			file://Anal/EmitterMerge/GeoCoordConv.h \
			file://Anal/EmitterMerge/LinearLS/LinearLS.h \
			file://Anal/EmitterMerge/Matrix/Matrix.h \
			file://Anal/EmitterMerge/NonlinearLS/NonLinearLS.h \
			file://Anal/EmitterMerge/PositionEstimationAlg.h \			
			file://Anal/EmitterMerge/PositionEstimation.h \	
			file://Anal/EmitterMerge/Quadratic/Quadratic.h \
			file://Anal/EmitterMerge/Stack.h \
			file://Anal/INC/AetIPL.h \ 
			file://Anal/INC/ErrorMsg.h \ 
			file://Anal/INC/Globals.h \ 
			file://Anal/INC/Macros.h \ 
			file://Anal/INC/OS.h \ 
			file://Anal/INC/PDW.h \ 
			file://Anal/INC/Stack.h \ 
			file://Anal/INC/TaskMsg.h \ 
			file://Anal/INC/defines.h \ 
			file://Anal/INC/structs.h \ 
			file://Anal/INC/system.h \ 
			file://Anal/Identify/ELCEDLibDataType.h \
			file://Anal/Identify/ELCEDLibDataType2.h \
			file://Anal/Identify/ELCEDLibMngr2.h \
			file://Anal/Identify/ELUtil.h \
			file://Anal/Identify/Identify.h \
			file://Anal/Identify/define.h \
			file://Anal/Identify/structs.h \
			file://Anal/NewSigAnal/NAnalPRI.cpp \ 
			file://Anal/NewSigAnal/NAnalPRI.h \ 
			file://Anal/NewSigAnal/NGroup.cpp \ 
			file://Anal/NewSigAnal/NGroup.h \ 
			file://Anal/NewSigAnal/NMakeAET.cpp \ 
			file://Anal/NewSigAnal/NMakeAET.h \ 
			file://Anal/NewSigAnal/NPulExt.h \ 
			file://Anal/NewSigAnal/NPulExt.cpp \ 
			file://Anal/NewSigAnal/NewSigAnal.h \ 
			file://Anal/NewSigAnal/NewSigAnal.cpp \ 
			file://Anal/ScanSigAnal/SAnalScan.h \ 
			file://Anal/ScanSigAnal/SDefine.h \ 
			file://Anal/ScanSigAnal/SGroup.h \ 
			file://Anal/ScanSigAnal/SPulExt.h \ 
			file://Anal/ScanSigAnal/SStruct.h \ 
			file://Anal/ScanSigAnal/ScanSigAnal.h \ 
			file://Anal/SigAnal/stdafx.cpp \ 			
			file://Anal/SigAnal/stdafx.h \ 
			file://Anal/SigAnal/Group.cpp \ 			
			file://Anal/SigAnal/Group.h \ 
			file://Anal/SigAnal/AnalPRI.cpp \ 
			file://Anal/SigAnal/AnalPRI.h \ 			
			file://Anal/SigAnal/MakeAET.h \ 
			file://Anal/SigAnal/PulExt.cpp \ 
			file://Anal/SigAnal/PulExt.h \ 
			file://Anal/SigAnal/MakeAET.cpp \ 
			file://Anal/SigAnal/MakeAET.h \ 
			file://Anal/SigAnal/SysPara.cpp \ 
			file://Anal/SigAnal/SysPara.h \ 
			file://Anal/SigAnal/_Define.h \ 
			file://Anal/SigAnal/_Macro.h \ 
			file://Anal/SigAnal/_SigAnal.h \ 
			file://Anal/SigAnal/_Struct.h \ 
			file://Anal/SigAnal/_Type.h \ 	
			file://Anal/Identify/ELUtil.h \ 	
			file://Include/SONATAPIP/_sysmsg.h \
			file://Makefile \
			file://bootscript \
			file://.profile \
			file://Web \
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

