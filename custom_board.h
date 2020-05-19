

// Defines the number of LEDs. In this example, there is a single RGB LED.
#define LEDS_NUMBER    3
// Defines which PIOs control the color of the LED.

#define LED_RGB_RED    26
#define LED_RGB_GREEN  24
#define LED_RGB_BLUE   23

// Defines an RGB LED as 3 single LEDs.
#define BSP_LED_0 LED_RGB_RED
#define BSP_LED_1 LED_RGB_GREEN
#define BSP_LED_2 LED_RGB_BLUE
#define LED_RGB_RED_MASK    (1<<LED_RGB_RED)
#define LED_RGB_GREEN_MASK  (1<<LED_RGB_GREEN)
#define LED_RGB_BLUE_MASK   (1<<LED_RGB_BLUE)
#define BSP_LED_0_MASK    (1<<BSP_LED_0)
#define BSP_LED_1_MASK    (1<<BSP_LED_1)
#define BSP_LED_2_MASK    (1<<BSP_LED_2)
#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | BSP_LED_2_MASK)
//// Defines which LEDs are lit when the signal is low. In this example,
//// all LEDs are lit.
//#define LEDS_INV_MASK  LEDS_MASK
//// Defines the user buttons. In this example, there are no user buttons.
//#define BUTTONS_NUMBER 0
//#define BUTTONS_MASK   0x00000000
//// Defines the UART connection with J-Link.
//#define RX_PIN_NUMBER  11
//#define TX_PIN_NUMBER  9
//#define CTS_PIN_NUMBER 10
//#define RTS_PIN_NUMBER 8
//#define HWFC           true



#define MUX_A0      14
#define MUX_A1      9
#define MUX_EN      10
#define DAC_A0      11
#define DAC_RST      6
#define P1_MEN      7
//
//#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_RC,              \
//                                 .rc_ctiv       = 16,                               \
//                                 .rc_temp_ctiv  = 2,                                \
//                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}