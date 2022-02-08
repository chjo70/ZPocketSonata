/* 40vxbStm32fEnd.cdf - Component configuration file */
                                                                                
/*
 * Copyright 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
                                                                                
/*
modification history
--------------------
14nov14,mpc  written
*/

Component DRV_VXBEND_STM32F {
     NAME         STM32F VxBus END driver
     SYNOPSIS     STM32F network driver
     MODULES      vxbStm32fEnd.o
     LINK_SYMS    stm32fEndDrv
     _CHILDREN    FOLDER_NET_END_DRV
     REQUIRES     INCLUDE_DMA_SYS \
                  INCLUDE_END
}

