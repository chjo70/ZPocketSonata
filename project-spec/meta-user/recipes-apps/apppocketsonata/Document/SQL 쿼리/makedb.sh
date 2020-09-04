#!/bin/bash

result=0

emitter_sqlite3="emitter.sqlite3"
cedeob_sqlite3="cedeob.sqlite3"

#

echo "에미터 테이블($emitter_sqlite3)을 생성합니다.===================================="
echo "LOB/ABT/AET 테이블을 생성합니다..."
sqlite3 $emitter_sqlite3 ".read emitter.sql"

echo "인덱스 테이블을 생성합니다.===================================="
sqlite3 $emitter_sqlite3 ".read emitter_index.sql"

echo "생성한 DB 를 복사합니다..."
cp $emitter_sqlite3 ../../files/SQLite3.DB/.
#cp $emitter_sqlite3 ~/SQLite3.DB/.

echo ""
echo "CED/EOB 테이블($cedeob_sqlite3)을 생성합니다.===================================="
echo "CED 관련 테이블을 생성합니다..."
sqlite3 $cedeob_sqlite3 ".read ced.sql"

echo "EOB 관련 테이블을 생성합니다..."
sqlite3 $cedeob_sqlite3 ".read eob.sql"

echo "EOB 관련 코드를 생성합니다..."
sqlite3 $cedeob_sqlite3 ".read eob_code.sql"

echo "CED/EOB VIEW 테이블을 생성합니다..."
sqlite3 $cedeob_sqlite3 ".read view.sql"

cp $cedeob_sqlite3 ../../files/SQLite3.DB/.
#cp $cedeob_sqlite3 ~/SQLite3.DB/.

echo ""
echo "성공적으로 PocketSonata 관련 테이블을 생성했습니다."
echo ""