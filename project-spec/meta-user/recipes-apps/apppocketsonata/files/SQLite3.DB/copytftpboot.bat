@echo off


copy ..\sysconfig.ini d:\tftpboot\INI\sysconfig.ini
copy cedeob_blank.sqlite3 d:\tftpboot\Lib\cedeob.sqlite3
copy emitter_blank.sqlite3 d:\tftpboot\Lib\emitter_blank.sqlite3

cd d:\tftpboot
d:
mv tftpboot.tar tftpboot.tar.bak
tar -cvf tftpboot.tar ./LIB/* ./INI/* ./Web/*

