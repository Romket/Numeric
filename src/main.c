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

#include "io/iodefs.h"
#include "ti/getcsc.h"
#include <string.h>
#include <util.h>

int main(void)
{
    #include <ti/screen.h>
    #include <io/read.h>
    #include <stdlib.h>
    #include <timath.h>
    #include <io/print.h>
    #include <ti/getkey.h>
    #include <io/key.h>
    os_ClrHome();
    uint16_t* test = NULL;
    int len = readString(&test);
    struct EquationElement* postfix = NULL;
    int postfixLen = parseToPostfix(test, len, &postfix);
    if (postfixLen == -1)
    {
        os_ClrHome();
        printStr("Error in parsing to postfix");
        while (!os_GetCSC());
        return 1;
    }
    bool status;
    for (int i = 0; i < postfixLen; ++i)
    {
        if (postfix[i].Type == number)
        {
            printDouble(postfix[i].Number);
        }
        else if (postfix[i].Type == variable)
        {
            char str[MAX_STRING_LEN] = {0};
            getKeyStringKey(postfix[i].VarName, str);
            printStr(str);
        }
        else
        {
            char str[MAX_STRING_LEN] = {0};
            getKeyStringKey(postfix[i].Operation, str);
            printStr(str);
        }
    }
    printChar('\n');
    double result = evaluate(postfix, postfixLen, &status, NULL, 0);
    if (!status)
    {
        os_ClrHome();
        printStr("Error in evaluating postfix expression");
        while (!os_GetCSC());
        return 1;
    }
    printDouble(result);
    while (!os_GetCSC());
    // startupScreen();
    // methodMenu();
    free(test);
    free(postfix);
    return 0;
}
