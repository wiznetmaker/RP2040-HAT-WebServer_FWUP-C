#include "port_common.h"

#ifndef	__DEVICE_FWUP_H__
#define	__DEVICE_FWUP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define APPLICATION_OFFSET 0x100000 //1Mbytes
#define APPLICATION_ADDR   XIP_BASE + APPLICATION_OFFSET

void device_reset(void);
void disable_interrupts(void);
void reset_peripherals(void);
void jump_to_app(uint32_t app_addr);

#endif  //__DEVICE_FWUP_H__