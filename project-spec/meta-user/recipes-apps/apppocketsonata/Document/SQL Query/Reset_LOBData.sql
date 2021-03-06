/*
  LOBDATA 테이블의 레코드를 일정 개수(@SEQ_NUM) 이상일 때 최근 100일(@DAYDIFF) 전의 데이터만 백업한다.

  
*/

use ELINT;

declare @Record_Count INT
declare @SEQ_NUM INT
declare @DAYDIFF INT
declare @AETID INT

/* set @SEQ_NUM=1073741823  */
set @SEQ_NUM=10737823
set @DAYDIFF=100

print '+-----------------------------------------------------+'
print 'LOB 테이블을' + str(@DAYDIFF) + '일 초과한 것에 대해서는 정리하려 합니다.'

select @Record_Count=count(*) from LOBDATA;
select @AETID=max(AETID) from LOBDATA where DATEDIFF(DD,CONTACT_TIME,GETDATE()) <= @DAYDIFF

if( @Record_Count > @SEQ_NUM )
  begin
    print '최근 100일 전의 자료를 이동합니다.';
    
    /*   LOBDATA 테이블 백업하기    */
    if exists ( select * from INFORMATION_SCHEMA.tables where table_name='LOBDATA2')
      begin
        drop table LOBDATA2;
      end
    select * into LOBDATA2 from LOBDATA where 1=2;

    /* SEQ_NUM 의 타입은 INT 형이고 최대 2,147,483,647 까지이다. */
    insert into LOBDATA2 (OP_INIT_ID,LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MAX,DOA_MIN,DI_RATIO,
    FREQ_TYPE,FREQ_PATTERN_TYPE,FREQ_PATTERN_PERIOD,FREQ_MEAN,FREQ_MIN,FREQ_MAX,
    FREQ_POSITION_COUNT,PRI_TYPE,PRI_PATTERN_TYPE,PRI_PATTERN_PERIOD,PRI_MEAN,PRI_MIN,PRI_MAX,PRI_JITTER_RATIO,PRI_POSITION_COUNT,
    PW_MEAN,PW_MIN,PW_MAX,PA_MEAN,PA_MIN,PA_MAX,IS_STORED_PDW,NUM_PDW,
    COLLECTOR_ID,RADAR_LATITUDE,RADAR_LONGGITUDE,RADAR_NAME,RADARMODE_INDEX,THREAT_INDEX )
    select OP_INIT_ID,LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MAX,DOA_MIN,DI_RATIO,
    FREQ_TYPE,FREQ_PATTERN_TYPE,FREQ_PATTERN_PERIOD,FREQ_MEAN,FREQ_MIN,FREQ_MAX,
    FREQ_POSITION_COUNT,PRI_TYPE,PRI_PATTERN_TYPE,PRI_PATTERN_PERIOD,PRI_MEAN,PRI_MIN,PRI_MAX,PRI_JITTER_RATIO,PRI_POSITION_COUNT,
    PW_MEAN,PW_MIN,PW_MAX,PA_MEAN,PA_MIN,PA_MAX,IS_STORED_PDW,NUM_PDW,
    COLLECTOR_ID,RADAR_LATITUDE,RADAR_LONGGITUDE,RADAR_NAME,RADARMODE_INDEX,THREAT_INDEX  
     from LOBDATA where DATEDIFF(DD,CONTACT_TIME,GETDATE()) < @DAYDIFF
    
    drop table LOBDATA;
    exec sp_rename 'LOBDATA2' , 'LOBDATA'
    
    /*   LOB_POSITION 테이블 백업하기    */
    if exists ( select * from INFORMATION_SCHEMA.tables where table_name='LOB_POSITION2')
      begin    
        drop table LOB_POSITION2;
      end
    select * into LOB_POSITION2 from LOB_POSITION where 1=2;
    
    insert into LOB_POSITION2 (OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05,
    SEQ_06, SEQ_07,SEQ_08,SEQ_09,SEQ_10,SEQ_11,SEQ_12,SEQ_13,SEQ_14,SEQ_15,SEQ_16 )
    select OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, SEQ_01, SEQ_02, SEQ_03, SEQ_04, SEQ_05,
    SEQ_06, SEQ_07,SEQ_08,SEQ_09,SEQ_10,SEQ_11,SEQ_12,SEQ_13,SEQ_14,SEQ_15,SEQ_16 from LOB_POSITION where AETID >= @AETID;
     
    drop table LOB_POSITION;
    exec sp_rename 'LOB_POSITION2' , 'LOB_POSITION'     

  end
else
  begin
    print '데이터 개수(' + str(@Record_Count) + ')가 최대 상한값(' + str(@SEQ_NUM) + ')보다 적기 때문에 데이터 이동을 취소 합니다.';
	print ''
	
  end
