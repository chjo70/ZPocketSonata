

==================================================
1. ��ġ ����

1.1 u-boot ����

1.1.1 ipaddress ����

EWSP# print ipaddr
ipaddr=192.168.10.30

1.1.2 ���� Ȯ��
	�Ŀ��� ��ũ��ũ�� ping �׽�Ʈ�� �����Ѵ�.
	
1.1.3 serverip Ȯ��

EWSP# print serverip
serverip=192.168.10.245


1.1.3 bootcmd Ȯ��

EWSP# print bootcmd
bootcmd=run tftpUvX; run tftpDTB; run uVxBoot

1.1.3.1 tftpUvX ����

uVxWorks ���� ��δ� PC���� tftp ������ �⺻ ���� ��ΰ� �����ؾ� ��.

EWSP# print tftpUvX
tftpUvX=tftp 0x2000000 uVxWorks


1.1.3.2 tftpDTB ����

uVxWorks ���� ��δ� PC���� tftp ������ �⺻ ���� ��ΰ� �����ؾ� ��.

EWSP# print tftpDTB
tftpDTB=tftp 0xf000000 t2080vpx3u.dtb

1.1.4 ������Ѵ�.
