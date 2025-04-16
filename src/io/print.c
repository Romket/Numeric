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

void printStr(char* str, int len)
{
    char buf[len];
    buf[len] = 0;

    for (int i = 0; i < len - 1; ++i)
    {
        if (str[i] == '\n')
        {
            os_PutStrFull(buf);
            os_NewLine();
            for (int j = 0; j < i; ++j) buf[j] = 0;
        }
        else buf[i] = str[i];
    }

    os_PutStrFull(buf);
}
