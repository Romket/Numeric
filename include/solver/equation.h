/**
 * @file equation.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Solver functions and associated data structures
 * @version 0.1
 * @date 2025-07-14
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

#include <stdbool.h>

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
    Variable* Var; // Variables are stored as pointers to a central list
    Expression Exp;
    Equality Relation;
} Equation;

// Returns false if `eq.Relation != eq` or if `eq.Exp` fails to evaluate
bool evalEq(Equation* eq);

// Returns the size of `vars` or `-1` if `solverId` is invalid
int getVars(int solverId, Variable* vars);

#ifdef __cplusplus
}
#endif
