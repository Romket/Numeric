/**
 * @file geteq.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Declares functions to get the equations to solve from the user
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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <timath.h>

#define MAX_SYSTEM_SIZE 10
#define MAX_ORDER 9

typedef enum Equality
{
    equal,
    notEqual,
    greater,
    greaterEq,
    less,
    lessEq
} Equality;

// Read as `Var Relation Exp`
typedef struct Equation
{
    Variable Var;
    Variable* VarList;
    int NVars;
    Expression Exp;
    Equality Relation;
} Equation;

typedef struct DiffEq
{
    int SystemSize;
    int Orders[MAX_SYSTEM_SIZE];
    Equation Equations[MAX_SYSTEM_SIZE];
    Variable Dependent;
    float Step;
    float End;
} DiffEq;

DiffEq getDiffEq(bool* status);

bool getEquation(DiffEq* de, int eqId, bool system);

// Returns false if `eq->Relation != equal` or if `eq->Exp` fails to evaluate
bool evalEq(Equation* eq);

#ifdef __cplusplus
}
#endif
