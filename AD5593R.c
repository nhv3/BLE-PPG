#include "AD5593R.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"

#define NRF_LOG_MODULE_NAME "I2C"

// I2C instance.
#define TWI_INSTANCE_ID 0
static const nrf_drv_twi_t i2c = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

#define AD5593R_ADDRESS  0x10U//(0x10 << 1)
/**
 * Write DAC channel.
 *
 * @param dev - The device structure.
 * @param chan - The channel number.
 * @param value - DAC value
 * @return 0 in case of success, negative error code otherwise
 */
//void ad5593r_write_dac(uint8_t chan, uint16_t value)
//{
//	uint8_t data[3];
//
//	data[0] = AD5593R_MODE_DAC_WRITE | chan;
//	data[1] = (value >> 8) & 0xF ;
//	data[2] = value & 0xFF;
//
//	write_bytes(AD5593R_ADDRESS, data, sizeof(data));
//}

void ad5593r_config(void)
{

uint8_t data[3];
//
	data[0] = 0x05;
	data[1] = 0x00;
	data[2] = 0xFF;
         
        write_bytes(AD5593R_ADDRESS, data, 3);
//        
//
//        return nrf_drv_twi_tx(&i2c, AD5593R_ADDRESS, data, sizeof(data), false);

	//return i2c_write(dev->i2c, data, sizeof(data), 0);

      
}
void ad5593_dac_status(void)
{
uint8_t dacID[2];
    read_bytes(AD5593R_ADDRESS, 0x75, dacID, 2);//read_bytes(AD5593R_ADDRESS, 0x75, dacID, 2);75 for DAC output pins; 77 for LDAC
    uint16_t dacID_16;
    dacID_16 = (uint16_t) dacID[0] << 8 | dacID[1];
    //SEGGER_RTT_printf(0, "DAC config is:%d \n", dacID_16);
}

void ad5593_ch1(void)
{
uint8_t dacID[2];
    read_bytes(AD5593R_ADDRESS, 0x59, dacID, 3);
    uint16_t dacID_16;
    dacID_16 = (uint16_t) dacID[0] << 8 | dacID[1];
    //SEGGER_RTT_printf(0, "Ch 1 is:%d \n", dacID_16);
}

void ad5593r_write_dac(uint8_t chan, uint16_t value)
{
	uint8_t data[3];

	data[0] = AD5593R_MODE_DAC_WRITE | chan;
	data[1] = (value >> 8) & 0xF ;
	data[2] = value & 0xFF;

        write_bytes(AD5593R_ADDRESS, data, 3);

	//return i2c_write(dev->i2c, data, sizeof(data), 0);
}

void AD5593R_Turn_On(void)
{
    
    //to confirm ID let's read back the pull down configuration register = default is 0x00FF
    //AD5593R
    //readback = 0111____
    //so command is
    //0111 0110 = 0x76
    //all other registers are 0 by default; only the PDCR has nonzero default useful for checcking
    //chip ID

    uint8_t data1[3];

    data1[0] = 0x0F;
    data1[1] = 0x0D;
    data1[2] = 0xAC;

    int32_t res = nrf_drv_twi_tx(&i2c, AD5593R_ADDRESS, data1, sizeof(data1), false);

    nrf_delay_us(10000);
    
    uint8_t devID[2];

    read_bytes(AD5593R_ADDRESS, 0x76, devID, 2);

    uint16_t devID_16;
    
    devID_16 = (uint16_t) devID[0] << 8 | devID[1];
            
    //SEGGER_RTT_printf(0, "AD5593R ID:%d Should be = 255\n", devID_16);

    
                 
    //if( devID_16 == 255 )
        //AD5593R_Configure();
        
}
///**
// * Read ADC channel.
// *
// * @param dev - The device structure.
// * @param chan - The channel number.
// * @param value - ADC value
// * @return 0 in case of success, negative error code otherwise
// */
//int32_t ad5593r_read_adc(struct ad5593r_dev *dev, uint8_t chan,
//			 uint16_t *value)
//{
//	int32_t ret;
//	uint8_t data[3];
//	uint16_t temp;
//
//	if (!dev)
//		return -1;
//
//	temp = BIT(chan);
//
//	data[0] = AD5593R_MODE_CONF | AD5593R_REG_ADC_SEQ;
//	data[1] = temp >> 8;
//	data[2] = temp & 0xFF;
//
//	ret = write_bytes(AD5593R_ADDRESS, data, sizeof(data));
//	if (ret < 0)
//		return ret;
//
//	data[0] = AD5593R_MODE_ADC_READBACK;
//	ret = write_byte(AD5593R_ADDRESS, data, 1);
//	if (ret < 0)
//		return ret;
//
//	ret = read_bytes(AD5593R_ADDRESS, data, 2);
//	if (ret < 0)
//		return ret;
//
//	*value = (uint16_t)((data[0] & 0x0F) << 8) + data[1];
//
//	return 0;
//}

/**
 * Write register.
 *
 * @param dev - The device structure.
 * @param reg - The register address.
 * @param value - register value
 * @return 0 in case of success, negative error code otherwise
 */
//int32_t ad5593r_reg_write(uint8_t reg, uint16_t value)
//{
//	uint8_t data[3];
//
//
//	data[0] = AD5593R_MODE_CONF | reg;
//	data[1] = value >> 8;
//	data[2] = value;
//
//        return nrf_drv_twi_tx(&i2c, AD5593R_ADDRESS, data, sizeof(data), false);
//}

/**
 * Read register.
 *
 * @param dev - The device structure.
 * @param reg - The register address.
 * @param value - register value
 * @return 0 in case of success, negative error code otherwise
 */
//int32_t ad5593r_reg_read(struct ad5593r_dev *dev, uint8_t reg,
//			 uint16_t *value)
//{
//	int32_t ret;
//	uint8_t data[2];
//
//	if (!dev)
//		return -1;
//
//	data[0] = AD5593R_MODE_REG_READBACK | reg;
//
//	ret = write_byte(AD5593R_ADDRESS, data, 1);
//	if (ret < 0)
//		return ret;
//
//	ret = read_bytes(AD5593R_ADDRESS, data, sizeof(data));
//	if (ret < 0)
//		return ret;
//
//	*value = (uint16_t) (data[0] << 8) + data[1];
//
//	return 0;
//}

/**
 * Read GPIOs.
 *
 * @param dev - The device structure.
 * @param value - GPIOs value.
 * @return 0 in case of success, negative error code otherwise
 */
//int32_t ad5593r_gpio_read(struct ad5593r_dev *dev, uint8_t *value)
//{
//	int32_t ret;
//	uint8_t data[2];
//
//	if (!dev)
//		return -1;
//
//	data[0] = AD5593R_MODE_GPIO_READBACK;
//	ret = write_byte(AD5593R_ADDRESS, data, 1, 0);
//	if (ret < 0)
//		return ret;
//
//	ret = read_byte(AD5593R_ADDRESS, data, sizeof(data), 0);
//	if (ret < 0)
//		return ret;
//
//	*value = data[1];
//
//	return 0;
//}



/**
 * Software reset device.
 *
 * @param dev - The device structure.
 * @return 0 in case of success, negative error code otherwise
 */
//int32_t ad5593r_software_reset()
//{
//	int32_t ret;
//
//
//
//	/* Writing this magic value resets the device */
//	ret = ad5593r_reg_write(struct ad5593r_dev *dev, AD5593R_REG_RESET, 0xdac);
//
//	mdelay(10);
//
//	return ret;
//}

/**
 * Set channels modes.
 *
 * @param dev - The device structure.
 * @return 0 in case of success, negative error code otherwise
 */
//int32_t ad5593r_set_channel_modes(struct ad5593r_dev *dev)
//{
//	int32_t ret;
//	uint8_t i;
//	uint8_t pulldown = 0, tristate = 0, dac = 0, adc = 0;
//	uint16_t read_back;
//
//	if (!dev)
//		return -1;
//
//	for (i = 0; i < dev->num_channels; i++) {
//		switch (dev->channel_modes[i]) {
//		case CH_MODE_DAC:
//			dac |= BIT(i);
//			break;
//
//		case CH_MODE_ADC:
//			adc |= BIT(i);
//			break;
//
//		case CH_MODE_DAC_AND_ADC:
//			dac |= BIT(i);
//			adc |= BIT(i);
//			break;
//
//		case CH_MODE_GPIO:
//			dev->gpio_map |= BIT(i);
//			dev->gpio_in |= BIT(i); /* Default to input */
//			break;
//
//		case CH_MODE_UNUSED:
//		/* fall-through */
//		default:
//			switch (dev->channel_offstate[i]) {
//			case CH_OFFSTATE_OUT_TRISTATE:
//				tristate |= BIT(i);
//				break;
//
//			case CH_OFFSTATE_OUT_LOW:
//				dev->gpio_out |= BIT(i);
//				break;
//
//			case CH_OFFSTATE_OUT_HIGH:
//				dev->gpio_out |= BIT(i);
//				dev->gpio_val |= BIT(i);
//				break;
//
//			case CH_OFFSTATE_PULLDOWN:
//			/* fall-through */
//			default:
//				pulldown |= BIT(i);
//				break;
//			}
//		}
//	}
//
//	/* Pull down unused pins to GND */
//	ret = ad5593r_reg_write(dev, AD5593R_REG_PULLDOWN, pulldown);
//	if (ret < 0)
//		return ret;
//
//	ret = ad5593r_reg_write(dev, AD5593R_REG_TRISTATE, tristate);
//	if (ret < 0)
//		return ret;
//
//	/* Configure pins that we use */
//	ret = ad5593r_reg_write(dev, AD5593R_REG_DAC_EN, dac);
//	if (ret < 0)
//		return ret;
//
//	ret = ad5593r_reg_write(dev, AD5593R_REG_ADC_EN, adc);
//	if (ret < 0)
//		return ret;
//
//	ret = ad5593r_reg_write(dev, AD5593R_REG_GPIO_SET, dev->gpio_val);
//	if (ret < 0)
//		return ret;
//
//	ret = ad5593r_reg_write(dev, AD5593R_REG_GPIO_OUT_EN,
//				     dev->gpio_out);
//	if (ret < 0)
//		return ret;
//
//	ret = ad5593r_reg_write(dev, AD5593R_REG_GPIO_IN_EN,
//				     dev->gpio_in);
//	if (ret < 0)
//		return ret;
//
//	/* Verify that we can read back at least one register */
//	ret = ad5593r_reg_read(dev, AD5593R_REG_ADC_EN, &read_back);
//	if (!ret && (read_back & 0xff) != adc)
//		return -1;
//
//	return ret;
//}
//
//
//
///**
// * Initialize AD5593r device.
// *
// * @param dev - The device structure.
// * @return 0 in case of success, negative error code otherwise
// */
//int32_t ad5593r_init(struct ad5593r_dev *dev)
//{
//	int32_t ret;
//
//	if (!dev)
//		return -1;
//
//	ret = ad5593r_software_reset(dev);
//	if (ret < 0)
//		return ret;
//
//	return ad5593r_set_channel_modes(dev);
//}