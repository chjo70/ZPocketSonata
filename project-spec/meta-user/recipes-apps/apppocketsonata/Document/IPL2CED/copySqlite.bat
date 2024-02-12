echo off

echo off

cls
color 17

set DEST_FOLDER=\\10.29.34.127\소형무인기\01.제안진행\★제안서(장절계획서, 소요기술분석 포함)\★ 20220805_디자인출력본_RED\2권


: 대상 폴더 저장
copy "cedeob.sqlite3" "..\..\files\SQLite3.DB\cedeob_blank.sqlite3" 
copy "cedeob.sqlite3" "..\..\files\SQLite3.DB\cedeob.sqlite3" 
copy "cedeob.sqlite3" "d:\rawdata\cedeob.sqlite3"
copy "cedeob.sqlite3" "d:\rawdata_sim\cedeob.sqlite3"
rem copy ".\1.6 상호운용성\%FILE_NAME6%.pptx" "%DEST_FOLDER_2%\%FILE_NAME6%.pptx" 


rem timeout 5

rem pause

