# 2020-08-26 오후 3:22:26

# VIEW 관련 테이블을 삭제합니다.
drop view if exists "VEL_RADAR_LIST";
drop view if exists "VEL_RADAR_RF_SEQENCE";
drop view if exists "VEL_RADAR_PRI_SEQENCE";

# VIEW 관련 테이블을 생성합니다.
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
          AND F.PLATFORM_INDEX = G.PLATFORM_INDEX

# =========================================================================
CREATE VIEW VEL_RADAR_RF_SEQENCE AS
    SELECT 	A.RADAR_MODE_INDEX,
            A.RF_SEQ_ID,
            A.RF_INDEX,

            B.RF_MIN,
            B.RF_MAX

    FROM RADAR_RF_SEQUENCE AS A, RADAR_RF_VALUES AS B
    WHERE 		A.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX
            AND A.RF_INDEX = B.RF_INDEX

# =========================================================================
CREATE VIEW VEL_RADAR_PRI_SEQENCE AS
    SELECT 	A.RADAR_MODE_INDEX,
            A.RF_SEQ_ID,
            A.RF_INDEX,

            B.RF_MIN,
            B.RF_MAX

    FROM RADAR_RF_SEQUENCE AS A, RADAR_RF_VALUES AS B
    WHERE 		A.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX
            AND A.RF_INDEX = B.RF_INDEX


