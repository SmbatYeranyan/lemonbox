#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "at.h"
#include "gpio.h"
extern uint8_t at_wifiMode;

void user_init(void)
{
  uart_init(BIT_RATE_115200, BIT_RATE_115200);
  at_wifiMode = wifi_get_opmode();
  os_printf("\r\nready!!!\r\n");
  uart0_sendStr("\r\nready LOL 8.2 GPIO\r\n");
  at_init();

  gpio_init();

  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
  gpio_output_set(0, BIT2, BIT2, 0);
  
}
