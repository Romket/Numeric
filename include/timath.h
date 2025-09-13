/**
 * @file timath.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Functions to perform math operations on user-generated equations
 * @version 0.1
 * @date 2025-04-23
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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <ti/real.h>

#include <io/iodefs.h>

#include <stdbool.h>
#include <stdint.h>

typedef enum TokenType
{
    number,
    variable,
    operation
} TokenType;

typedef struct Token
{
    TokenType Type;
    char VarName;
    int Subscript;
    int Deriv;
    real_t Number;
    uint16_t Operation;
} Token;

typedef struct Expression
{
    Token Tokens[MAX_STRING_LEN];
    int Length;
} Expression;

typedef struct Variable
{
    char Name;
    int Subscript; // -1 for no suscript
    int Deriv;
    real_t Value;
} Variable;

Expression parseToPostfix(uint16_t* in, int len);
int prec(uint16_t el);

real_t evaluate(Expression* expr, bool* status, Variable* vars, int nVars);

real_t ex(real_t first, real_t second, uint16_t op, int* top, bool* status);

real_t realSinhRad(const real_t* arg);
real_t realCoshRad(const real_t* arg);
real_t realTanhRad(const real_t* arg);

real_t realAsinhRad(const real_t* arg);
real_t realAcoshRad(const real_t* arg);
real_t realAtanhRad(const real_t* arg);

real_t realAbs(const real_t* arg);

real_t realEE(const real_t* arg1, const real_t* arg2);

#ifdef __cplusplus
}
#endif
