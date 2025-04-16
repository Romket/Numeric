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

#include <ti/screen.h>

void printStr(const char* str)
{
    int lineBufferIndex = 0;

    unsigned int x, y;
    os_GetCursorPos(&y, &x);
    
    if (isLineEnd && x == SCREEN_WIDTH_CHARS - 1) ++x;
    
    for (int i = 0; i < MAX_STRING_LEN; ++i, ++lineBufferIndex)
    {
        // Ensure null termination by erasing any potentially existing data
        lineBuffer[lineBufferIndex + 1] = 0;
        if (str[i] == 0) break;
        
        if ((lineBufferIndex + x >= SCREEN_WIDTH_CHARS) || str[i] == '\n')
        {
            os_PutStrLine(lineBuffer);
            os_NewLine();
            
            lineBufferIndex = 0;
            lineBuffer[0] = 0;
            lineBuffer[1] = 0;
            
            x = 0;
        }
        
        if (str[i] != '\n') lineBuffer[lineBufferIndex] = str[i];
    }

    os_PutStrLine(lineBuffer);

    if (lineBufferIndex == SCREEN_WIDTH_CHARS) isLineEnd = true;
}

void printChar(const char val)
{
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
