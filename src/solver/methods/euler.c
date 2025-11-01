/**
 * @file euler.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Euler's method implementation
 * @version 0.1
 * @date 2025-09-12
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

#include <solver/methods/euler.h>

#include <io/print.h>
#include <solver/geteq.h>

#include <ti/getcsc.h>
#include <ti/screen.h>

void euler()
{
    bool status = true;
    DiffEq de = getDiffEq(&status);
    if (!status)
    {
        os_ClrHome();
        printStr("Invalid differential equation entered");
        while (!os_GetCSC());
        return;
    }

    // TODO: handle negative step
    while (os_RealToFloat(&de.Independent.Value) < de.End)
    {
        for (int i = 0; i < de.SystemSize; ++i)
        {
            if (!evalEq(&de.Equations[i]))
            {
                printStr("Failed to evaluate differential equation");
                return;
            }
        }
    }
}