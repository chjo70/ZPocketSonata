

==================================================
1. 설치 절차

1.1 u-boot 설정

1.1.1 ipaddress 설정

EWSP# print ipaddr
ipaddr=192.168.10.30

1.1.2 연결 확인
	컴에서 네크워크로 ping 테스트를 시험한다.
	
1.1.3 serverip 확인

EWSP# print serverip
serverip=192.168.10.245


1.1.3 bootcmd 확인

EWSP# print bootcmd
bootcmd=run tftpUvX; run tftpDTB; run uVxBoot

1.1.3.1 tftpUvX 학인

uVxWorks 파일 경로는 PC에서 tftp 데몬의 기본 파일 경로가 설정해야 됨.

EWSP# print tftpUvX
tftpUvX=tftp 0x2000000 uVxWorks


1.1.3.2 tftpDTB 학인

uVxWorks 파일 경로는 PC에서 tftp 데몬의 기본 파일 경로가 설정해야 됨.

EWSP# print tftpDTB
tftpDTB=tftp 0xf000000 t2080vpx3u.dtb

1.1.4 재실행한다.
