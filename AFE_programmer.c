#include "Calibration_AFE4404.h"
#include "AFE_programmer.h"
#include "AFE4404.h"
#include <stdio.h>
#include "nrf_delay.h"




void update_AFE(uint8_t LED_phase)

{
        switch LED_phase 
        {
          case 0x01: //nir, turn off LED1 and LED2
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
          break;

          case 0x04: //red, turn off LED1 and LED3
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
                  AFE4404_Reg_Write(54, 0x191); //LED3LEDSTC
                  AFE4404_Reg_Write(55, 0x320); //LED3LEDENDC
                  AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x06: //red green
                      //In this mode, we sample LED2, null LED3 as amb2, and then sample LED1, followed by ambient LED 1 sampling
                      AFE4404_Reg_Write(AFE_CONTROL0, 0x00000000);            // write mode           
                      AFE4404_Reg_Write(AFE_LED3LEDSTC, 0x00); //Set the start time for LED 3 to 0 
                      AFE4404_Reg_Write(AFE_TIAAMBGAIN, GAIN1); //Set the end time for LED 3 to 0   
                      AFE4404_Reg_Write(AFE_CONTROL0, 0x00000001); //seal the changes 
          break;

          case 0x07: //red green nir
          break;
  




        }





}