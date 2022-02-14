#
# 자체개발 RWR-SBC 보드의 플레쉬를 포멧하고 시스템 파일을 복사해 주는 스크립트 입니다.
#	by 2009년 8월, 조철희 (chjo70@hotmail.com)
# 사용방법: vxworks 셸에서 "<configTffs0.cmd" 를 입력한다.

# 플레쉬 메모리를 포맷합니다.
sysTffsFormat()

usrTffsConfig( 0, 0, "/tffs0" );

# 플레쉬 메모리에 설치파일을 복사합니다. 약 1분 정도 소요돱니다. 전원을 중간에 절대 끊지 마세요.
copy "host:install.tar","/tffs0/install.tar"

#압축을 풉니다.
untar( "/tffs0/install.tar", "/tffs0" );

#설치 파일을 삭제합니다.
unlink( "/tffs0/install.tar" );

# 나머지 추가할 파일은 알FTP 또는 ftpSync 툴을 이용해서 복사할 수 있습니다.

# 완료했습니다.

