/**
 * @file print.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements functions for printing
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

#include <io/print.h>

#include <io/iodefs.h>

#include <ti/screen.h>

void printStr(char* str)
{
    int i = 0;
    while (str[i] != '\0' && i < MAX_STRING_LEN) ++i;

    printStrLen(str, i + 1);
}

void printStrLen(char* str, int len)
{
    char buf[len];
    buf[0] = '\0';

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    int bufIndex = 0;
    for (int i = 0; i < len - 1; ++i, ++bufIndex)
    {
        // Ensure null termination by setting next element to '\0'
        buf[bufIndex + 1] = '\0';

        if (str[i] == '\n')
        {
            os_PutStrLine(buf);
            os_NewLine();
            
            bufIndex = -1; // will be 0 next loop iteration
            buf[0] = '\0';

            x = 0;
        }
        else buf[bufIndex] = str[i];

        if (bufIndex + x == SCREEN_WIDTH_CHARS + 1)
        {
            os_PutStrLine(buf);
            os_NewLine();
            bufIndex = -1;
            x = 0;
        }
    }

    if (bufIndex != 0) os_PutStrLine(buf);
}

// TODO: print characters without calling printStrLen
void printChar(char val)
{
    // char buf[2] = {0};
    // buf[0] = val;
    // printStrLen(buf, 2);

    if (val == '\n')
    {
        os_NewLine();
        return;
    }

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    if (x == SCREEN_WIDTH_CHARS) os_NewLine();

    char buf[2] = {0};
    buf[0] = val;
    os_PutStrLine(buf);
}
