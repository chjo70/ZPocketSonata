#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"

echo "upload.cgi 를 업데이트 합니다."
cp upload_cgi ../upload.cgi
cp upload_cgi $cgi_bin/upload.cgi
chmod 777 $cgi_bin/upload.cgi

