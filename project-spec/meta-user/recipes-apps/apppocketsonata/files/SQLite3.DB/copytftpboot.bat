@echo off


pushd .


copy ..\sysconfig.ini d:\tftpboot\INI\sysconfig.ini /Y
copy cedeob.sqlite3 d:\tftpboot\Lib\cedeob.sqlite3 /Y
copy cedeob.sqlite3 d:\rawdata\cedeob.sqlite3 /Y
copy emitter_blank.sqlite3 d:\tftpboot\Lib\emitter_blank.sqlite3 /Y

cd d:\tftpboot
d:
mv tftpboot.tar tftpboot.tar.bak
tar -cvf tftpboot.tar ./LIB/* ./INI/* ./Web/* ./BIN/*

popd .

