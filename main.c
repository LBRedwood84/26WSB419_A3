// Example file - Public Domain
// Need help? http://bit.ly/bluepad32-help

#include <stdlib.h>
#include <time.h>

#include <btstack_port_esp32.h>
#include <btstack_run_loop.h>
#include <btstack_stdio_esp32.h>
#include <hci_dump.h>
#include <hci_dump_embedded_stdout.h>
#include <uni.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define UART_PORT_NUM      UART_NUM_1
#define TXD_PIN            GPIO_NUM_11
#define RXD_PIN            UART_PIN_NO_CHANGE

static void init_uart(void) {
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_PORT_NUM, 1024, 0, 0, NULL, 0);
}

// Defined in my_platform.c
struct uni_platform* get_my_platform(void);

int app_main(void){
    // If you enable HCI Dump better to disable "Bluepad32 USB Console" from "idf.py menuconfig".
    //  hci_dump_init(hci_dump_embedded_stdout_get_instance());
    // Don't use BTstack buffered UART. It conflicts with the console.

#ifdef CONFIG_ESP_CONSOLE_UART
#ifndef CONFIG_BLUEPAD32_USB_CONSOLE_ENABLE
    btstack_stdio_init();
#endif  // CONFIG_BLUEPAD32_USB_CONSOLE_ENABLE
#endif  // CONFIG_ESP_CONSOLE_UART

    init_uart();
    btstack_init(); 
    uni_platform_set_custom(get_my_platform());
    uni_init(0 /* argc */, NULL /* argv */);

    // Does not return.
    btstack_run_loop_execute();

    return 0;
}
