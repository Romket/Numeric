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

#include "io/iodefs.h"
#include <io/key.h>

#include <stdlib.h>
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

//! Unfinished, do not use!
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

int getKeyStringKey(uint16_t key, char* str)
{
    str = malloc(MAX_STRING_LEN);

    if (key >= k_CapA && key <= k_CapZ)
    {
        str[0] = (key - k_CapA) + 'A';
        return 1;
    }
    else if (key >= k_0 && key <= k_9)
    {
        str[0] = '0' + (key - k_0);
        return 1;
    }

    switch (key)
    {
        case k_EE: str = "*10^"; return 4;
        case k_Space: str = " "; return 1;
        case k_Varx: str = "x"; return 1;
        case k_Pi: str = "π"; return 1;
        case k_Inv: str = "⁻¹"; return 2;
        case k_Sin: str = "sin("; return 4;
        case k_ASin: str = "asin("; return 5;
        case k_Cos: str = "cos("; return 4;
        case k_ACos: str = "acos("; return 5;
        case k_Tan: str = "tan("; return 4;
        case k_ATan: str = "atan("; return 5;
        case k_Square: str = "^2"; return 2;
        case k_Sqrt: str = "√("; return 2;
        case k_Ln: str = "ln("; return 3;
        case k_Exp: str = "e^"; return 2;
        case k_Log: str = "log("; return 4;
        case k_ALog: str = "10^"; return 3;
        case k_Ans: str = "Ans"; return 3;
        case k_Colon: str = ":"; return 1;
        case k_NDeriv: str = "nDeriv("; return 7;
        case k_FnInt: str = "fnInt("; return 6;
        case k_Root: str = "root("; return 5;
        case k_Quest: str = "?"; return 1;
        case k_Quote: str = "\""; return 1;
        case k_Theta: str = "θ"; return 1;
        case k_SinH: str = "sinh("; return 5;
        case k_CosH: str = "cosh("; return 5;
        case k_TanH: str = "tanh("; return 5;
        case k_ASinH: str = "asinh("; return 6;
        case k_ACosH: str = "acosh("; return 6;
        case k_ATanH: str = "atanh("; return 6;
        case k_LBrace: str = "{"; return 1;
        case k_RBrace: str = "}"; return 1;
        case k_I: str = "i"; return 1;
        
        case k_Abs: str = "abs("; return 4;
        case 
    }
}