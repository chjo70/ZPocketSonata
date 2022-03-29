# 2020-08-26 오후 3:22:26

# 에미터 관련 인덱스 테이블을 삭제합니다.
drop index if exists lob_index;
drop index if exists lob_position_index;
drop index if exists abt_index;
drop index if exists abt_position_index;
drop index if exists aet_index;

# 에미터 관련 인덱스 테이블을 생성합니다.
create index lob_index on lobdata (lobid);
create index lob_position_index on lob_position (lobid);
create index abt_index on abtdata (abtid);
create index abt_position_index on abt_position (abtid);
create index aet_index on aetdata (aetid);
