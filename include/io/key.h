/**
 * @file key.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Declares functions to convert a keycode to a usable value
 * @version 0.1
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

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>
    
// Returns -1 if the key is not a number
int getKeyNumberCSC(uint8_t key);
int getKeyNumberKey(uint16_t key);

int getKeyCharCSC(uint8_t key, bool alpha);
int getKeyStringKey(uint16_t key, char* str);

#ifdef __cplusplus
}
#endif
