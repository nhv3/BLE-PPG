
#ifndef AD5593R_H_
#define AD5593R_H_

#include "stdint.h"
#include "I2C.h"
#include "SEGGER_RTT.h"
// checked >
#define BIT(n) (1<<(n))

#define CH_MODE_UNUSED			0
#define CH_MODE_ADC			1
#define CH_MODE_DAC			2
#define CH_MODE_DAC_AND_ADC		3
#define CH_MODE_GPIO			8

#define CH_OFFSTATE_PULLDOWN		0
#define CH_OFFSTATE_OUT_LOW		1
#define CH_OFFSTATE_OUT_HIGH		2
#define CH_OFFSTATE_OUT_TRISTATE	3
// checked <

#define AD5593R_MODE_CONF		(0 << 4)
#define AD5593R_MODE_DAC_WRITE		(1 << 4)
#define AD5593R_MODE_ADC_READBACK	(4 << 4)
#define AD5593R_MODE_DAC_READBACK	(5 << 4)
#define AD5593R_MODE_GPIO_READBACK	(6 << 4)
#define AD5593R_MODE_REG_READBACK	(7 << 4)
// checked >
enum ad5593r_registers {
	AD5593R_REG_NOOP		= 0x0,
	AD5593R_REG_DAC_READBACK	= 0x1,
	AD5593R_REG_ADC_SEQ		= 0x2,
	AD5593R_REG_CTRL		= 0x3,
	AD5593R_REG_ADC_EN		= 0x4,
	AD5593R_REG_DAC_EN		= 0x5,
	AD5593R_REG_PULLDOWN		= 0x6,
	AD5593R_REG_LDAC		= 0x7,
	AD5593R_REG_GPIO_OUT_EN		= 0x8,
	AD5593R_REG_GPIO_SET		= 0x9,
	AD5593R_REG_GPIO_IN_EN		= 0xA,
	AD5593R_REG_PD			= 0xB,
	AD5593R_REG_OPEN_DRAIN		= 0xC,
	AD5593R_REG_TRISTATE		= 0xD,
	AD5593R_REG_RESET		= 0xF,
};

#define AD5593R_REG_PD_EN_REF		BIT(9)
#define AD5593R_REG_CTRL_ADC_RANGE	BIT(5)
#define AD5593R_REG_CTRL_DAC_RANGE	BIT(4)

struct ad5593r_dev;
// checked <
struct ad5593r_rw_ops {
	int32_t (*write_dac)(struct ad5593r_dev *dev, uint8_t chan,
			     uint16_t value);
	int32_t (*read_adc)(struct ad5593r_dev *dev, uint8_t chan,
			    uint16_t *value);
	int32_t (*reg_write)(struct ad5593r_dev *dev, uint8_t reg,
			     uint16_t value);
	int32_t (*reg_read)(struct ad5593r_dev *dev, uint8_t reg,
			    uint16_t *value);
	int32_t (*gpio_read)(struct ad5593r_dev *dev, uint8_t *value);
};

struct ad5593r_dev {
	const struct ad5593r_rw_ops *ops;
	uint16_t spi_msg;
	uint8_t num_channels;
	uint16_t cached_dac[8];
	uint16_t cached_gp_ctrl;
	uint8_t channel_modes[8];
	uint8_t channel_offstate[8];
	uint8_t gpio_map;
	uint8_t gpio_out;
	uint8_t gpio_in;
	uint8_t gpio_val;
};

// checked >
void ad5593r_write_dac(uint8_t chan, uint16_t value);
//int32_t ad5593r_read_adc(struct ad5593r_dev *dev, uint8_t chan,uint16_t *value);
//int32_t ad5593r_reg_write(uint8_t reg, uint16_t value);
//int32_t ad5593r_reg_read(struct ad5593r_dev *dev, uint8_t reg, uint16_t *value);
//int32_t ad5593r_gpio_read(struct ad5593r_dev *dev, uint8_t *value);
//int32_t ad5593r_init(struct ad5593r_dev *dev);
void  AD5593R_Turn_On( void );
void ad5593r_config(void);
void ad5593_dac_status(void);
void ad5593_ch1(void);
// checked <
#endif /* AD5593R_H_ */
