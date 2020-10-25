#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"

echo "download.cgi 를 업데이트 합니다."
cp download_cgi ../download.cgi
cp download_cgi $cgi_bin/download.cgi
chmod 777 $cgi_bin/download.cgi

