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

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum Methods
{
    mEuler,
    mImpEuler,
    mRK4,
    mABM,
    mCustomRK,
    mQuit
} Methods;

void startupScreen();

Methods methodMenu();

bool strToNum(uint16_t* str, int len, double* result);
int strToInt(uint16_t* str, int len);

#ifdef __cplusplus
}
#endif
