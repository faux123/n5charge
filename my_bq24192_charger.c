/* Copyright (c) 2013 LGE Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "my_bq24192_charger.h"

#include <linux/i2c.h>

#define INPUT_SRC_CONT_REG 0x00
#define CHARGE_CUR_CONT_REG 0x02

int my_bq24192_write_reg(struct i2c_client *client, int reg, u8 val)
{
	s32 ret;

	// Manipulate
	if (reg == INPUT_SRC_CONT_REG) val |= 0x07;
	else if (reg == CHARGE_CUR_CONT_REG) val |= 0xfc;

	ret = i2c_smbus_write_byte_data(client, reg, val);
	if (ret < 0) {
		dev_err(&client->dev,
			"i2c write fail: can't write %02x to %02x: %d\n",
			val, reg, ret);
		return ret;
	}
	return 0;
}
