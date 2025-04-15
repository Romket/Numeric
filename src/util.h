/**
 * @file util.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Miscellaneous utility functions
 * @version 0.2
 * @date 2025-04-13
 * 
 * @copyright Copyright (c) 2025 Luke Houston
 *
 * This file is a part of Numeric.
 *
 * Numeric is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Numeric is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Numeric.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "ti/getcsc.h"
#ifdef __cplusplus
extern "C"
{
#endif

void startupScreen(void);

void methodMenu(void);

int drawMenu(const char* title, const char** options, int count);

// returns a value 0-9 or -1 if given key is not a number
int getKeyNumber(sk_key_t key);

#ifdef __cplusplus
}
#endif