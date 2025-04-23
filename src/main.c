/**
 * @file main.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Entry point for Numeric
 * @version 0.1
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

int main(void)
{
    #include "ti/screen.h"
    #include "io/token.h"
    #include "ti/getcsc.h"
    os_ClrHome();
    os_PutStrFull("'`");
    for (int i = 0; i <= 0xFF; ++i)
    {
        os_PutStrFull(STR(i));
        while (!os_GetCSC());
    }

    // #include <io/read.h>
    // os_ClrHome();
    // os_SetCursorPos(1, 1);
    // uint16_t* test = readString();
    // // startupScreen();
    // // methodMenu();
    // free(test);
    // return 0;
}
