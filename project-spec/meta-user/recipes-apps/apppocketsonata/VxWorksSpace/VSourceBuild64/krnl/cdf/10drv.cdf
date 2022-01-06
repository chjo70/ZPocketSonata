/* 10drver.cdf - Component configuration file */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------
14jun17,mjn  text updates (F8862)
01a,16jul13,l_z  created for VxBus GEN2
*/

Folder FOLDER_DRIVERS {
    NAME       Device drivers
    SYNOPSIS   This folder provides device drivers.
    _CHILDREN  FOLDER_HARDWARE
}

Folder   FOLDER_DRIVERS_TIMER {
    NAME    Timer
    SYNOPSIS    This folder contains timer related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_SERIAL {
    NAME    Serial
    SYNOPSIS    This folder contains serial port related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_SPI {
    NAME    SPI
    SYNOPSIS    This folder contains SPI related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_ADC {
    NAME    ADC
    SYNOPSIS    This folder ADC contains related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_DMA {
    NAME    DMA
    SYNOPSIS    This folder contains DMA and eDMA related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_EEPROM {
    NAME    EEPROM
    SYNOPSIS    This folder contains EEPROM related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_INTERRUPT {
    NAME    Interrupt
    SYNOPSIS    This folder contains interrupt related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_GPIO {
    NAME    GPIO
    SYNOPSIS    This folder contains GPIO related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_PCI {
    NAME    PCI
    SYNOPSIS    This folder contains PCI related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_BUS {
    NAME     Busses
    SYNOPSIS    This folder contains bus related drivers.
    _CHILDREN   FOLDER_DRIVERS
}

Folder  FOLDER_DRIVERS_OTHER {
    NAME     Other
    SYNOPSIS    This folder contains drivers that could not be easily placed into their own grouping.
    _CHILDREN   FOLDER_DRIVERS
}

