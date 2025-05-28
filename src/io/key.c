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

#include <io/symbols.h>

#include <ti/getcsc.h>
#include <ti/getkey.h>

#include <string.h>

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
        default: return ' ';
    }
}

int getKeyStringKey(uint16_t key, char* str)
{
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
        case k_Add:     strcpy(str, "+");             return 1;
        case k_Sub:     strcpy(str, "-");             return 1;
        case k_Mul:     strcpy(str, "*");             return 1;
        case k_Div:     strcpy(str, "/");             return 1;
        case k_Expon:   strcpy(str, "^");             return 1;
        case k_LParen:  strcpy(str, "(");             return 1;
        case k_RParen:  strcpy(str, ")");             return 1;
        case k_LBrack:  strcpy(str, STR(LBRACK));     return 1;
        case k_RBrack:  strcpy(str, "]");             return 1;
        case k_Comma:   strcpy(str, ",");             return 1;
        case k_Chs:     strcpy(str, STR(CHS));        return 1;
        case k_DecPnt:  strcpy(str, ".");             return 1;
        case k_EE:      strcpy(str, STR(EE));         return 1;
        case k_Space:   strcpy(str, " ");             return 1;
        case k_Varx:    strcpy(str, "X");             return 1;
        case k_Pi:      strcpy(str, STR(LPI));        return 1;
        case k_Inv:     strcpy(str, STR(INV));        return 1;
        case k_Sin:     strcpy(str, "sin(");          return 4;
        case k_ASin:    strcpy(str, "asin(");         return 5;
        case k_Cos:     strcpy(str, "cos(");          return 4;
        case k_ACos:    strcpy(str, "acos(");         return 5;
        case k_Tan:     strcpy(str, "tan(");          return 4;
        case k_ATan:    strcpy(str, "atan(");         return 5;
        case k_Square:  strcpy(str, STR(SQUARE));     return 1;
        case k_Sqrt:    strcpy(str, STR(SQRT, '('));  return 2;
        case k_Ln:      strcpy(str, "ln(");           return 3;
        case k_Exp:     strcpy(str, STR(E, '^'));     return 2;
        case k_Log:     strcpy(str, "log(");          return 4;
        case k_ALog:    strcpy(str, STR(SUB10, '^')); return 2;
        case k_Ans:     strcpy(str, "Ans");           return 3;
        case k_Colon:   strcpy(str, ":");             return 1;
        case k_NDeriv:  strcpy(str, "nDeriv(");       return 7;
        case k_FnInt:   strcpy(str, "fnInt(");        return 6;
        case k_Root:    strcpy(str, "root(");         return 5;
        case k_Quest:   strcpy(str, "?");             return 1;
        case k_Quote:   strcpy(str, "\"");            return 1;
        case k_Theta:   strcpy(str, STR(THETA));      return 1;
        case k_SinH:    strcpy(str, "sinh(");         return 5;
        case k_CosH:    strcpy(str, "cosh(");         return 5;
        case k_TanH:    strcpy(str, "tanh(");         return 5;
        case k_ASinH:   strcpy(str, "asinh(");        return 6;
        case k_ACosH:   strcpy(str, "acosh(");        return 6;
        case k_ATanH:   strcpy(str, "atanh(");        return 6;
        case k_LBrace:  strcpy(str, "{");             return 1;
        case k_RBrace:  strcpy(str, "}");             return 1;
        case k_I:       strcpy(str, STR(I));          return 1;
        case k_CONSTeA: strcpy(str, STR(E));          return 1;
        
        case k_Abs: strcpy(str, "abs("); return 4;

        case k_Underscore: strcpy(str, "_"); return 1;

        default: str[0] = '\0'; return -1;
    }
}