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

#include <io/key.h> // for getKeyNumber
#include <ti/screen.h>

int readInt()
{
    int value = 0;
    char key;
    bool isNegative = false;

    int i = 0;
    while (true)
    {
        while (!(key = os_GetCSC()));

        if (getKeyNumber(key) != -1)
        {
            value *= 10;
            value += getKeyNumber(key);
            char str[2] = {0};
            str[0] = '0' + getKeyNumber(key);
            os_PutStrFull(str);
        }
        else if (key == sk_Chs && i == 0)
        {
            isNegative = true;
            char str[2] = {0};
            str[0] = '-';
            os_PutStrFull(str);
        }

        
        if (key == sk_Enter)
        {
            return value * (isNegative ? -1 : 1);
        }

        ++i;
    }
}

double readDouble()
{
    double value = 0.0;
    bool isDecimal = false;
    char key;

    while (true)
    {
        while (!(key = os_GetCSC()));

        if (getKeyNumber(key) != -1)
        {
            value *= 10;
            value += getKeyNumber(key);
        }
        else if (key == sk_Enter)
        {
            return value;
        }
    }
}
