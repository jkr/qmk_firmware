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
#include "i2c_master.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

static uint8_t expander_status = 0;

void expander_scan(void)
{
  uprintf("expander status: %d ... ", expander_status);
  uint8_t ret = i2c_start(0x20, 1000);
  uprintf("(retval: %d) ", ret);
  if (ret == 0) {
    uprintf("hello");
    i2c_stop();
    if (expander_status == 0) {
      uprintf("attached\n");
      expander_status = 1;
      clear_keyboard();
    }
  }
  else {
    if (expander_status == 1) {
      uprintf("detached\n");
      expander_status = 0;
      clear_keyboard();
    } else {
      uprintf("connection err\n");
      expander_status = 0;
      clear_keyboard();
    }
  }
  uprintf("%d\n", expander_status);
}


void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  i2c_init();
}



void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware

  expander_scan();
  return process_record_user(keycode, record);
}



void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}
