#!/bin/bash

echo "에미터 테이블을 생성합니다.===================================="
sqlite3 emitter.sqlite3 ".read emitter.sql"

echo "생성한 DB 를 복사합니다..."
cp emitter.sqlite3 ../../files/SQLite3.DB/.
cp emitter.sqlite3 ~/SQLite3.DB/.

echo ""
echo "CED/EOB 테이블을 생성합니다.===================================="
echo "CED 관련 테이블을 생성합니다..."
sqlite3 cedeob.sqlite3 ".read ced.sql"

echo "EOB 관련 테이블을 생성합니다..."
sqlite3 cedeob.sqlite3 ".read eob.sql"

echo "EOB 관련 코드를 생성합니다..."
sqlite3 cedeob.sqlite3 ".read eob_code.sql"

echo "CED/EOB VIEW 테이블을 생성합니다..."
sqlite3 cedeob.sqlite3 ".read view.sql"

cp cedeob.sqlite3 ../../files/SQLite3.DB/.
cp cedeob.sqlite3 ~/SQLite3.DB/.

echo ""
echo "성공적으로 PocketSonata 관련 테이블을 생성했습니다."
echo ""