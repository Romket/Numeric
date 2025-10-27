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
#include <io/symbols.h>
#include <timath.h>

#include <ti/screen.h>

DiffEq getDiffEq(bool* status)
{
    os_ClrHome();
    
    DiffEq de;
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

    printChar(de.SystemSize == 1 ? 'X' : 'T');
    printStr("i=");
    Variable initialXCond = {
        de.SystemSize == 1 ? 'X' : 'T',
        -1,
        0,
        os_FloatToReal(readFloat())
    };
    de.Dependent = initialXCond;

    printChar(de.SystemSize == 1 ? 'X' : 'T');
    printStr("f=");
    de.End = readFloat();

    printStr("h=");
    de.Step = readFloat();

    return de;
}

bool getEquation(DiffEq* de, int eqId, bool system)
{
    de->Orders[eqId] = readInt();

    char prompt[MAX_STRING_LEN] = {0};
    int promptID = system ? 2 : 1;

    prompt[0] = system ? 'X' : 'Y';
    prompt[1] = system ? SUB0 + eqId + 1 : 0;

    char varName[3] = {0};
    varName[0] = system ? 'X' : 'Y';
    varName[1] = system ? SUB0 + eqId + 1 : 0;

    for (int i = 0; i < de->Orders[eqId]; ++i)
    {
        prompt[promptID] = '\'';
        ++promptID;
    }
    
    prompt[promptID] = '=';

    int len = 0;
    uint16_t* eqStr = readString(&len, prompt);

    Expression expr = parseToPostfix(eqStr, len);
    if (len <= 0) return false;

    Variable y = {
        prompt[0],
        system ? 1 + eqId : -1,
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
        printStr("i=");
        Variable initialYCond = {
            varName[0],
            system ? varName[1] : -1,
            i,
            os_FloatToReal(readFloat())
        };
        varlist[nvars++] = initialYCond;
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
