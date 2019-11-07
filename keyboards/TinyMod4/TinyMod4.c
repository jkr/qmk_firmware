/* Copyright 2019 Jesse Rosenthal
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "TinyMod4.h"
#include "print.h"
#include "i2cmaster.h"


/* static uint8_t expander_reset_loop; */
uint8_t expander_status;
/* uint8_t expander_input_pin_mask; */
bool i2c_initialized = false;

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.


#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  i2c_init();
  i2c_start_wait(I2C_ADDR_WRITE);
  i2c_write (0x0C); // GPPUA
  i2c_write (0xff);
  i2c_write (0xff);
  i2c_stop();

}

unsigned char foo = 0;
unsigned char bar = 0;

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware

  /* Playing around with not using sequential mode. */
  i2c_start_wait(I2C_ADDR_WRITE);
  i2c_write (0x12); // GPIOA
  i2c_stop();

  i2c_start_wait(I2C_ADDR_READ);
  foo = i2c_read(0);
  i2c_stop();

  i2c_start_wait(I2C_ADDR_WRITE);
  i2c_write (0x13); // GPIOB
  i2c_stop();

  i2c_start_wait(I2C_ADDR_READ);
  bar = i2c_read(0);
  i2c_stop();

  foo ^= 0xff;
  bar ^= 0xff;
  if (!(foo == 0 && bar == 0)) {
    uprintf(" ["BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"]\n",
	    BYTE_TO_BINARY(foo),
	    BYTE_TO_BINARY(bar));
  }


  return process_record_user(keycode, record);
}



void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}
