#include "AFE_programmer.h"
#include "AFE4404.h"
#include <stdio.h>
#include <string.h>
#include "stdint.h"
#include "nrf_delay.h"

extern volatile char LED_Sel;
extern volatile bool CALIBRATION_ENABLED;
extern volatile int Calibration;
extern volatile uint32_t LED_cntrl;
extern volatile uint32_t main_tia_gain;
extern volatile uint32_t sep_gain;
extern volatile uint32_t dac_set;




uint32_t Settings[5]= {0x00,0x00,0x00,0x00,0x00};
uint8_t setting_8b[20] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //4 bytes for each 32int and 1 byte for int8

void update_AFE_phase(uint8_t LED_phase)

{
        switch (LED_phase)
        {
          case 0x01: //nir, turn off LED1 and LED2
          printf("NIR ONLY \n");
                  LED_Sel = 3;
                  AFE4404_Reg_Write(0, 0x0); //CONTROL0
                  AFE4404_Reg_Write(1, 0x64); //LED2STC
                  AFE4404_Reg_Write(2, 0x18F); //LED2ENDC
                  AFE4404_Reg_Write(3, 0x0); //LED1LEDSTC
                  AFE4404_Reg_Write(4, 0x0); //LED1LEDENDC
                  AFE4404_Reg_Write(5, 0x1F5); //ALED2STC
                  AFE4404_Reg_Write(6, 0x320); //ALED2ENDC
                  AFE4404_Reg_Write(7, 0x386); //LED1STC
                  AFE4404_Reg_Write(8, 0x4B1); //LED1ENDC
                  AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                  AFE4404_Reg_Write(10, 0x0); //LED2LEDENDC
                  AFE4404_Reg_Write(11, 0x517); //ALED1STC
                  AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                  AFE4404_Reg_Write(13, 0x199); //LED2CONVST
                  AFE4404_Reg_Write(14, 0x5BC); //LED2CONVEND
                  AFE4404_Reg_Write(15, 0x5C6); //ALED2CONVST
                  AFE4404_Reg_Write(16, 0x9E9); //ALED2CONVEND
                  AFE4404_Reg_Write(17, 0x9F3); //LED1CONVST
                  AFE4404_Reg_Write(18, 0xE16); //LED1CONVEND
                  AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                  AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                  AFE4404_Reg_Write(21, 0x191); //ADCRSTSTCT0
                  AFE4404_Reg_Write(22, 0x197); //ADCRSTENDCT0
                  AFE4404_Reg_Write(23, 0x5BE); //ADCRSTSTCT1
                  AFE4404_Reg_Write(24, 0x5C4); //ADCRSTENDCT1
                  AFE4404_Reg_Write(25, 0x9EB); //ADCRSTSTCT2
                  AFE4404_Reg_Write(26, 0x9F1); //ADCRSTENDCT2
                  AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                  AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                  AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                  AFE4404_Reg_Write(30, 0x103); //CONTROL1
                  AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                  AFE4404_Reg_Write(49, 0x20); //CONTROL3
                  AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                  AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                  AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                  AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                  AFE4404_Reg_Write(54, 0x191); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x320); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 

          break;

          case 0x02: //green, turn off LED2 and LED 3
          printf("Green ONLY \n");
                  LED_Sel = 1;
                  AFE4404_Reg_Write(0, 0x0); //CONTROL0
                  AFE4404_Reg_Write(1, 0x64); //LED2STC
                  AFE4404_Reg_Write(2, 0x18F); //LED2ENDC
                  AFE4404_Reg_Write(3, 0x322); //LED1LEDSTC
                  AFE4404_Reg_Write(4, 0x4B1); //LED1LEDENDC
                  AFE4404_Reg_Write(5, 0x1F5); //ALED2STC
                  AFE4404_Reg_Write(6, 0x320); //ALED2ENDC
                  AFE4404_Reg_Write(7, 0x386); //LED1STC
                  AFE4404_Reg_Write(8, 0x4B1); //LED1ENDC
                  AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                  AFE4404_Reg_Write(10, 0x0); //LED2LEDENDC
                  AFE4404_Reg_Write(11, 0x517); //ALED1STC
                  AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                  AFE4404_Reg_Write(13, 0x199); //LED2CONVST
                  AFE4404_Reg_Write(14, 0x5BC); //LED2CONVEND
                  AFE4404_Reg_Write(15, 0x5C6); //ALED2CONVST
                  AFE4404_Reg_Write(16, 0x9E9); //ALED2CONVEND
                  AFE4404_Reg_Write(17, 0x9F3); //LED1CONVST
                  AFE4404_Reg_Write(18, 0xE16); //LED1CONVEND
                  AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                  AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                  AFE4404_Reg_Write(21, 0x191); //ADCRSTSTCT0
                  AFE4404_Reg_Write(22, 0x197); //ADCRSTENDCT0
                  AFE4404_Reg_Write(23, 0x5BE); //ADCRSTSTCT1
                  AFE4404_Reg_Write(24, 0x5C4); //ADCRSTENDCT1
                  AFE4404_Reg_Write(25, 0x9EB); //ADCRSTSTCT2
                  AFE4404_Reg_Write(26, 0x9F1); //ADCRSTENDCT2
                  AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                  AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                  AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                  AFE4404_Reg_Write(30, 0x103); //CONTROL1
                  AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                  AFE4404_Reg_Write(49, 0x20); //CONTROL3
                  AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                  AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                  AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                  AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                  AFE4404_Reg_Write(54, 0x0); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x0); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x03: //green nir, here we switch the LED1 and LED2 timing triggers so we have LED1 - LED2(off) - LED3 - AMB1 sample 
          printf("GN Scheme \n");
                  LED_Sel = 1;
                  AFE4404_Reg_Write(0, 0x0); //CONTROL0
                  AFE4404_Reg_Write(1, 0x1F5); //LED2STC
                  AFE4404_Reg_Write(2, 0x320); //LED2ENDC
                  AFE4404_Reg_Write(3, 0x322); //LED1LEDSTC
                  AFE4404_Reg_Write(4, 0x4B1); //LED1LEDENDC
                  AFE4404_Reg_Write(5, 0x0); //ALED2STC
                  AFE4404_Reg_Write(6, 0x18F); //ALED2ENDC
                  AFE4404_Reg_Write(7, 0x386); //LED1STC
                  AFE4404_Reg_Write(8, 0x4B1); //LED1ENDC
                  AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                  AFE4404_Reg_Write(10, 0x0); //LED2LEDENDC
                  AFE4404_Reg_Write(11, 0x517); //ALED1STC
                  AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                  AFE4404_Reg_Write(13, 0x5C6); //LED2CONVST
                  AFE4404_Reg_Write(14, 0x9E9); //LED2CONVEND
                  AFE4404_Reg_Write(15, 0x199); //ALED2CONVST
                  AFE4404_Reg_Write(16, 0x5BC); //ALED2CONVEND
                  AFE4404_Reg_Write(17, 0x9F3); //LED1CONVST
                  AFE4404_Reg_Write(18, 0xE16); //LED1CONVEND
                  AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                  AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                  AFE4404_Reg_Write(21, 0x5BE); //ADCRSTSTCT0
                  AFE4404_Reg_Write(22, 0x5C4); //ADCRSTENDCT0
                  AFE4404_Reg_Write(23, 0x191); //ADCRSTSTCT1
                  AFE4404_Reg_Write(24, 0x197); //ADCRSTENDCT1
                  AFE4404_Reg_Write(25, 0x9EB); //ADCRSTSTCT2
                  AFE4404_Reg_Write(26, 0x9F1); //ADCRSTENDCT2
                  AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                  AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                  AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                  AFE4404_Reg_Write(30, 0x103); //CONTROL1
                  AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                  AFE4404_Reg_Write(49, 0x20); //CONTROL3
                  AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                  AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                  AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                  AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                  AFE4404_Reg_Write(54, 0x0); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x18F); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x04: //red, turn off LED1 and LED3
          printf("Red ONLY \n");
          LED_Sel = 2;
                  AFE4404_Reg_Write(0, 0x0); //CONTROL0
                  AFE4404_Reg_Write(1, 0x64); //LED2STC
                  AFE4404_Reg_Write(2, 0x18F); //LED2ENDC
                  AFE4404_Reg_Write(3, 0x0); //LED1LEDSTC
                  AFE4404_Reg_Write(4, 0x0); //LED1LEDENDC
                  AFE4404_Reg_Write(5, 0x1F5); //ALED2STC
                  AFE4404_Reg_Write(6, 0x320); //ALED2ENDC
                  AFE4404_Reg_Write(7, 0x386); //LED1STC
                  AFE4404_Reg_Write(8, 0x4B1); //LED1ENDC
                  AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                  AFE4404_Reg_Write(10, 0x18F); //LED2LEDENDC
                  AFE4404_Reg_Write(11, 0x517); //ALED1STC
                  AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                  AFE4404_Reg_Write(13, 0x199); //LED2CONVST
                  AFE4404_Reg_Write(14, 0x5BC); //LED2CONVEND
                  AFE4404_Reg_Write(15, 0x5C6); //ALED2CONVST
                  AFE4404_Reg_Write(16, 0x9E9); //ALED2CONVEND
                  AFE4404_Reg_Write(17, 0x9F3); //LED1CONVST
                  AFE4404_Reg_Write(18, 0xE16); //LED1CONVEND
                  AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                  AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                  AFE4404_Reg_Write(21, 0x191); //ADCRSTSTCT0
                  AFE4404_Reg_Write(22, 0x197); //ADCRSTENDCT0
                  AFE4404_Reg_Write(23, 0x5BE); //ADCRSTSTCT1
                  AFE4404_Reg_Write(24, 0x5C4); //ADCRSTENDCT1
                  AFE4404_Reg_Write(25, 0x9EB); //ADCRSTSTCT2
                  AFE4404_Reg_Write(26, 0x9F1); //ADCRSTENDCT2
                  AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                  AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                  AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                  AFE4404_Reg_Write(30, 0x103); //CONTROL1
                  AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                  AFE4404_Reg_Write(49, 0x20); //CONTROL3
                  AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                  AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                  AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                  AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                  AFE4404_Reg_Write(54, 0x0); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x0); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x05: //red nir - in this phase, we switched the timing triggers for LED1 and LED3. This means we sample LED2 - LED1 (off) - LED3 - AMB1
                  printf("RN Scheme \n");
                  LED_Sel = 2;
                  AFE4404_Reg_Write(0, 0x0); //CONTROL0
                  AFE4404_Reg_Write(1, 0x64); //LED2STC
                  AFE4404_Reg_Write(2, 0x18F); //LED2ENDC
                  AFE4404_Reg_Write(3, 0x0); //LED1LEDSTC
                  AFE4404_Reg_Write(4, 0x0); //LED1LEDENDC
                  AFE4404_Reg_Write(5, 0x386); //ALED2STC
                  AFE4404_Reg_Write(6, 0x4B1); //ALED2ENDC
                  AFE4404_Reg_Write(7, 0x1F5); //LED1STC
                  AFE4404_Reg_Write(8, 0x320); //LED1ENDC
                  AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                  AFE4404_Reg_Write(10, 0x18F); //LED2LEDENDC
                  AFE4404_Reg_Write(11, 0x517); //ALED1STC
                  AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                  AFE4404_Reg_Write(13, 0x199); //LED2CONVST
                  AFE4404_Reg_Write(14, 0x5BC); //LED2CONVEND
                  AFE4404_Reg_Write(15, 0x9F3); //ALED2CONVST
                  AFE4404_Reg_Write(16, 0xE16); //ALED2CONVEND
                  AFE4404_Reg_Write(17, 0x5C6); //LED1CONVST
                  AFE4404_Reg_Write(18, 0x9E9); //LED1CONVEND
                  AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                  AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                  AFE4404_Reg_Write(21, 0x191); //ADCRSTSTCT0
                  AFE4404_Reg_Write(22, 0x197); //ADCRSTENDCT0
                  AFE4404_Reg_Write(23, 0x9EB); //ADCRSTSTCT1
                  AFE4404_Reg_Write(24, 0x9F1); //ADCRSTENDCT1
                  AFE4404_Reg_Write(25, 0x5BE); //ADCRSTSTCT2
                  AFE4404_Reg_Write(26, 0x5C4); //ADCRSTENDCT2
                  AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                  AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                  AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                  AFE4404_Reg_Write(30, 0x103); //CONTROL1
                  AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                  AFE4404_Reg_Write(49, 0x20); //CONTROL3
                  AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                  AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                  AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                  AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                  AFE4404_Reg_Write(54, 0x322); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x4B1); //LED3LEDENDC
                  AFE4404_Reg_Write(55, 0x320); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x06: //red green
          printf("RG Scheme\n");
                      LED_Sel = 1;
                      //In this mode, we sample LED2, null LED3 as amb2, and then sample LED1, followed by ambient LED 1 sampling
                     AFE4404_Reg_Write(0, 0x0); //CONTROL0
                      AFE4404_Reg_Write(1, 0x64); //LED2STC
                      AFE4404_Reg_Write(2, 0x18F); //LED2ENDC
                      AFE4404_Reg_Write(3, 0x322); //LED1LEDSTC
                      AFE4404_Reg_Write(4, 0x4B1); //LED1LEDENDC
                      AFE4404_Reg_Write(5, 0x1F5); //ALED2STC
                      AFE4404_Reg_Write(6, 0x320); //ALED2ENDC
                      AFE4404_Reg_Write(7, 0x386); //LED1STC
                      AFE4404_Reg_Write(8, 0x4B1); //LED1ENDC
                      AFE4404_Reg_Write(9, 0x0); //LED2LEDSTC
                      AFE4404_Reg_Write(10, 0x18F); //LED2LEDENDC
                      AFE4404_Reg_Write(11, 0x517); //ALED1STC
                      AFE4404_Reg_Write(12, 0x642); //ALED1ENDC
                      AFE4404_Reg_Write(13, 0x199); //LED2CONVST
                      AFE4404_Reg_Write(14, 0x5BC); //LED2CONVEND
                      AFE4404_Reg_Write(15, 0x5C6); //ALED2CONVST
                      AFE4404_Reg_Write(16, 0x9E9); //ALED2CONVEND
                      AFE4404_Reg_Write(17, 0x9F3); //LED1CONVST
                      AFE4404_Reg_Write(18, 0xE16); //LED1CONVEND
                      AFE4404_Reg_Write(19, 0xE20); //ALED1CONVST
                      AFE4404_Reg_Write(20, 0x1243); //ALED1CONVEND
                      AFE4404_Reg_Write(21, 0x191); //ADCRSTSTCT0
                      AFE4404_Reg_Write(22, 0x197); //ADCRSTENDCT0
                      AFE4404_Reg_Write(23, 0x5BE); //ADCRSTSTCT1
                      AFE4404_Reg_Write(24, 0x5C4); //ADCRSTENDCT1
                      AFE4404_Reg_Write(25, 0x9EB); //ADCRSTSTCT2
                      AFE4404_Reg_Write(26, 0x9F1); //ADCRSTENDCT2
                      AFE4404_Reg_Write(27, 0xE18); //ADCRSTSTCT3
                      AFE4404_Reg_Write(28, 0xE1E); //ADCRSTENDCT3
                      AFE4404_Reg_Write(29, 0x9C3F); //PRPCOUNT
                      AFE4404_Reg_Write(30, 0x103); //CONTROL1
                      AFE4404_Reg_Write(35, 0x124218); //CONTROL2
                      AFE4404_Reg_Write(49, 0x20); //CONTROL3
                      AFE4404_Reg_Write(50, 0x1563); //PDNCYCLESTC
                      AFE4404_Reg_Write(51, 0x991F); //PDNCYCLEENDC
                      AFE4404_Reg_Write(52, 0x0); //PROG_TG_STC
                      AFE4404_Reg_Write(53, 0x0); //PROG_TG_ENDC
                      AFE4404_Reg_Write(54, 0x0); //LED3LEDSTC
                      AFE4404_Reg_Write(55, 0x0); //LED3LEDENDC
                      AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x07: //red green nir
                      printf("RGN Scheme \n");
                      LED_Sel = 1;
                      AFE4404_Reg_Write(0, 0x0); //CONTROL0
                      AFE4404_Reg_Write(1, 100);    //AFE_LED2STC
                      AFE4404_Reg_Write(2, 399);    //AFE_LED2ENDC
                      AFE4404_Reg_Write(3, 802);    //AFE_LED1LEDSTC
                      AFE4404_Reg_Write(4, 1201);   //AFE_LED1LEDENDC
                      AFE4404_Reg_Write(5, 501);    //AFE_ALED2STC
                      AFE4404_Reg_Write(6, 800);    //AFE_ALED2ENDC
                      AFE4404_Reg_Write(7, 902);    //AFE_LED1STC
                      AFE4404_Reg_Write(8, 1201);   //AFE_LED1ENDC
                      AFE4404_Reg_Write(9, 0);      //AFE_LED2LEDSTC
                      AFE4404_Reg_Write(10, 399);   //AFE_LED2LEDENDC
                      AFE4404_Reg_Write(11, 1303);  //AFE_ALED1STC
                      AFE4404_Reg_Write(12, 1602);  //AFE_ALED1ENDC
                      AFE4404_Reg_Write(13, 409);   //AFE_LED2CONVST
                      AFE4404_Reg_Write(14, 1468);  //AFE_LED2CONVEND
                      AFE4404_Reg_Write(15, 1478);  //AFE_ALED2CONVST
                      AFE4404_Reg_Write(16, 2537);  //AFE_ALED2CONVEND
                      AFE4404_Reg_Write(17, 2547);  //AFE_LED1CONVST
                      AFE4404_Reg_Write(18, 3606);  //AFE_LED1CONVEND
                      AFE4404_Reg_Write(19, 3616);  //AFE_ALED1CONVST
                      AFE4404_Reg_Write(20, 4675);  //AFE_ALED1CONVEND
                      AFE4404_Reg_Write(21, 401);   //AFE_ADCRSTSTCT0
                      AFE4404_Reg_Write(22, 407);   //AFE_ADCRSTENDCT0
                      AFE4404_Reg_Write(23, 1470);  //AFE_ADCRSTSTCT1
                      AFE4404_Reg_Write(24, 1476);  //AFE_ADCRSTENDCT1
                      AFE4404_Reg_Write(25, 2539);  //AFE_ADCRSTSTCT2
                      AFE4404_Reg_Write(26, 2545);  //AFE_ADCRSTENDCT2
                      AFE4404_Reg_Write(27, 3608);  //AFE_ADCRSTSTCT3
                      AFE4404_Reg_Write(28, 3614);  //AFE_ADCRSTENDCT3
                      AFE4404_Reg_Write(54, 401);   //AFE_LED3LEDSTC //0 here means we use LED3 as AMB2
                      AFE4404_Reg_Write(55, 800);   //AFE_LED3LEDENDC //0 here means we use LED3 as AMB2
                      AFE4404_Reg_Write(29, 39999); //AFE_PRPCOUNT
                      AFE4404_Reg_Write(30, 0x000103);	//AFE_CONTROL1 TimerEN = 1; NUMAV = 3
                      AFE4404_Reg_Write(32, 0x008003);  //AFE_TIA_SEP_GAIN (LED2) ENSEPGAIN = 1; LED2/LED3 gain = 50K
                      AFE4404_Reg_Write(33, 0x000003);  //AFE_TIA_GAIN (LED1) LED1/LED1AMB gain = 50K
                      AFE4404_Reg_Write(58, 0x000000);  //AFE_DAC_SETTING_REG
                      AFE4404_Reg_Write(34, 0x0030CF); 	//LED3 - 3.125mA; LED2 - 3.125mA; LED1 - 12.5mA
                      AFE4404_Reg_Write(35, 0x124218); 	//DYN1, LEDCurr, DYN2, Ext CLK, DYN3, DYN4 //0x000200); - 0x200 Osc mode //AFE_CONTROL2
                      AFE4404_Reg_Write(49, 0x000020); 	//ENABLE_INPUT_SHORT
                      AFE4404_Reg_Write(57, 0);     	//CLKDIV_PRF
                      AFE4404_Reg_Write(50, 5475);  	//AFE_DPD1STC
                      AFE4404_Reg_Write(51, 39199); 	//AFE_DPD1ENDC
                      AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;
  
        }

}

void update_LED_drive(uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive)
{
    //First 6 bits are LED1 control 
    uint32_t LED1_val = (uint32_t)LED1_drive;
    uint32_t LED2_val = (uint32_t)(LED2_drive << 6);
    uint32_t LED3_val = (uint32_t)(LED3_drive << 12);
    LED_cntrl = LED3_val|LED2_val|LED1_val;

    AFE4404_Reg_Write(0, 0x0); //CONTROL0
    AFE4404_Reg_Write(AFE_LEDCNTRL,LED_cntrl);
    AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
}

void update_gain(uint8_t en_sep, uint8_t TIA_R1, uint8_t TIA_C1, uint8_t TIA_R2, uint8_t TIA_C2)
{
  uint32_t r1 = (uint32_t)TIA_R1;
  uint32_t c1 = (uint32_t)(TIA_C1 << 3);
  uint32_t r2 = (uint32_t)TIA_R2;
  uint32_t c2 = (uint32_t)(TIA_C2 << 3);
  
  main_tia_gain = c1 | r1;
 sep_gain = c2 | r2;

  if(en_sep == 1)
  {
      sep_gain = (0x8000 | sep_gain);
  }
    AFE4404_Reg_Write(0, 0x0); //CONTROL0
    AFE4404_Reg_Write(AFE_TIAAMBGAIN,main_tia_gain);
    AFE4404_Reg_Write(AFE_TIAGAIN,sep_gain);
    AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
}

void update_DAC(uint8_t DAC1, uint8_t DAC2, uint8_t DAC3, uint8_t DACA)
{
  uint32_t d1 = (uint32_t)DAC1 <<5;
  uint32_t d2 = (uint32_t)DAC2 << 15;
  uint32_t d3 = (uint32_t)DAC3;
  uint32_t da = (uint32_t)DACA << 10;
  dac_set = d2|da|d1|d3;

    AFE4404_Reg_Write(0, 0x0); //CONTROL0
    AFE4404_Reg_Write(AFE_DAC_SETTING_REG,dac_set);
    AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 



}

void program_AFE4404(uint8_t developer_mode, uint8_t LED_phase, uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive, uint8_t TIA_R1, uint8_t TIA_C1,uint8_t en_sep, uint8_t TIA_R2, uint8_t TIA_C2, uint8_t DAC1_off,uint8_t DAC2_off,uint8_t DAC3_off,uint8_t DACA_off)
{
     if(developer_mode == 0) //program only the phase update
     {
        update_AFE_phase(LED_phase);
        CALIBRATION_ENABLED = true;
        Calibration = 1;
     }

     else if (developer_mode == 1) //program phsae update and all other options
     {
       update_AFE_phase(LED_phase);
       update_LED_drive(LED1_drive,LED2_drive,LED3_drive);
       update_gain(en_sep,TIA_R1,TIA_C1,TIA_R2,TIA_C2);
       update_DAC(DAC1_off, DAC2_off, DAC3_off, DACA_off);
       CALIBRATION_ENABLED = false;
       Calibration = 0;
     }

}

void afe_read_settings(uint8_t LED_phase)
{

  Settings[0] = AFE4404_Reg_Read(AFE_DAC_SETTING_REG);
  Settings[1] = AFE4404_Reg_Read(AFE_LEDCNTRL);
  Settings[2]= AFE4404_Reg_Read(AFE_TIAAMBGAIN);
  Settings[3] = AFE4404_Reg_Read(AFE_TIAGAIN);
  Settings[4]= (uint32_t) LED_phase;

  memcpy(setting_8b, &Settings, sizeof(Settings));

  //return setting_8b;
}