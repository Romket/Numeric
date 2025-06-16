/**
 * @file mathmenu.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements a custom version of the TI-83/84's 'math' menu
 * @version 0.1
 * @date 2025-06-16
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

#include <mathmenu.h>

#include <io/symbols.h>
#include <menu.h>

#include <ti/getkey.h>
#include <ti/screen.h>

uint16_t mathMenu()
{
    os_DisableCursor();

    uint16_t menuOptions[3][9] = {
        {k_Cube, k_CbRt, k_XRoot, k_SinH, k_CosH, k_TanH, k_ASinH, k_ACosH,
             k_ATanH},

        {k_Abs, k_XFactorial},
        {k_Underscore}
    };

    const char* math[] = {
        STR(CUBE),
        STR(CUBE, SQRT, '('),
        STR(SUPERX, SQRT, '('),
        "sinh(",
        "cosh(",
        "tanh(",
        "asinh(",
        "acosh(",
        "atanh("
    };

    const char* num[] = {
        "abs(",
        "!"
    };

    const char* var[] = {
        "_"
    };

    Tab tabs[3] = {
        {"MATH", math, 9},
        {"NUM", num, 2},
        {"VAR", var, 1}
    };

    Menu menuInfo = {
        "MathMenu",
        false,
        tabs,
        3
    };

    const Selected result = drawMenu(&menuInfo);

    if (result.SelectedOption == -1) return 0;

    return menuOptions[result.SelectedTab][result.SelectedOption];
}
