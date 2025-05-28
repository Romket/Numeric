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

#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/real.h>
#include <ti/screen.h>

void startupScreen(void)
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

enum Methods methodMenu(void)
{
    #define METHODS_COUNT 6
    const char* methods[METHODS_COUNT] =
    {
        "Euler",
        "Improved Euler",
        "RK4",
        "AdamsBashforthMoulton",
        "More",
        "Quit"
    };

    int choice = drawMenu("Main Menu", methods, METHODS_COUNT);

    enum Methods selectedMethod;
    // Yes yes magic numbers bad, but lightweight
    switch (choice)
    {
        case 0:
            selectedMethod = mEuler;
            return selectedMethod;
        case 1:
            selectedMethod = mImpEuler;
            return selectedMethod;
        case 2:
            selectedMethod = mRK4;
            return selectedMethod;
        case 3:
            selectedMethod = mABM;
            return selectedMethod;
        case 4:
        {
            #define MORE_MENU_COUNT 3
            const char* more_menu[MORE_MENU_COUNT] =
            {
                "Custom RK",
                "Back",
                "Quit"
            };

            int more_choice = drawMenu("Main Menu", more_menu, MORE_MENU_COUNT);

            switch (more_choice)
            {
                case 0:
                    selectedMethod = mCustomRK;
                    return selectedMethod;
                case 1:
                    return methodMenu();
                default:
                    selectedMethod = mQuit;
                    return selectedMethod;
            }
        }
        default:
            selectedMethod = mQuit;
            return selectedMethod;
    }
}

int drawMenu(const char* title, const char** options, int count)
{
    int selected = 0;
    sk_key_t key;

    while (true)
    {
        os_ClrHome();
        os_SetCursorPos(0, 0);
        printStr(title);
        printChar('\n');

        for (int i = 0; i < count; ++i)
        {
            if (i == selected) { printChar(SEL); }
            else { printChar(' '); }

            char optionStr[4] = {0};
            optionStr[0] = '1' + i;
            optionStr[1] = ':';
            optionStr[2] = ' ';
            printStr(optionStr);
            printStr(options[i]);
            printChar('\n');
        }

        while (!(key = os_GetCSC()));

        // Arrow key navigation
        if (key == sk_Up) { selected = (selected - 1 + count) % count; }
        else if (key == sk_Down) { selected = (selected + 1) % count; }
        else if (key == sk_2nd || key == sk_Enter) { return selected; }
        else if (getKeyNumberCSC(key) != -1 && getKeyNumberCSC(key) <= count)
        {
            return getKeyNumberCSC(key) - 1;
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
