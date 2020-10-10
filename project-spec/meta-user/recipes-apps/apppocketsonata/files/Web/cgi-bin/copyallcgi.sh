#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"

# 모든 CGI 들을 문자열에 등록한다. 
system_cgi="system_cgi/system_cgi"

# 1. system.cgi
echo "system.cgi 를 업데이트 합니다."
cp $system_cgi system.cgi
cp $system_cgi $cgi_bin/system.cgi