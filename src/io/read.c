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

#include <io/read.h>

#include <io/iodefs.h>
#include <io/key.h>
#include <io/print.h>
#include <mathmenu.h>

#include <ti/getkey.h>
#include <ti/screen.h>

#include <string.h>

uint16_t* readString(int* len)
{
    static uint16_t result[MAX_STRING_LEN];

    uint16_t key;

    os_EnableCursor();

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    unsigned int lengths[MAX_STRING_LEN] = {0};

    for (*len = 0; *len < MAX_STRING_LEN; ++*len)
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

            // Reset result and lengths array
            memset(result, 0, MAX_STRING_LEN * sizeof(uint16_t));
            memset(lengths, 0, MAX_STRING_LEN * sizeof(unsigned int));
            *len = 0;
        }
        else if (key == k_Math)
        {
            key = mathMenu();

            os_EnableCursor();
            os_ClrHome();

            char str[SCREEN_WIDTH_CHARS] = {0};
            for (int j = 0; j <= *len; ++j)
            {
                getKeyStringKey(result[j], str);
                printStr(str);
            }
        }
        else if (key == k_Del && *len > 0)
        {
            os_DisableCursor();

            unsigned int curY, curX, targetX, targetY;
            os_GetCursorPos(&curY, &curX);

            --*len;

            if (curX < lengths[*len])
            {
                targetX = SCREEN_WIDTH_CHARS - (lengths[*len] - curX);
                targetY = curY - 1;
            }
            else
            {
                targetX = curX - lengths[*len];
                targetY = curY;
            }

            os_SetCursorPos(targetY, targetX);
            for (unsigned int j = 0; j <= lengths[*len]; ++j)
            {
                printChar(' ');
            }
            os_SetCursorPos(targetY, targetX);

            result[*len] = 0;
            lengths[*len] = 0;

            // decrement again to get the correct index in next loop iteration
            --*len;

            os_EnableCursor();
        }

        char str[SCREEN_WIDTH_CHARS] = {0};
        int length = getKeyStringKey(key, str);
        if (length != -1)
        {
            lengths[*len] = length;
            result[*len] = key;
            printStr(str);
        }
    }

    os_DisableCursor();

    char clearCursorDot[2] = {0};
    clearCursorDot[0] = ' ';
    os_PutStrLine(clearCursorDot);

    // TODO: check if clearing the dot goes to a newline on its own
    os_NewLine();

    return result;
}
