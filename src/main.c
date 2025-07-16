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
    #include <ti/screen.h>
    #include <io/read.h>
    #include <timath.h>
    #include <io/print.h>
    #include <ti/getkey.h>
    #include <io/key.h>
    #include <ti/getcsc.h>
    os_ClrHome();
    int len = 0;
    uint16_t* test = readString(&len);

    Expression postfix = parseToPostfix(test, len);
    if (postfix.Length == -1)
    {
        os_ClrHome();
        printStr("Error in parsing to postfix");
        while (!os_GetCSC());
        return 1;
    }
    bool status;
    for (int i = 0; i < postfix.Length; ++i)
    {
        if (postfix.Tokens[i].Type == number)
        {
            printReal(postfix.Tokens[i].Number);
        }
        else if (postfix.Tokens[i].Type == variable)
        {
            printChar(postfix.Tokens[i].VarName);
            if (postfix.Tokens[i].Subscript != -1)
            {
                printIntAsSubscript(postfix.Tokens[i].Subscript);
            }
        }
        else
        {
            char str[MAX_STRING_LEN] = {0};
            getKeyStringKey(postfix.Tokens[i].Operation, str);
            printStr(str);
        }
    }
    printChar('\n');
    Variable vars[3] = {
        {'X', -1, os_Int24ToReal(2)},
        {'X', 0, os_Int24ToReal(0)},
        {'X', 10, os_FloatToReal(3.3)}
    };

    real_t result = evaluate(&postfix, &status, vars, 3);
    if (!status)
    {
        os_ClrHome();
        printStr("Error in evaluating postfix expression\n");
        while (!os_GetCSC());
        return 1;
    }

    printReal(result);

    while (!os_GetCSC());
    // startupScreen();
    // methodMenu();
    return 0;
}
