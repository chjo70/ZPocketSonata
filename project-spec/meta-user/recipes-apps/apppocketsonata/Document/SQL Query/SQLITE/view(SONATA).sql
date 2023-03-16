/* 2020-08-26 오후 3:22:26			*/

/* VIEW 관련 테이블을 삭제합니다.	*/
drop view if exists VEL_RADAR_LIST;
drop view if exists VEL_RADAR_RF_SEQENCE;
drop view if exists VEL_RADAR_PRI_SEQENCE;
drop view if exists VEL_RADARMODE_LIST;

/* VIEW 관련 테이블을 생성합니다.			*/

/* VEL_RADARMODE_LIST 를 생성 합니다. */
CREATE VIEW VEL_RADARMODE_LIST (
           RM_RADAR_MODE_INDEX,
           RM_FUNCTION_CODE,

           RM_SIGNAL_TYPE,
           RM_POLARIZATION,
           RM_PLATFORM,
           RM_VALIDATION,

           RM_RF_TYPE,
           RM_RF_TYPICAL_MIN,
           RM_RF_TYPICAL_MAX,
           RM_RF_PATTERN,
           RM_RF_NUM_ELEMENTS,
           RM_RF_NUM_POSITIONS,
           RM_RF_PATTERN_PERIOD_MIN,
           RM_RF_PATTERN_PERIOD_MAX,
           RM_RF_MEAN_MIN,
           RM_RF_MEAN_MAX,

           RM_PRI_TYPE,
           RM_PRI_TYPICAL_MIN,
           RM_PRI_TYPICAL_MAX,
           RM_PRI_PATTERN,
           RM_PRI_NUM_ELEMENTS,
           RM_PRI_NUM_POSITIONS,
           RM_PRI_PATTERN_PERIOD_MIN,
           RM_PRI_PATTERN_PERIOD_MAX,
           RM_PRI_MEAN_MIN,
           RM_PRI_MEAN_MAX,

           RM_PD_TYPICAL_MIN,
           RM_PD_TYPICAL_MAX,

           RM_SCAN_PRIMARY_TYPE,
           RM_SCAN_PRIMARY_TYPICAL_MIN,
           RM_SCAN_PRIMARY_TYPICAL_MAX,
           RM_SCAN_SECONDARY_TYPE,
           RM_SCAN_SECONDARY_TYPICAL_MIN,
           RM_SCAN_SECONDARY_TYPICAL_MAX,

           RM_MODULATION_CODE,
           RM_PRIORITY,

           RML_RADAR_INDEX,
           RML_RADAR_MODE_NAME,
           RML_MODE_CODE,

           R_PRIORITY,
           R_ELNOT,
           R_NICKNAME,
           R_TIME_INACTIVATED,

           D_THREAT_INDEX,
           D_DEVICE_INDEX,
           D_ELNOT ) AS

    SELECT RADAR_MODE.RADAR_MODE_INDEX,
           RADAR_MODE.FUNCTION_CODE,

           RADAR_MODE.SIGNAL_TYPE,
           RADAR_MODE.POLARIZATION,
           RADAR_MODE.PLATFORM,
           RADAR_MODE.VALIDATION,

           RADAR_MODE.RF_TYPE,
           RADAR_MODE.RF_TYPICAL_MIN,
           RADAR_MODE.RF_TYPICAL_MAX,
           RADAR_MODE.RF_PATTERN,
           RADAR_MODE.RF_NUM_ELEMENTS,
           RADAR_MODE.RF_NUM_POSITIONS,
           RADAR_MODE.RF_PATTERN_PERIOD_MIN,
           RADAR_MODE.RF_PATTERN_PERIOD_MAX,
           RADAR_MODE.RF_MEAN_MIN,
           RADAR_MODE.RF_MEAN_MAX,

           RADAR_MODE.PRI_TYPE,
           RADAR_MODE.PRI_TYPICAL_MIN,
           RADAR_MODE.PRI_TYPICAL_MAX,
           RADAR_MODE.PRI_PATTERN,
           RADAR_MODE.PRI_NUM_ELEMENTS,
           RADAR_MODE.PRI_NUM_POSITIONS,
           RADAR_MODE.PRI_PATTERN_PERIOD_MIN,
           RADAR_MODE.PRI_PATTERN_PERIOD_MAX,
           RADAR_MODE.PRI_MEAN_MIN,
           RADAR_MODE.PRI_MEAN_MAX,

           RADAR_MODE.PD_TYPICAL_MIN,
           RADAR_MODE.PD_TYPICAL_MAX,

           RADAR_MODE.SCAN_PRIMARY_TYPE,
           RADAR_MODE.SCAN_PRIMARY_TYPICAL_MIN,
           RADAR_MODE.SCAN_PRIMARY_TYPICAL_MAX,
           RADAR_MODE.SCAN_SECONDARY_TYPE,
           RADAR_MODE.SCAN_SECONDARY_TYPICAL_MIN,
           RADAR_MODE.SCAN_SECONDARY_TYPICAL_MAX,

           RADAR_MODE.MODULATION_CODE,
           RADAR_MODE.PRIORITY,

           RADAR_MODE_LIFECYCLE.RADAR_INDEX,
           RADAR_MODE_LIFECYCLE.RADAR_MODE_NAME,
           RADAR_MODE_LIFECYCLE.MODE_CODE,

           RADAR.PRIORITY,
           RADAR.ELNOT,
           RADAR.NICKNAME,
           RADAR.TIME_INACTIVATED,

           DEVICE.THREAT_INDEX,
           DEVICE.DEVICE_INDEX,
           DEVICE.ELNOT


    FROM RADAR_MODE
    INNER JOIN RADAR_MODE_LIFECYCLE ON RADAR_MODE.RADAR_MODE_INDEX = RADAR_MODE_LIFECYCLE.RADAR_MODE_INDEX
    INNER JOIN RADAR ON RADAR.RADAR_INDEX = RADAR_MODE_LIFECYCLE.RADAR_INDEX
    LEFT OUTER JOIN DEVICE ON RADAR.ELNOT = DEVICE.ELNOT

    WHERE RADAR.STATUS = 'ACTIVE'  AND RADAR_MODE.VALIDATION = '1'

/* VEL_RADAR_LIST 를 생성 합니다. */
CREATE VIEW VEL_RADAR_LIST AS
    SELECT A.ELNOT,
          A.NICKNAME,
          A.FUNCTION_CODE,
          A.PRIORITY,
          A.STATUS,

          B.RF_TYPICAL_MIN,
          B.RF_TYPICAL_MAX,
          B.PRI_TYPICAL_MIN,
          B.PRI_TYPICAL_MAX,
          E.WEAPON_SYS,
          G.PLATFORM,
          A.RADAR_INDEX

    FROM RADAR AS A, RADAR_MODE AS B, RADAR_MODE_LIFECYCLE AS C, ASSOC_WEAP_SYS AS D, WEAPON_SYSTEM AS E, ASSOC_PLATFORM AS F, PLATFORM AS G
    WHERE     A.RADAR_INDEX = C.RADAR_INDEX
          AND C.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX
          AND A.RADAR_INDEX = D.RADAR_INDEX
          AND D.WEAPON_INDEX = E.WEAPON_INDEX
          AND A.RADAR_INDEX = F.RADAR_INDEX
          AND F.PLATFORM_INDEX = G.PLATFORM_INDEX;



/* VEL_RADAR_RF_SEQENCE 를 생성 합니다. */
CREATE VIEW VEL_RADAR_RF_SEQENCE AS
    SELECT 	A.RADAR_MODE_INDEX,
            A.RF_SEQ_ID,
            A.RF_INDEX,

            B.RF_MIN,
            B.RF_MAX

    FROM RADAR_RF_SEQUENCE AS A, RADAR_RF_VALUES AS B
    WHERE 		A.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX
            AND A.RF_INDEX = B.RF_INDEX;

/* VEL_RADAR_PRI_SEQENCE 를 생성 합니다. */
CREATE VIEW VEL_RADAR_PRI_SEQENCE AS
    SELECT 	A.RADAR_MODE_INDEX,
            A.PRI_SEQ_ID,
            A.PRI_INDEX,

            B.PRI_MIN,
            B.PRI_MAX

    FROM RADAR_PRI_SEQUENCE AS A, RADAR_PRI_VALUES AS B
    WHERE 		A.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX
            AND A.PRI_INDEX = B.PRI_INDEX


