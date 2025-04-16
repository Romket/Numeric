/**
 * @file key.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements functions to convert a keycode to a usable value
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

#include <io/key.h>

#include <ti/getcsc.h>
#include <ti/getkey.h>

int getKeyNumberCSC(uint8_t key)
{
    switch (key)
    {
        case sk_0: return 0;
        case sk_1: return 1;
        case sk_2: return 2;
        case sk_3: return 3;
        case sk_4: return 4;
        case sk_5: return 5;
        case sk_6: return 6;
        case sk_7: return 7;
        case sk_8: return 8;
        case sk_9: return 9;
        default: return -1;
    }
}

int getKeyNumberKey(uint16_t key)
{
    return (key >= k_0 && key <= k_9) ? key - k_0 : -1;
}

int getKeyCharCSC(sk_key_t key, bool alpha)
{
    switch (key)
    {
        case sk_Enter: return '\n';
        case sk_Clear: return '\0';
        case sk_Alpha: return -1;
        case sk_Add: return alpha ? '"' : '+';
        case sk_Sub: return alpha ? 'W' : '-';
        case sk_Mul: return alpha ? 'R' : '*';
        case sk_Div: return alpha ? 'M' : '/';
        case sk_Graph: return alpha ? 'Y' : '^';
    }
}