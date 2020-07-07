#include "stdint.h"

void update_AFE_phase(uint8_t LED_phase);
void update_LED_drive(uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive);
void update_gain(uint8_t en_sep, uint8_t TIA_R1, uint8_t TIA_C1, uint8_t TIA_R2, uint8_t TIA_C2);
void program_AFE4404(uint8_t developer_mode, uint8_t LED_phase, uint8_t LED1_drive, uint8_t LED2_drive, uint8_t LED3_drive, uint8_t TIA_R1, uint8_t TIA_C1,uint8_t en_sep, uint8_t TIA_R2, uint8_t TIA_C2);
