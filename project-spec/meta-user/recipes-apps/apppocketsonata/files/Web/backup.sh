#!/bin/bash

backup_directory="/home/chjo70/Lab/Xilinx/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/files/Web"

web_directory="/var/www/html/Web"

present_directory=`pwd`
if [[ "$present_directory" =~ "smb-share" ]] ; then
	echo ""
	echo "1단계: 모든 데이터 파일을 " [$present_directory] "폴더에 압축 합니다."
	rm -f web.tar.gz
	tar zcf web.tar.gz --exclude zcu111 --exclude _we_info5 --exclude *.bak --exclude comp* *

	echo ""
	echo "2단계: 압축된 파일을" [$backup_directory] "에 풀어서 백업 합니다." 
	cp web.tar.gz $backup_directory
	tar xf web.tar.gz -C $backup_directory
	chmod 755 -R $backup_directory/*

	echo ""
	echo "3단계: 압축된 파일을"  [$web_directory] " 웹 서버에 올립니다." 
	sudo mkdir -p $web_directory
	#sudo chmod 777 $web_directory
	sudo cp $backup_directory/web.tar.gz $web_directory
	sudo tar xf $web_directory/web.tar.gz -C $web_directory
	sudo chmod 777 -R $web_directory

	echo ""
	echo "모든 데이터 파일을 복사 완료 했습니다.============================="
	
elif [[ "$present_directory" =~ "Web" ]] ; then
	echo ""
	echo "1단계: 모든 데이터 파일을 " [$present_directory] "폴더에 압축 합니다."
	rm -f web.tar.gz
	tar zcf web.tar.gz --exclude zcu111 --exclude _we_info5 --exclude *.bak --exclude comp* *	
	
	echo ""
	echo "2단계: 압축된 파일을"  [$web_directory] " 웹 서버에 올립니다." 
	sudo mkdir -p $web_directory	
	sudo cp $backup_directory/web.tar.gz $web_directory
	sudo tar xf $web_directory/web.tar.gz -C $web_directory
	sudo chmod 777 -R $web_directory		
	
	echo ""
	echo ""
else
	echo "[주의] 이 작업은 호스트컴을 공유한 폴더를 리눅스 서버에서 SMB로 연결하여 실행 파일을 실행해야 합니다."

fi


