#include "LMP91000.h"
#include "I2C.h"
#include "nrf_drv_twi.h"
#include <stdint.h>

uint8_t LMP91000_write(uint8_t reg, uint8_t val) 
{
  uint8_t data[2];
  data[0] = reg;
  data[1] = val;
  write_bytes(LMP91000_I2C_ADDRESS, data, 2);
  return read_byte(LMP91000_I2C_ADDRESS,reg);
}

uint8_t LMP91000_read(uint8_t reg) 
{
  return read_byte(LMP91000_I2C_ADDRESS,reg);
}

uint8_t LMP91000_status(void) 
{
  return read_byte(LMP91000_I2C_ADDRESS,LMP91000_STATUS_REG);
}

uint8_t LMP91000_lock(void) 
{
  write_byte(LMP91000_I2C_ADDRESS, LMP91000_LOCK_REG, LMP91000_WRITE_LOCK);
  return read_byte(LMP91000_I2C_ADDRESS,LMP91000_LOCK_REG);
}

uint8_t LMP91000_unlock(void) 
{
  write_byte(LMP91000_I2C_ADDRESS, LMP91000_LOCK_REG, LMP91000_WRITE_UNLOCK);
  return read_byte(LMP91000_I2C_ADDRESS,LMP91000_LOCK_REG);
}

uint8_t LMP91000_configure(uint8_t _tiacn, uint8_t _refcn, uint8_t _modecn) 
{
        if(LMP91000_status() == LMP91000_READY){
            LMP91000_unlock();
            LMP91000_write(LMP91000_TIACN_REG, _tiacn);
            LMP91000_write(LMP91000_REFCN_REG, _refcn);
            LMP91000_write(LMP91000_MODECN_REG, _modecn);
            LMP91000_lock();
            return 1;
      }
      return 0;
}

