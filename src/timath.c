/**
 * @file timath.cpp
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Implements math functions
 * @version 0.1
 * @date 2025-04-24
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

#include <timath.h>

#include <util.h>
#include <io/iodefs.h>

#include <ti/getkey.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

double evaluate(struct EquationElement* eq, int eqLen, bool* status,
                struct Variable* vars, int numVars)
{
    double stack[MAX_STRING_LEN] = {0.0};
    int top = 0;

    *status = true;

    for (int i = 0; i < eqLen; ++i)
    {
        switch (eq[i].Type)
        {
            case number:
                stack[top++] = eq[i].Number;
                break;
            case variable:
                for (int j = 0; j < numVars; ++j)
                {
                    if (vars[j].Name == eq[i].VarName)
                    {
                        stack[top++] = vars[j].Value;
                        break;
                    }
                }
                *status = false;
                return 0.0;
            // TODO: Implement constants like e, pi, etc.
            // TODO: Maybe not as a separate ElementType, but as a Number
            // case constant:
            //     stack[top++] = toConstant(eq[i].ConstName);
            case operation:
            {
                double a = stack[--top];
                double b = stack[top - 1];
                double result = ex(a, b, eq[i].Operation, &top);
                if (result == NAN)
                {
                    *status = false;
                    return 0.0;
                }
                stack[top++] = result;
                break;
            }
        }
    }

    return stack[0];
}

double ex(double a, double b, uint16_t op, int* top)
{
    switch (op)
    {
        case k_Add:   --*top; return a + b;
        case k_Sub:   --*top; return a - b;
        case k_Mul:   --*top; return a * b;
        case k_Div:   --*top; return a / b;
        case k_Expon: --*top; return pow(a, b);
        case k_Sin:           return sin(a);
        case k_ASin:          return asin(a);
        case k_Cos:           return cos(a);
        case k_ACos:          return acos(a);
        case k_Tan:           return tan(a);
        case k_ATan:          return atan(a);
        case k_Sqrt:          return sqrt(a);
        case k_Ln:            return log(a);
        // TODO: handle different log bases, different roots, etc.
        case k_SinH:          return sinh(a);
        case k_CosH:          return cosh(a);
        case k_TanH:          return tanh(a);
        case k_ASinH:         return asinh(a);
        case k_ACosH:         return acosh(a);
        case k_ATanH:         return atanh(a);
        case k_Abs:           return a < 0 ? -1.0 * a : a;
        default:              return NAN;
    }
}

int parseToPostfix(uint16_t* eq, int len, struct EquationElement** result)
{
    if (*result != NULL) free(*result);
    *result = malloc((len + 1) * sizeof(uint16_t));
    if (*result == NULL) return -1;

    uint16_t stack[len];
    int j = 0;
    int top = -1;

    bool canImpMultLast = false;

    for (int i = 0; i < len; ++i)
    {
        // If the scanned character is an operand, add it to the output string.
        if ((eq[i] >= k_0 && eq[i] <= k_9) || eq[i] == k_DecPnt)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    struct EquationElement el = {
                        operation,
                        ' ',
                        0,
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            uint16_t str[len];
            int k = 0;
            memset(str, k_0, len * sizeof(uint16_t));

            while (((eq[i] >= k_0 && eq[i] <= k_9) || eq[i] == k_DecPnt)
                   && i < len)
            {
                str[k] = eq[i];
                ++i;
                ++k;
            }

            double num;
            if (!strToNum(str, k, &num)) return -1;

            struct EquationElement el = {
                number,
                ' ',
                num,
                0
            };
            (*result)[j++] = el;
            canImpMultLast = true;

            --i;
        }

        // Same logic for variables as for numbers
        else if ((eq[i] >= k_CapA && eq[i] <= k_CapZ) || eq[i] == k_Varx ||
                 eq[i] == k_Theta)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    struct EquationElement el = {
                        operation,
                        ' ',
                        0,
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            struct EquationElement el = {
                variable,
                eq[i],
                0,
                0
            };
            (*result)[j++] = el;
            canImpMultLast = true;
        }

        // If the scanned character is ‘(‘, push it to the stack.
        else if (eq[i] == k_LParen)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    struct EquationElement el = {
                        operation,
                        ' ',
                        0,
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }
            stack[++top] = k_LParen;
            canImpMultLast = false;
        }

        // If the scanned character is ‘)’, pop and add to the output string
        // from the stack until an ‘(‘ is encountered.
        else if (eq[i] == k_RParen)
        {
            while (top != -1 && stack[top] != k_LParen)
            {
                struct EquationElement el = {
                    operation,
                    ' ',
                    0,
                    stack[top--]
                };
                (*result)[j++] = el;
            }
            top--;

            canImpMultLast = true;
        }

        // If an operator is scanned
        else
        {
            int pr = prec(eq[i]);
            if (pr == -1) return -1;

            while (top != -1 && pr <= prec(stack[top]))
            {
                struct EquationElement el = {
                    operation,
                    ' ',
                    0,
                    stack[top--]
                };
                (*result)[j++] = el;
            }
            stack[++top] = eq[i];
            if (pr == 5) stack[++top] = k_LParen; // sin, cos, etc. has a '('

            canImpMultLast = false;
        }
    }

    // Pop all the remaining elements from the stack
    while (top != -1)
    {
        struct EquationElement el = {
            operation,
            ' ',
            0,
            stack[top--]
        };
        (*result)[j++] = el;
    }

    return j;
}

int prec(uint16_t c)
{
    switch (c)
    {
        case k_Sin:
        case k_ASin:
        case k_Cos:
        case k_ACos:
        case k_Tan:
        case k_ATan:
        case k_Sqrt:
        case k_Ln:
        case k_Log:
        case k_ALog:
        case k_Root:
        case k_SinH:
        case k_CosH:
        case k_TanH:
        case k_ASinH:
        case k_ACosH:
        case k_ATanH:
            return 5;
        
        case k_Expon:
        case k_EE:
        case k_Inv:
        case k_Square:
            return 4;

        // prec 3 is for implicit multiplication

        case k_Div:
        case k_Mul:
            return 2;
        
        case k_Add:
        case k_Sub:
            return 1;
        
        default:
            return -1;
    }
}
