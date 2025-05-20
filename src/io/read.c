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

#include <string.h>

int readString(uint16_t** result)
{
    if (*result != NULL) free(*result);
    *result = calloc(MAX_STRING_LEN, sizeof(uint16_t));
    
    uint16_t key;

    os_EnableCursor();

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    int length, i = 0;
    for (i = 0; i < MAX_STRING_LEN; ++i)
    {
        key = os_GetKey();
        if (key == k_Enter) break;
        else if (key == k_Clear)
        {
            unsigned int curX, curY;

            // Clear newlines
            os_GetCursorPos(&curY, &curX);
            while (curY > y)
            {
                os_SetCursorPos(curY, 0);
                printStr(CLEAR_LINE);
                --curY;
            }

            // Clear original line
            os_SetCursorPos(y, x);
            for (curX = x; curX < SCREEN_WIDTH_CHARS; ++curX) printChar(' ');

            // Reset cursor position
            os_SetCursorPos(y, x);

            // Reset result
            memset(*result, 0, MAX_STRING_LEN * sizeof(uint16_t));
            i = 0;
        }

        char str[SCREEN_WIDTH_CHARS] = {0};
        if ((length = getKeyStringKey(key, str)) != -1)
        {
            (*result)[i] = key;
            printStr(str);
        }
    }

    os_DisableCursor();

    char clearCursorDot[2] = {0};
    clearCursorDot[0] = ' ';
    os_PutStrLine(clearCursorDot);

    os_NewLine();

    return i;
}
