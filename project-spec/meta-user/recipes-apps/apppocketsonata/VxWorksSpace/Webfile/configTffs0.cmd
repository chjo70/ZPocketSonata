#
# ��ü���� RWR-SBC ������ �÷����� �����ϰ� �ý��� ������ ������ �ִ� ��ũ��Ʈ �Դϴ�.
#	by 2009�� 8��, ��ö�� (chjo70@hotmail.com)
# �����: vxworks �п��� "<configTffs0.cmd" �� �Է��Ѵ�.

# �÷��� �޸𸮸� �����մϴ�.
sysTffsFormat()

usrTffsConfig( 0, 0, "/tffs0" );

# �÷��� �޸𸮿� ��ġ������ �����մϴ�. �� 1�� ���� �ҿ䉴�ϴ�. ������ �߰��� ���� ���� ������.
copy "host:install.tar","/tffs0/install.tar"

#������ Ǳ�ϴ�.
untar( "/tffs0/install.tar", "/tffs0" );

#��ġ ������ �����մϴ�.
unlink( "/tffs0/install.tar" );

# ������ �߰��� ������ ��FTP �Ǵ� ftpSync ���� �̿��ؼ� ������ �� �ֽ��ϴ�.

# �Ϸ��߽��ϴ�.

