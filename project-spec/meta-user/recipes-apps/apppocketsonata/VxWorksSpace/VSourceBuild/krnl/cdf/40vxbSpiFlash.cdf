/* 40vxbSpiFlash - Component configuration file */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09apr15,y_f  written. (V7PRO-1908)
*/

Component DRV_SPI_FLASH {
    NAME            SPI Flash vxBus Driver
    SYNOPSIS        This enables access to most modern SPI flash chips,       \
                    series supported include Atmel AT25, Spansion S25,        \
                    ST M25P, EN25 and Winbond W25X. Other chips are supported \
                    as well. See the driver source for the current list. This \
                    driver is a replace for DRV_SPIFLASH_SP25, so it cannot   \
                    be used together with DRV_SPIFLASH_SP25.
    MODULES         vxbSpiFlash.o
    LINK_SYMS       vxbSpiFlashDrv
    REQUIRES        INCLUDE_VXBUS       \
                    INCLUDE_SPI_BUS
    EXCLUDES        DRV_SPIFLASH_SP25
    _CHILDREN       FOLDER_FLASH
}