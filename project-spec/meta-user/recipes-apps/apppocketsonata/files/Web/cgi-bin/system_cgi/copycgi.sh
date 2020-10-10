#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"

echo "system.cgi 를 업데이트 합니다."
cp system_cgi ../system.cgi
cp system_cgi $cgi_bin/system.cgi
