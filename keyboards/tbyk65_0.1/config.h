#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* Device */
#define VENDOR_ID       0xDE29
#define PRODUCT_ID      0x7318
#define DEVICE_VER      0x0001
#define MANUFACTURER    Tebayaki
#define PRODUCT         tbyk65

/* Command */
#define IS_COMMAND() ( keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) )

/* Matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define MATRIX_ROW_PINS { F1,F0,D4,F5,F4}
#define MATRIX_COL_PINS { B6,D6,D7,B4,B5,B0,B1,B2,B3,B7,D0,D1,D3,E6}
#define DIODE_DIRECTION COL2ROW // COL2ROW or ROW2COL

#define DEBOUNCE 5
#define TAP_CODE_DELAY 10

#define TAPPING_TOGGLE 2
#define HOLD_ON_OTHER_KEY_PRESS

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#ifdef PS2_USE_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect

#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y

#endif

#endif
