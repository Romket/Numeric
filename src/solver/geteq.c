/**
 * @file geteq.c
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Defines functions to get the equations to solve from the user
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

#include <solver/geteq.h>

#include <io/print.h>
#include <io/read.h>
#include <timath.h>

#include <ti/screen.h>

DiffEq getDiffEq(bool* status)
{
    os_ClrHome();
    
    static DiffEq de;
    *status = true;

    printStr("Number of Equations: ");
    de.SystemSize = readInt();

    if (de.SystemSize < 1)
    {
        *status = false;
        return de;
    }
    
    if (de.SystemSize == 1)
    {
        printStr("Order of equation: ");
        
        if (!getEquation(&de, 0, false))
        {
            *status = false;
            return de;
        }
    }
    else
    {
        for (int i = 0; i < de.SystemSize; ++i)
        {
            printStr("Order of equation ");
            printInt(i + 1);
            printStr(": ");

            if (!getEquation(&de, i, true))
            {
                *status = false;
                return de;
            }
        }
    }

    return de;
}

bool getEquation(DiffEq* de, int eqId, bool system)
{
    de->Orders[eqId] = readInt();

    char varName[3] = {0};
    varName[0] = system ? 'X' : 'Y';
    varName[1] = system ? '1' + eqId : 0;

    printStr(varName);
    for (int i = 0; i < de->Orders[eqId]; ++i) printChar('\'');
    printChar('=');

    int len = 0;
    uint16_t* eqStr = readString(&len);

    Expression expr = parseToPostfix(eqStr, len);
    if (len <= 0) return false;

    Variable y = {
        varName[0],
        system ? '1' + eqId : -1,
        de->Orders[eqId],
        {0}
    };

    Variable varlist[MAX_SYSTEM_SIZE] = {{' ', -1, 0, {0}}};

    int nvars = 0;
    for (int i = 0; i < len; ++i)
    {
        if (expr.Tokens[i].Type == variable)
        {
            Token tok = expr.Tokens[i];
            if (tok.Subscript > de->SystemSize || tok.Deriv >= de->Orders[eqId])
                return false;

            Variable var = {
                tok.VarName,
                tok.Subscript,
                tok.Deriv,
                {0}
            };
            varlist[nvars++] = var;
        }
    }

    for (int i = 0; i < de->Orders[eqId]; ++i)
    {
        printStr(varName);
        for (int j = 0; j < i; ++j) printChar('\'');
        printChar('=');
        Variable initialCond = {
            varName[0],
            system ? varName[1] : -1,
            i,
            os_FloatToReal(readFloat())
        };
        varlist[nvars++] = initialCond;
    }

    Equation eq = {y, varlist, nvars, expr, equal};

    de->Equations[eqId] = eq;

    return true;
}

bool evalEq(Equation* eq)
{
    bool status;
    eq->Var.Value = evaluate(&eq->Exp, &status, eq->VarList, eq->NVars);

    return status;
}
