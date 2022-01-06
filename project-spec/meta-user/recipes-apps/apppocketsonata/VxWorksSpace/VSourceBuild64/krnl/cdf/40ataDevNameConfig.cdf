/* 40vxbDevNameConfig.cdf - Component Definition file for 
    Sata/ata rename */

/* Copyright (c) 2007, 2014, 2016-2017 Wind River Systems, Inc. */

/*
modification history
--------------------
22jan17,jbm  Fixed spacing and line breaks, minor editing.
28mar16,hma  add the limitation of the disk/partition name.
27jan16,hma  surpport rename sata disk/partition(US74194)
01apr14,myt  written
*/

/* ATA Hard drive component */

Parameter FS_NAMES_SATA_DISK0 {
        NAME          SATA disk 0 logical names
        SYNOPSIS      "disk:" and "partition:" are the keywords. \
                      Disk names and partition names begin with '/'. \
                      Disk names and partition names are separated by ';'. \
                      Partition names are separated by '.'. \
                      NOTE: \
                        The length of the disk name should be less than 7. \
                        The length of the partition name should be less than 10.\
                      For example : \
                          "disk:/disk0;partition:/p01,/p02,,p04" \
                          "/disk0;partition:/p01,/p02,,p04"  \
                      The partition names are "/p01","/p02","/disk0:3","/p04". \
                          "partition:/p01,/p02,,p04".  \
                      The partition names are "/p01","/p02","/ata0:3","/p04".
        TYPE          string
        DEFAULT       ""
}

Parameter FS_NAMES_SATA_DISK1 {
        NAME          SATA disk 1 logical names
        SYNOPSIS      "disk:" and "partition:" are the keywords. \
                      Disk names and partition names begin with '/'. \
                      Disk names and partition names are separated by ';'. \
                      Partition names are separated by '.'. \
                      NOTE: \
                        The length of the disk name should be less than 7. \
                        The length of the partition name should be less than 10. \
                      For example : \
                          "disk:/disk1;partition:/p11,/p12,,p14"; \
                          "/disk1;partition:/p11,/p12,,p14" \
                      The partition names are "/p11","/p12","/disk1:3","/p14". \
                           "partition:/p11,/p12,,p14". \
                      The partition names are "/p11","/p12","/ata1:3","/p14".
        TYPE          string
        DEFAULT       ""
}

Parameter FS_NAMES_SATA_DISK2 {
        NAME          SATA disk 2 logical names
        SYNOPSIS      "disk:" and "partition:" are the keywords. \
                      Disk names and partition names begin with '/'. \
                      Disk names and partition names are separated by ';'. \
                      Partition names are separated by '.'. \
                      NOTE: \
                        The length of the disk name should be less than 7. \
                        The length of the partition name should be less than 10.
        TYPE          string
        DEFAULT       ""
}
Parameter FS_NAMES_SATA_DISK3 {
        NAME          SATA disk 3 logical names
        SYNOPSIS      "disk:" and "partition:" are the keywords. \
                      Disk names and partition names begin with '/'. \
                      Disk names and partition names are separated by ';'. \
                      Partition names are separated by '.'. \
                      NOTE: \
                        The length of the disk name should be less than 7. \
                        The length of the partition name should be less than 10.
        TYPE          string
        DEFAULT       ""
}

#ifdef _WRS_CONFIG_VXBUS_LEGACY
Component INCLUDE_SATA_DISK_NAME_CFG {
    NAME            SATA disk name
    SYNOPSIS        This component provides the SATA disk name configuration.
    _CHILDREN       FOLDER_BDM
    CONFIGLETTES    usrAta.c
    _INIT_ORDER     hardWareInterFaceBusInit
    CFG_PARAMS      FS_NAMES_SATA_DISK0    \
                    FS_NAMES_SATA_DISK1    \
                    FS_NAMES_SATA_DISK2    \
                    FS_NAMES_SATA_DISK3 
    INIT_RTN        usrAtaPartitionRename (0, FS_NAMES_SATA_DISK0);    \
                    usrAtaPartitionRename (1, FS_NAMES_SATA_DISK1);    \
                    usrAtaPartitionRename (2, FS_NAMES_SATA_DISK2);    \
                    usrAtaPartitionRename (3, FS_NAMES_SATA_DISK3);
    INIT_AFTER      INCLUDE_VXBUS_INIT
    INIT_BEFORE     INCLUDE_PLB_BUS
}
#else
Component INCLUDE_SATA_DISK_NAME_CFG {
    NAME            SATA disk name
    SYNOPSIS        This component can be used to change the default name of \
                    the device, which is normally derived from the device name \
                    and the partition number. The assignment of an empty string \
                    means that the default name is used (/ata0:0).
    _CHILDREN       FOLDER_BDM
    CONFIGLETTES    usrAta.c
    _INIT_ORDER     usrRoot
    CFG_PARAMS      FS_NAMES_SATA_DISK0    \
                    FS_NAMES_SATA_DISK1    \
                    FS_NAMES_SATA_DISK2    \
                    FS_NAMES_SATA_DISK3 
    INIT_RTN        usrAtaPartitionRename (0, FS_NAMES_SATA_DISK0);    \
                    usrAtaPartitionRename (1, FS_NAMES_SATA_DISK1);    \
                    usrAtaPartitionRename (2, FS_NAMES_SATA_DISK2);    \
                    usrAtaPartitionRename (3, FS_NAMES_SATA_DISK3);
    INIT_AFTER      usrIosCoreInit
    INIT_BEFORE     INCLUDE_VXBUS
}
#endif                                           
