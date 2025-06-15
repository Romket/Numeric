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
#include <io/key.h>

#include <ti/getkey.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

real_t evaluate(Expression expr, int len, bool* status, Variable* vars,
                int nVars)
{
    real_t stack[MAX_STRING_LEN] = {{0}};
    int top = 0;

    *status = true;

    for (int i = 0; i < len; ++i)
    {
        Token tok = expr[i];

        switch (tok.Type)
        {
            case number:
                stack[top++] = expr[i].Number;
                break;
            case variable:
            {
                bool found = false;
                for (int j = 0; j < nVars; ++j)
                {
                    if (vars[j].Name == tok.VarName &&
                        vars[j].Subscript == tok.Subscript)
                    {
                        found = true;
                        stack[top++] = vars[j].Value;
                        break;
                    }
                }
                if (!found)
                {
                    *status = false;
                    return os_Int24ToReal(0);
                }
                break;
            }
            case operation:
            {
                real_t second = stack[--top];
                real_t first = stack[top - 1];
                bool exStatus = true;
                real_t result = ex(first, second, tok.Operation, &top,
                                   &exStatus);
                if (!exStatus)
                {
                    *status = false;
                    return os_Int24ToReal(0);
                }
                if (top < 0)
                {
                    *status = false;
                    return os_Int24ToReal(0);
                }
                stack[top++] = result;
                break;
            }
        }
    }

    return stack[0];
}

real_t ex(real_t first, real_t second, uint16_t op, int* top, bool* status)
{
    switch (op)
    {
        // prec 5
        case k_Sin:           return os_RealSinRad(&second);
        case k_ASin:          return os_RealAsinRad(&second);
        case k_Cos:           return os_RealCosRad(&second);
        case k_ACos:          return os_RealAcosRad(&second);
        case k_Tan:           return os_RealTanRad(&second);
        case k_ATan:          return os_RealAtanRad(&second);
        case k_Sqrt:          return os_RealSqrt(&second);
        case k_Ln:            return os_RealLog(&second);
        // TODO: handle different log bases, different roots, etc.
        case k_SinH:          return realSinhRad(&second);
        case k_CosH:          return realCoshRad(&second);
        case k_TanH:          return realTanhRad(&second);
        case k_ASinH:         return realAsinhRad(&second);
        case k_ACosH:         return realAcoshRad(&second);
        case k_ATanH:         return realAtanhRad(&second);
        case k_Abs:           return realAbs(&second);

        // prec 4
        case k_Expon: --*top; return os_RealPow(&first, &second);
        case k_Inv:           return os_RealInv(&second);
        case k_Square:        return os_RealMul(&second, &second);
        case k_EE:    --*top; return realEE(&first, &second);

        // prec 3 (implicit multiplication)
        // prec 2
        case k_Mul:   --*top; return os_RealMul(&first, &second);
        case k_Div:   --*top; return os_RealDiv(&first, &second);
        case k_Chs:           return os_RealNeg(&second);

        // prec 1
        case k_Add:   --*top; return os_RealAdd(&first, &second);
        case k_Sub:   --*top; return os_RealSub(&first, &second);

        default: *status = false; return os_Int24ToReal(0);
    }
}

int parseToPostfix(uint16_t* in, int len, Expression* result)
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
        uint16_t c = in[i];

        // If the scanned character is a separator, go to the next character
        if (c == k_Space || c == k_Comma) continue;

        // If the scanned character is an operand, add it to the output string.
        if ((c >= k_0 && c <= k_9) || c == k_DecPnt)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    Token el = {
                        operation,
                        ' ',
                        -1,
                        {0},
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            char str[len];
            int k = 0;
            memset(str, 0, len);

            while (((c >= k_0 && c <= k_9) || c == k_DecPnt) && i < len)
            {
                if (c >= k_0 && c <= k_9) str[k] = (c - k_0) + '0';
                else str[k] = '.';

                ++i;
                ++k;
                c = in[i];
            }

            char* end = &str[k - 1];

            Token el = {
                number,
                ' ',
                -1,
                os_StrToReal(str, &end),
                0
            };
            (*result)[j++] = el;
            canImpMultLast = true;

            --i;
        }

        // Same logic for variables as for numbers
        else if ((c >= k_CapA && c <= k_CapZ) || c == k_Varx || c == k_Theta)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    Token el = {
                        operation,
                        ' ',
                        -1,
                        {0},
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            char varName;
            if (c >= k_CapA && c <= k_CapZ) varName = (c - k_CapA) + 'A';
            else if (c == k_Varx) varName = 'X';
            else if (c == k_Theta) varName = 't';

            int subscript = -1;
            if (i + 1 < len && in[i + 1] == k_Underscore)
            {
                i += 2;

                uint16_t str[len];
                int k = 0;
                memset(str, 0, len);

                c = in[i];
                while (i < len && c >= k_0 && c <= k_9)
                {
                    str[k] = c;
                    
                    ++i;
                    ++k;
                    c = in[i];
                }

                subscript = strToInt(str, k);

                --i;
            } 

            Token el = {
                variable,
                varName,
                subscript,
                {0},
                0
            };
            (*result)[j++] = el;
            canImpMultLast = true;
        }

        // Constants
        else if (c == k_Pi || c == k_CONSTeA)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    Token el = {
                        operation,
                        ' ',
                        -1,
                        {0},
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            Token el = {
                number,
                ' ',
                -1,
                os_FloatToReal(c == k_Pi ? M_PI : M_E), // Only pi and e are
                // currently supported constants
                0
            };

            (*result)[j++] = el;
            canImpMultLast = true;
        }

        // If the scanned character is ‘(‘, push it to the stack.
        else if (c == k_LParen)
        {
            if (canImpMultLast)
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    Token el = {
                        operation,
                        ' ',
                        -1,
                        {0},
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
        else if (c == k_RParen)
        {
            while (top != -1 && stack[top] != k_LParen)
            {
                Token el = {
                    operation,
                    ' ',
                    -1,
                    {0},
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
            int pr = prec(c);
            if (pr == -1) return -1;

            if (pr == 5 && canImpMultLast) // e.g. 5sin(x) is valid
            {
                while (top != -1 && 3 <= prec(stack[top]))
                {
                    Token el = {
                        operation,
                        ' ',
                        -1,
                        {0},
                        stack[top--]
                    };
                    (*result)[j++] = el;
                }
                stack[++top] = k_Mul;
            }

            while (top != -1 && pr <= prec(stack[top]))
            {
                Token el = {
                    operation,
                    ' ',
                    -1,
                    {0},
                    stack[top--]
                };
                (*result)[j++] = el;
            }
            stack[++top] = c;
            if (pr == 5) stack[++top] = k_LParen; // sin, cos, etc. has a '('

            canImpMultLast = false;
        }
    }

    // Pop all the remaining elements from the stack
    while (top != -1)
    {
        Token el = {
            operation,
            ' ',
            -1,
            {0},
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
        case k_Abs:
            return 5;
        
        case k_Expon:
        case k_EE:
        case k_Inv:
        case k_Square:
            return 4;

        // prec 3 is for implicit multiplication

        case k_Div:
        case k_Mul:
        case k_Chs:
            return 2;
        
        case k_Add:
        case k_Sub:
            return 1;
        
        default:
            return -1;
    }
}

real_t realSinhRad(const real_t* arg)
{
    real_t exp = os_RealExp(arg);

    real_t neg = os_RealNeg(arg);
    real_t expNeg = os_RealExp(&neg);

    real_t sub = os_RealSub(&exp, &expNeg);

    real_t two = os_Int24ToReal(2);

    return os_RealDiv(&sub, &two);
}

real_t realCoshRad(const real_t* arg)
{
    real_t exp = os_RealExp(arg);

    real_t neg = os_RealNeg(arg);
    real_t expNeg = os_RealExp(&neg);

    real_t add = os_RealAdd(&exp, &expNeg);

    real_t two = os_Int24ToReal(2);

    return os_RealDiv(&add, &two);
}

real_t realTanhRad(const real_t* arg)
{
    real_t sinh = realSinhRad(arg);
    real_t cosh = realCoshRad(arg);

    return os_RealDiv(&sinh, &cosh);
}

real_t realAsinhRad(const real_t* arg)
{
    real_t square = os_RealMul(arg, arg);
    
    real_t one = os_Int24ToReal(1);
    real_t addOne = os_RealAdd(&square, &one);

    real_t sqrt = os_RealSqrt(&addOne);
    real_t addArg = os_RealAdd(arg, &sqrt);

    return os_RealLog(&addArg);
}

real_t realAcoshRad(const real_t* arg)
{
    real_t square = os_RealMul(arg, arg);
    
    real_t one = os_Int24ToReal(1);
    real_t subOne = os_RealSub(&square, &one);

    real_t sqrt = os_RealSqrt(&subOne);
    real_t addArg = os_RealAdd(arg, &sqrt);

    return os_RealLog(&addArg);
}

real_t realAtanhRad(const real_t* arg)
{
    real_t one = os_Int24ToReal(1);

    real_t addToOne = os_RealAdd(&one, arg);
    real_t subFromOne = os_RealSub(&one, arg);

    real_t frac = os_RealDiv(&addToOne, &subFromOne);

    real_t log = os_RealLog(&frac);

    real_t two = os_Int24ToReal(2);

    return os_RealDiv(&log, &two);
}

real_t realAbs(const real_t* arg)
{
    real_t zero = os_Int24ToReal(0);
    real_t neg = os_RealNeg(arg);
    return os_RealCompare(arg, &zero) < 0 ? neg : *arg;
}

real_t realEE(const real_t* arg1, const real_t* arg2)
{
    real_t ten = os_Int24ToReal(10);
    real_t pow = os_RealPow(&ten, arg2);
    return os_RealMul(arg1, &pow);
}
