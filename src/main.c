#include "board.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <os/os.h>
#include <os/linked_queue.h>
#include <mcu/twi.h>
#include <perif/sen0313.h>
#include <perif/ds18b20.h>
#include <drivers/onewire.h>
#include <mcu/util.h>

#define TWI_CMD_PERFORM 0x10
#define TWI_CMD_READ 0x11

// Tasks
void measurement(void);
os_task measurement_task = {
    .func = &measurement,
    .priority = 1,
};

sen0313_t sen0313 = {
    .mode = SEN0313_MODE_PROCESSED,
    .tx_port = &SEN0313_Port,
    .tx_pin = SEN0313_TX_Pin,
};

int main(void)
{
  sei(); // Enable interrupts
  delay_init();
  SENSOR_PWR_PORT.DIRSET = 1 << SENSOR_PWR_PIN;
  SENSOR_PWR_PORT.OUTCLR = 1 << SENSOR_PWR_PIN;

  OW_PORT.DIRCLR = 1 << OW_PIN;

  os_init();
  twi_init(0x36, 1);

  for (;;)
  {
    os_processTasks();
    os_sleep();
  }
}

volatile uint16_t reading = 0xffff;
volatile int16_t temperature = 0;
void measurement(void)
{
  SENSOR_PWR_PORT.OUTSET = 1 << SENSOR_PWR_PIN;

  // Read SEN0313
  sen0313_init(&sen0313);
  sen0313_read(&sen0313);
  reading = sen0313_read(&sen0313);

  // Read temperature
  float t = ds18b20_read(0);
  temperature = (int16_t)(t * 10);

  SENSOR_PWR_PORT.OUTCLR = 1 << SENSOR_PWR_PIN;
}

void twi_perform(uint8_t *buf, uint8_t length)
{
  os_pushTask(&measurement_task);
}

void twi_read(uint8_t *buf, uint8_t length)
{
  buf[0] = 4;
  buf[1] = (reading >> 8) & 0xff;
  buf[2] = reading & 0xff;
  buf[3] = (temperature >> 8) & 0xff;
  buf[4] = temperature & 0xff;
}

twi_cmd_t twi_cmds[] = {
    {
        .cmd = TWI_CMD_PERFORM,
        .handler = &twi_perform,
    },
    {
        .cmd = TWI_CMD_READ,
        .handler = &twi_read,
    },
};