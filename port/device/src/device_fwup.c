
#include "port_common.h"
#include "device_fwup.h"

void device_reset(void)
{
    NVIC_SystemReset();
    while(1);
}

void disable_interrupts(void)
{
  SysTick->CTRL &= ~1;

  NVIC->ICER[0] = 0xFFFFFFFF;
  NVIC->ICPR[0] = 0xFFFFFFFF;
}

void reset_peripherals(void)
{
    reset_block(~(
            RESETS_RESET_IO_QSPI_BITS |
            RESETS_RESET_PADS_QSPI_BITS |
            RESETS_RESET_SYSCFG_BITS |
            RESETS_RESET_PLL_SYS_BITS
    ));
}
 
void jump_to_app(uint32_t app_addr)
{
  uint32_t reset_vector = *(volatile uint32_t *)(app_addr + 0x04);

  sleep_ms(100);
  disable_interrupts();
  reset_peripherals();

  SCB->VTOR = app_addr;

	asm volatile("msr msp, %0"::"g"
			(*(volatile uint32_t *)app_addr));
  asm volatile("bx %0"::"r" (reset_vector));
}

