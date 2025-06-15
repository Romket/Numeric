/**
 * @file menu.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Declares functions for creating menus
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

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

typedef struct Tab
{
    const char* Name;
    const char** Options;
    int Count;
} Tab;

typedef struct Selected
{
    int SelectedTab;
    int SelectedOption;
} Selected;

typedef struct Menu
{
    const char* Title;
    bool ShowTitle;
    const Tab* Tabs;
    int TabCount;
} Menu;

/**
 * @brief Draws a menu
 * 
 * @param title The menu title
 * @param tabs A list of tabs to display
 * @param tabCount The number of Tabs
 * @return Selected The index of the selected tab and option
 *
 * @note Tab name will not be displayed with only one tab
 * @note Returns {-1, -1} if the user quits
 */
Selected drawMenu(const Menu* info);

#ifdef __cplusplus
}
#endif
