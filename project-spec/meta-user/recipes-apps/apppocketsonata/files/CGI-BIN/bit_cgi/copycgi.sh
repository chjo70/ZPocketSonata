#!/bin/bash

# 웹 서버에 있는 CGI를 정의 한다.
cgi_bin="/var/www/html/Web/cgi-bin"
output_header="bit"
project_folder="${output_header}_cgi"

echo "bit.cgi 를 업데이트 합니다."
cp $project_folder ../../Web/cgi-bin/$output_header.cgi
sudo cp $project_folder $cgi_bin/$output_header.cgi
