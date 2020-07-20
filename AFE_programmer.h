#include "stdint.h"

void update_AFE_phase(uint8_t LED_phase);
void update_LED_drive(uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive);
void update_gain(uint8_t en_sep, uint8_t TIA_R1, uint8_t TIA_C1, uint8_t TIA_R2, uint8_t TIA_C2);
void program_AFE4404(uint8_t developer_mode, uint8_t LED_phase, uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive, uint8_t TIA_R1, uint8_t TIA_C1,uint8_t en_sep, uint8_t TIA_R2, uint8_t TIA_C2, uint8_t DAC1_off,uint8_t DAC2_off,uint8_t DAC3_off,uint8_t DACA_off);
void afe_read_settings(uint8_t);
void update_DAC(uint8_t,uint8_t,uint8_t,uint8_t);
