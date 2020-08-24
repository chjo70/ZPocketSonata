set timing on

drop index IDX_E_MSG_IF_DATA;
drop index IDX_E_MSG_IF_DATA2;

/* create index IDX_E_MSG_IF_DATA on E_MSG_IF_DATA( TASK_ID, SEARCH_BAND_ID, LOB_ID, CREATE_TIME );  */
create index IDX_E_MSG_IF_DATA2 on E_MSG_IF_DATA(FILE_NAME);
