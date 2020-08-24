set timing on

drop index IDX_E_MSG_IQ_DATA;
drop index IDX_E_MSG_IQ_DATA2;

create index IDX_E_MSG_IQ_DATA on E_MSG_IQ_DATA( TASK_ID, SEARCH_BAND_ID, LOB_ID, CREATE_TIME );
create index IDX_E_MSG_IQ_DATA2 on E_MSG_IQ_DATA(FILE_NAME);
