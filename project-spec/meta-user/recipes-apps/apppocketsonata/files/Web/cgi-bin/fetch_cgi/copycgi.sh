#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"

echo "upload.cgi 를 업데이트 합니다."
cp fetch_cgi ../fetch.cgi
cp fetch_cgi $cgi_bin/fetch.cgi
chmod 777 $cgi_bin/fetch.cgi
