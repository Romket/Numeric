/**
 * @file menu.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements functions for creating menus
 * @version 0.1
 * @date 2025-05-28
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

#include <menu.h>

#include <io/print.h>
#include <io/symbols.h>

#include <ti/getkey.h>
#include <ti/screen.h>

Selected drawMenu(const Menu* info)
{
    Selected current = {0, 0};

    int top = 0;

    while (true)
    {
        os_ClrHome();
        if (info->ShowTitle)
        {
            printStr(info->Title);
            os_NewLine();
        }

        // while is used instead of if to handle the selected option wrapping
        // down
        while (current.SelectedOption >= top + SCREEN_HEIGHT_LINES -
            (info->ShowTitle + (info->TabCount > 1)))
        {
            ++top;
        }

        while (current.SelectedOption < top)
        {
            --top;
        }
        
        if (info->TabCount > 1)
        {
            for (int i = 0; i < info->TabCount; ++i)
            {
                unsigned int x, y;
                os_GetCursorPos(&y, &x);

                if (i == current.SelectedTab)
                {
                    printInvStr(info->Tabs[i].Name);
                }
                else
                {
                    printStr(info->Tabs[i].Name);
                }

                printChar(' ');
            }
        }

        for (int i = 0; i < info->Tabs[current.SelectedTab].Count; ++i)
        {
            if (i + info->ShowTitle + (info->TabCount > 1) >=
                SCREEN_HEIGHT_LINES)
            {
                break;
            }

            os_NewLine();

            char num[3] = {0};

            if (i + top <= 8) num[0] = (i + top) + 1 + '0';
            else if (i + top == 9) num[0] = '0';
            else if (i + top <= 35) num[0] = (i + top) - 10 + 'A';
            else num[0] = ' ';

            if (i == 0 && top > 0) num[1] = UPLIGHT;
            else if (i + info->ShowTitle + (info->TabCount > 1) + 1 ==
                     SCREEN_HEIGHT_LINES && i + top <
                        info->Tabs[current.SelectedTab].Count - 1)
            {
                num[1] = DOWNLIGHT;
            }
            else num[1] = ':';

            if (i + top == current.SelectedOption) printInvStr(num);
            else printStr(num);

            printStr(info->Tabs[current.SelectedTab].Options[i + top]);
        }

        uint16_t key = os_GetKey();

        if (key == k_Right)
        {
            current.SelectedTab = (current.SelectedTab + 1) % info->TabCount;
            current.SelectedOption = 0;
            top = 0;
        }
        else if (key == k_Left)
        {
            current.SelectedTab =
                (current.SelectedTab - 1 + info->TabCount) % info->TabCount;
            current.SelectedOption = 0;
            top = 0;
        }
        else if (key == k_Down)
        {
            current.SelectedOption = (current.SelectedOption + 1) %
                                     info->Tabs[current.SelectedTab].Count;
        }
        else if (key == k_Up)
        {
            current.SelectedOption = (current.SelectedOption - 1 +
                                      info->Tabs[current.SelectedTab].Count) %
                                     info->Tabs[current.SelectedTab].Count;
        }
        else if ((key >= k_0 && key <= k_9) || (key >= k_CapA && key <= k_CapZ))
        {
            if ((key >= k_1 && key <= k_9) &&
                info->Tabs[current.SelectedTab].Count >= key - k_0)
            {
                current.SelectedOption = key - k_1;
                return current;
            }
            else if (key == k_0 && info->Tabs[current.SelectedTab].Count >= 10)
            {
                current.SelectedOption = 9;
                return current;
            }
            else if ((key >= k_CapA && key <= k_CapZ) &&
                info->Tabs[current.SelectedTab].Count >= key - k_CapA + 10)
            {
                current.SelectedOption = key - k_CapA + 9;
                return current;
            }
        }
        else if (key == k_Enter) return current;
        else if (key == k_Quit)
        {
            current.SelectedOption = -1;
            current.SelectedTab = -1;
            return current;
        }
    }
}