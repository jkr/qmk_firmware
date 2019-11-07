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
#pragma once

#include "quantum.h"
#include "matrix.h"
#include <stdint.h>
#include <stdbool.h>

/* /\* static uint8_t expander_reset_loop; *\/ */
/* uint8_t expander_status; */
/* /\* uint8_t expander_input_pin_mask; *\/ */
/* bool i2c_initialized = false; */

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.


#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )




/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT(k00, k01, k02, k03, k04, k05, k06, k07, k08)	\
  { { k00, k01, k02, k03, k04, k05, k06, k07, k08 }}
