/**
 * @file util.cpp
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements utility functions
 * @version 0.3
 * @date 2025-04-13
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

#include <util.h>

#include <io/key.h>
#include <io/print.h>
#include <io/symbols.h>
#include <menu.h>

#include <solver/methods/abm.h>
#include <solver/methods/euler.h>
#include <solver/methods/improved_euler.h>
#include <solver/methods/rk4.h>

#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/real.h>
#include <ti/screen.h>

void startupScreen()
{
    os_ClrHome();

    printStr("------ NUMERIC v0.1 ------\n");
    printStr("    Copyright (c) 2025\n");
    printStr("       Luke Houston\n\n");

    printStr("The ultimate numerical\n");
    printStr("differential equation\n");
    printStr("solver for the TI-84+ CE\n\n");

    printStr("Press any key to continue\n");
    printStr("--------------------------");

    while (!os_GetCSC());
}

void methodMenu()
{
    const char* singleStep[] = {
        "Euler",
        "Improved Euler",
        "RK4"
    };

    const char* multiStep[] = {
        "Adams-Bashforth-Moulton"
    };

    const char* more[] = {
        "Custom RK"
    };

    Tab tabs[3] = {
        {"1-Step", singleStep, 3},
        {"Multi-Step", multiStep, 1},
        {"More", more, 1}
    };

    Menu menuInfo = {"Methods Menu", false, tabs, 3};

    Selected choice = drawMenu(&menuInfo);

    if (choice.SelectedTab == 0)
    {
        switch (choice.SelectedOption)
        {
            case 0:
                euler();
            case 1:
                impEuler();
            case 3:
                rk4();
        }
    }
    else if (choice.SelectedTab == 1)
    {
        switch (choice.SelectedOption)
        {
            case 0:
                abm();
        }
    }
    else if (choice.SelectedTab == 2)
    {
        switch (choice.SelectedOption)
        {
            case 0:
                break; // TODO
        }
    }
}

bool strToNum(uint16_t* str, int len, double* result)
{
    *result = 0.0;
    double place = 1.0;
    bool negative = false;

    if (str[0] == k_Chs) negative = true;

    for (int i = 0 + negative; i < len; ++i)
    {
        if (place == 1.0 && str[i] != k_DecPnt)
        {
            *result *= 10.0;
            *result += str[i] - k_0;
        }
        else if (str[i] == k_DecPnt && place != 1.0) return false;
        else
        {
            if (str[i] != k_DecPnt) *result += (double)(str[i] - k_0) * place;
            place /= 10.0;
        }
    }

    *result *= negative ? -1.0 : 1.0;

    return true;
}

int strToInt(uint16_t* str, int len)
{
    int result = 0;

    for (int i = 0; i < len; ++i)
    {
        result *= 10;
        result += str[i] - k_0;
    }

    return result;
}
