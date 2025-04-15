/**
 * @file util.cpp
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements utility functions
 * @version 0.2
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

#include "util.h"

#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/real.h>

void startupScreen(void)
{
    os_ClrHome();

    os_PutStrFull("------ NUMERIC v0.1 ------");
    os_PutStrFull("    Copyright (c) 2025");
    os_NewLine();
    os_PutStrFull("       Luke Houston");
    os_NewLine();
    os_NewLine();
    os_PutStrFull("The ultimate numerical");
    os_NewLine();
    os_PutStrFull("differential equation");
    os_NewLine();
    os_PutStrFull("solver for the TI-84+ CE");
    os_NewLine();
    os_NewLine();
    os_PutStrFull("Press any key to continue");

    while (!os_GetCSC()) {}
}

enum Methods methodMenu(void)
{
    #define METHODS_COUNT 6
    const char* methods[METHODS_COUNT] =
    {
        "Euler",
        "Improved Euler",
        "RK4",
        "Adams-Bashforth-Moulton",
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
        os_PutStrFull(title);

        for (int i = 0; i < count; ++i)
        {
            os_SetCursorPos(i + 1, 0);

            if (i == selected) { os_PutStrFull(">"); }
            else { os_PutStrFull(" "); }

            char option_str[4] = {0};
            option_str[0] = '1' + i;
            option_str[1] = ':';
            option_str[2] = ' ';
            os_PutStrFull(option_str);
            os_PutStrFull(options[i]);
        }

        while (!(key = os_GetCSC()));

        // Arrow key navigation
        if (key == sk_Up) { selected = (selected - 1 + selected) % count; }
        else if (key == sk_Down) { selected = (selected + 1) % count; }
        else if (key == sk_2nd || key == sk_Enter) { return selected; }
        else if (getKeyNumber(key) != -1 && getKeyNumber(key) <= count)
        {
            return getKeyNumber(key) - 1;
        }
    }
}

int getKeyNumber(sk_key_t key)
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
