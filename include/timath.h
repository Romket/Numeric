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

#include <stdbool.h>
#include <stdint.h>

enum ElementType
{
    number,
    variable,
    operation
};

typedef struct EquationElementStruct
{
    enum ElementType Type;
    uint16_t VarName;
    double Number;
    uint16_t Operation;
} EquationElement;
typedef EquationElement* Equation;

typedef struct VariableStruct
{
    uint16_t Name;
    double Value;
} Variable;

int parseToPostfix(uint16_t* eq, int len, Equation* result);
int prec(uint16_t el);

double evaluate(Equation eq, int len, bool* status, Variable* vars, int nVars);
double ex(double a, double b, uint16_t op, int* top);

#ifdef __cplusplus
}
#endif
