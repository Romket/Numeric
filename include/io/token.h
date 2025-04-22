/**
 * @file token.h
 * @author Luke Houston (Romket) (lukehouston08@gmail.com)
 * @brief Defines tokens for characters such as pi, exponents, etc.
 * @version 0.1
 * @date 2025-04-20
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

#ifdef __cplusplus
extern "C"
{
#endif

#define STR(x) ((const char[]){ x, 0 })

// 0x00 is empty
// 0x01 - 0x04 can be printed without special codes
#define SEL         STR(0x05)
#define UP          STR(0x06)
#define DOWN        STR(0x07)
#define INT         STR(0x08)
#define BOX         STR(0x0A)
#define PLUS        STR(0x0B)
#define DOT         STR(0x0C)
#define CUBE        STR(0x0E)
#define SQRT        STR(0x10)
#define INV         STR(0x11)
#define SQUARE      STR(0x12)
#define ANGLE       STR(0x13)
#define DEG         STR(0x14)
#define POWR        STR(0x15)
#define POWT        STR(0x16)
#define LEQ         STR(0x17)
#define NEQ         STR(0x18)
#define GEQ         STR(0x19)
#define CHS         STR(0x1A)
#define EE          STR(0x1B)
#define STO         STR(0x1C)
#define SUB10       STR(0x1D)
#define UPLIGHT     STR(0x1E)
#define DOWNLIGHT   STR(0x1F)
// 0x20 - 0x2F are special characters and can be printed without codes
// 0x30 - 0x39 are numbers
// 0x3A - 0x40 are more special characters
// 0x41 - 0x5A are uppercase letters
#define THETA       STR(0x5B)
// 0x5B - 0x60 are more special characters
// 0x61 - 0x7A are lowercase letters
// 0x7B - 0x7E are more special characters
#define BLOCKEQ     STR(0x7F)
#define SUB0        STR(0x80)
// 0x81 - 0x89 are subscripts - index from SUB0
// 0x8A - 0xB5 are accented characters - need testing
// TODO: continue
#define PI          STR(0xC4)

#ifdef __cplusplus
}
#endif
