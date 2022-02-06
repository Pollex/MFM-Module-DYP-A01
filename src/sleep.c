#include <avr/io.h>
#include <os/os.h>
#include "board.h"

void os_presleep(void)
{
  // return;
  // Configure BOD
  _PROTECTED_WRITE(BOD_CTRLA, BOD_CTRLA & ~(BOD_SLEEP_gm));

  // Enable all internal pullups
  PORTA.PIN0CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN1CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN2CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN3CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN4CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN5CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;
  PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN0CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN1CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN2CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN3CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN4CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN6CTRL |= PORT_PULLUPEN_bm;
  PORTB.PIN7CTRL |= PORT_PULLUPEN_bm;

  // Configure I2C Ports
  // I2C_Port.DIRSET = (1 << I2C_SCL_Pin) | (1 << I2C_SDA_Pin);
  // I2C_Port.OUTSET = (1 << I2C_SCL_Pin) | (1 << I2C_SDA_Pin);

  // Configure Sensor mosfets
  SENSOR_PWR_PORT.DIRSET = 1 << SENSOR_PWR_PIN;
  SENSOR_PWR_PORT.OUTCLR = 1 << SENSOR_PWR_PIN;

  // Configure Onewire
  ONEWIRE_Port.DIRSET = 1 << ONEWIRE_Pin;
  ONEWIRE_Port.OUTSET = 1 << ONEWIRE_Pin;

  // Configure SEN0313 TX/Rx
  SEN0313_Port.DIRSET = (1 << SEN0313_RX_Pin) | (1 << SEN0313_TX_Pin);
  SEN0313_Port.OUTCLR = (1 << SEN0313_RX_Pin) | (1 << SEN0313_TX_Pin);
}

void os_postsleep(void)
{
}