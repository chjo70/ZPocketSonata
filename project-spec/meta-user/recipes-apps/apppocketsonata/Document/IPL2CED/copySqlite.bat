echo off

echo off

cls
color 17

set DEST_FOLDER=\\10.29.34.127\�������α�\01.��������\�����ȼ�(������ȹ��, �ҿ����м� ����)\�� 20220805_��������º�_RED\2��


: ��� ���� ����
copy "cedeob.sqlite3" "..\..\files\SQLite3.DB\cedeob_blank.sqlite3" 
copy "cedeob.sqlite3" "..\..\files\SQLite3.DB\cedeob.sqlite3" 
copy "cedeob.sqlite3" "d:\rawdata\cedeob.sqlite3"
copy "cedeob.sqlite3" "d:\rawdata_sim\cedeob.sqlite3"
rem copy ".\1.6 ��ȣ��뼺\%FILE_NAME6%.pptx" "%DEST_FOLDER_2%\%FILE_NAME6%.pptx" 


rem timeout 5

rem pause

