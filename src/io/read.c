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
#include <io/symbols.h>
#include <mathmenu.h>

#include <ti/getkey.h>
#include <ti/screen.h>

#include <string.h>

uint16_t* readString(int* len, char* prompt)
{
    printStr(prompt);

    static uint16_t result[MAX_STRING_LEN];

    uint16_t key;

    os_EnableCursor();

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    unsigned int lengths[MAX_STRING_LEN] = {0};

    for (int i = 0; *len < MAX_STRING_LEN; ++i, ++*len)
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
            i = 0;
            *len = 0;
        }
        else if (key == k_Math)
        {
            key = mathMenu();

            os_EnableCursor();
            os_ClrHome();

            printStr(prompt);

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

            --i;
            --*len;

            TargetCursorPos target = getTargetPos(lengths, i);

            // Less than or equal to needed to clear trailing cursor dot
            os_SetCursorPos(target.y, target.x);
            for (unsigned int j = 0; j <= lengths[i]; ++j)
            {
                printChar(' ');
            }
            os_SetCursorPos(target.y, target.x);

            result[*len] = 0;
            lengths[*len] = 0;

            // decrement again to get the correct index in next loop iteration
            --i;
            --*len;

            os_EnableCursor();
        }
        else if (key == k_Left)
        {
            if (i <= 0) continue;

            i--;

            TargetCursorPos target = getTargetPos(lengths, i);
            os_SetCursorPos(target.y, target.x);
        }
        else if (key == k_Right)
        {
            if (i >= *len) continue;

            i++;

            TargetCursorPos target = getTargetPos(lengths, i);
            os_SetCursorPos(target.y, target.x);
        }

        char str[SCREEN_WIDTH_CHARS] = {0};
        int length = getKeyStringKey(key, str);
        if (length != -1)
        {
            lengths[i] = length;
            result[i] = key;
            
            if (i == *len || lengths[i] == length)
            {
                printStr(str);
                continue;
            }

            unsigned int curX, curY;
            os_GetCursorPos(&curY, &curX);
            for (int j = i; j <= *len; ++j)
            {
                char str[SCREEN_WIDTH_CHARS] = {0};
                getKeyStringKey(result[j], str);
                printStr(str);
            }

            if (lengths[i] > length)
                for (int j = 0; j < lengths[i] - length; ++j) printChar(' ');

            os_SetCursorPos(curY, curX);
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

TargetCursorPos getTargetPos(unsigned int lengths[MAX_STRING_LEN], int i)
{
    TargetCursorPos result;

    unsigned int curX, curY;
    os_GetCursorPos(&curY, &curX);

    if (curX < lengths[i])
    {
        result.x = SCREEN_WIDTH_CHARS - (lengths[i] - curX);
        result.y = curY - 1;
    }
    else
    {
        result.x = curX - lengths[i];
        result.y = curY;
    }

    return result;
}

int readInt()
{
    int result = 0;
    bool negative = false;

    uint16_t key;

    os_EnableCursor();

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    for (int i = 0; i < MAX_STRING_LEN; ++i)
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

            result = 0;
            i = 0;
            negative = false;
        }
        else if (key == k_Del && i > 0)
        {
            os_DisableCursor();

            unsigned int curY, curX, targetX, targetY;
            os_GetCursorPos(&curY, &curX);

            --i;

            targetX = (curX == 0 ? SCREEN_WIDTH_CHARS : curX) - 1;
            targetY = curY - curX == 0;

            os_SetCursorPos(targetY, targetX);
            printChar(' ');
            os_SetCursorPos(targetY, targetX);

            if (i == 0) negative = false;
            result /= 10;

            // decrement again to get the correct index in next loop iteration
            --i;

            os_EnableCursor();
        }

        if (key >= k_0 && key <= k_9)
        {
            result *= 10;
            result += key - k_0;
            printChar((key - k_0) + '0');
        }
        else if (key == k_Chs && i == 0)
        {
            negative = true;
            printChar(CHS);
        }
    }

    os_DisableCursor();

    char clearCursorDot[2] = {0};
    clearCursorDot[0] = ' ';
    os_PutStrLine(clearCursorDot);

    // TODO: check if clearing the dot goes to a newline on its own
    os_NewLine();

    return result * (negative ? -1 : 1);
}

float readFloat()
{
    float result = 0.0;
    bool negative = false;
    int place = -1;
    int lastDigit = 0;

    uint16_t key;

    os_EnableCursor();

    unsigned int x, y;
    os_GetCursorPos(&y, &x);

    for (int i = 0; i < MAX_STRING_LEN; ++i)
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

            result = 0;
            i = 0;
            negative = false;
            place = -1;
        }
        else if (key == k_Del && i > 0)
        {
            os_DisableCursor();

            unsigned int curY, curX, targetX, targetY;
            os_GetCursorPos(&curY, &curX);

            --i;

            targetX = (curX == 0 ? SCREEN_WIDTH_CHARS : curX) - 1;
            targetY = curY - curX == 0;

            os_SetCursorPos(targetY, targetX);
            printChar(' ');
            os_SetCursorPos(targetY, targetX);

            if (i == 0) negative = false;

            if (place == -1) result = (int)result / 10;
            if (place == 0) place = -1;
            else
            {
                float lastNum = (float)lastDigit;
                for (int i = 0; i < place; ++i) lastNum /= 10.0;
                result -= lastNum;

                --place;
            }

            // decrement again to get the correct index in next loop iteration
            --i;

            os_EnableCursor();
        }

        if (key >= k_0 && key <= k_9)
        {
            if (place == -1)
            {
                result *= 10;
                result += key - k_0;
            }
            else
            {
                float num = key - k_0;
                for (int i = 0; i < place; ++i) num /= 10.0;
                result += num;
                ++place;
            }
            printChar((key - k_0) + '0');
        }
        else if (key == k_Chs && i == 0)
        {
            negative = true;
            printChar(CHS);
        }
        else if (key == k_DecPnt && place == -1)
        {
            place = 0;
            printChar('.');
        }
    }

    os_DisableCursor();

    char clearCursorDot[2] = {0};
    clearCursorDot[0] = ' ';
    os_PutStrLine(clearCursorDot);

    // TODO: check if clearing the dot goes to a newline on its own
    os_NewLine();

    return result * (negative ? -1 : 1);
}
