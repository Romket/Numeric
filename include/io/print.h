/**
 * @file print.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Defines functions for printing
 * @version 0.3
 * @date 2025-04-15
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

#include "ti/real.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include <io/iodefs.h>
#include <stdbool.h>

// 26 characters and a null terminator
static char lineBuffer[SCREEN_WIDTH_CHARS + 1] = {0};
static bool isLineEnd = false;
void printStr(const char* str);

void printChar(const char val);

void printInt(int val);

void printReal(const real_t val);

#ifdef __cplusplus
}
#endif
