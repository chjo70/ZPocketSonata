DROP VIEW EW701.VEL_RADAR_LIST_P;

CREATE OR REPLACE FORCE VIEW EW701.VEL_RADAR_LIST_P
(
   ELNOT,
   NICKNAME,
   FUNCTION_CODE,
   RADAR_PRIORITY,
   STATUS,
   
   RF_TYPICAL_MIN,
   RF_TYPICAL_MAX,
   PRI_TYPICAL_MIN,
   PRI_TYPICAL_MAX,
   WEAPON_SYS,
   PLATFORM,
   RADAR_INDEX,
   
   DEVICE_INDEX
)
AS
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
          A.RADAR_INDEX,
          H.DEVICE_INDEX
          
          
     FROM RADAR_P A,
          RADAR_MODE_P B,
          RADAR_MODE_LIFECYCLE_P C,
          ASSOC_WEAP_SYS_P D,
          WEAPON_SYSTEM_P E,
          ASSOC_PLATFORM_P F,
          PLATFORM_P G,
          DEVICE_P H
          
    WHERE     A.RADAR_INDEX = C.RADAR_INDEX(+)
          AND C.RADAR_MODE_INDEX = B.RADAR_MODE_INDEX(+)
          AND A.RADAR_INDEX = D.RADAR_INDEX(+)
          AND D.WEAPON_INDEX = E.WEAPON_INDEX(+)
          AND A.RADAR_INDEX = F.RADAR_INDEX(+)
          AND A.ELNOT = H.ELNOT(+)
          AND F.PLATFORM_INDEX = G.PLATFORM_INDEX(+);