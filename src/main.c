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

typedef struct
{
  unsigned short distance;
  float temperature;
} packet_t;

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

volatile packet_t packet;
void measurement(void)
{
  SENSOR_PWR_PORT.OUTSET = 1 << SENSOR_PWR_PIN;

  // Read SEN0313
  sen0313_init(&sen0313);
  sen0313_read(&sen0313);

  packet = (packet_t){
      .distance = sen0313_read(&sen0313),
      .temperature = ds18b20_read(0),
  };

  SENSOR_PWR_PORT.OUTCLR = 1 << SENSOR_PWR_PIN;
}

void twi_perform(uint8_t *buf, uint8_t length)
{
  os_pushTask(&measurement_task);
}

void twi_read(uint8_t *buf, uint8_t length)
{
  buf[0] = sizeof(packet_t);
  memcpy(&buf[1], &packet, sizeof(packet_t));
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