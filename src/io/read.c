/**
 * @file read.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements functions to read user input
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

#include "stdbool.h"
#include <io/read.h>

#include <io/iodefs.h>
#include <io/key.h>
#include <io/print.h>
#include <stdint.h>
#include <stdlib.h>
#include <ti/getkey.h>
#include <ti/screen.h>

char* readString(int* length)
{
    char* string = malloc(MAX_STRING_LEN);
    uint16_t key;

    for (*length = 0; *length < MAX_STRING_LEN; ++*length)
    {
        key = os_GetKey();
        if (key == k_Enter) break;

        int c = getKeyCharKey(key); // int for -1 to 255 guaranteed

        if (c != -1)
        {
            // Implicit cast to char
            string[*length] = c;
            printChar(c);
        }
    }

    return string;
}
