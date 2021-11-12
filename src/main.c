#include <avr/io.h>
#include <os/os.h>
#include <mcu/twi.h>

// PORT A
#define MCU_DBG_Port PORTA
#define MCU_RX_DBG_Pin PIN2_bp
#define MCU_TX_DBG_Pin PIN3_bp
#define SENSORS_ON_Port PORTA
#define SENSORS_ON_Pin PIN5_bp
#define SMBALERT_Port PORTA
#define SMBALERT_Pin PIN6_bp
#define ONEWIRE_Port PORTA
#define ONEWIRE_Pin PIN7_bp

// PORT B
#define I2C_Port PORTB
#define I2C_SCL_Pin PIN0_bp
#define I2C_SDA_Pin PIN1_bp

#define SEN0313_Port PORTB
#define SEN0313_TX_Pin PIN2_bp
#define SEN0313_RX_Pin PIN3_bp

int main(void)
{
  twi_init(0x36);
  os_init();

  // Never ends
  os_loop();
}

void os_presleep(void)
{
  // // Configure BOD
  // _PROTECTED_WRITE(BOD_CTRLA, BOD_CTRLA & ~(BOD_SLEEP_gm));

  // // Enable all internal pullups
  // PORTA.PIN0CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN1CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN2CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN3CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN4CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN5CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;
  // PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN0CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN1CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN2CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN3CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN4CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN5CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN6CTRL |= PORT_PULLUPEN_bm;
  // PORTB.PIN7CTRL |= PORT_PULLUPEN_bm;

  // // Configure I2C Ports
  // // I2C_Port.DIRSET = (1 << I2C_SCL_Pin) | (1 << I2C_SDA_Pin);
  // // I2C_Port.OUTSET = (1 << I2C_SCL_Pin) | (1 << I2C_SDA_Pin);

  // // Configure Sensor mosfets
  // SENSORS_ON_Port.DIRSET = 1 << SENSORS_ON_Pin;
  // SENSORS_ON_Port.OUTCLR = 1 << SENSORS_ON_Pin;

  // // Configure Onewire
  // ONEWIRE_Port.DIRSET = 1 << ONEWIRE_Pin;
  // ONEWIRE_Port.OUTSET = 1 << ONEWIRE_Pin;

  // // Configure SEN0313 TX/Rx
  // SEN0313_Port.DIRSET = (1 << SEN0313_RX_Pin) | (1 << SEN0313_TX_Pin);
  // SEN0313_Port.OUTCLR = (1 << SEN0313_RX_Pin) | (1 << SEN0313_TX_Pin);
}

void os_postsleep(void)
{
}

void doMeasure(void)
{
  SENSORS_ON_Port.OUTSET = 1 << SENSORS_ON_Pin;

  for (uint32_t ix = 0; ix < 100000; ix++)
  {
    __asm("nop");
  }
}

os_task task_doMeasure = {
    .func = &doMeasure,
    .priority = 1,
};

void cmd_doMeasure(uint8_t *buffer, uint8_t len)
{
  // os_pushTask(&task_doMeasure);
}

twi_cmd_t twi_cmds[] = {
    // {0x10, &cmd_doMeasure},
};