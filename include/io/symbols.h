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

#define STR(...) ((const char[]){ __VA_ARGS__, 0 })

// 0x00 is empty
#define VARN                0x01
#define VARU                0x02
#define VARV                0x03
#define VARW                0x04

#define SEL                 0x05
#define UP                  0x06
#define DOWN                0x07
#define INT                 0x08
#define TIMES               0x09
#define BOX                 0x0A
#define PLUS                0x0B
#define DOTSMALL            0x0C
#define SUBT                0x0D
#define CUBE                0x0E
#define FIELD               0x0F
#define SQRT                0x10
#define INV                 0x11
#define SQUARE              0x12
#define ANGLE               0x13
#define SUPERO              0x14
#define SUPERR              0x15
#define SUPERT              0x16
#define LEQ                 0x17
#define NEQ                 0x18
#define GEQ                 0x19
#define CHS                 0x1A
#define EE                  0x1B
#define STO                 0x1C
#define SUB10               0x1D
#define UPLIGHT             0x1E
#define DOWNLIGHT           0x1F

// 0x20 - 0x2F are special characters and can be printed without codes
// 0x30 - 0x39 are numbers
// 0x3A - 0x40 are more special characters
// 0x41 - 0x5A are uppercase letters

#define THETA               0x5B

// 0x5C - 0x60 are more special characters
// 0x61 - 0x7A are lowercase letters
// 0x7B - 0x7E are more special characters

#define BLOCKEQ             0x7F
#define SUB0                0x80
// 0x81 - 0x89 are subscripts - index from SUB0

#define UACCA               0x8A
#define UGRAVEA             0x8B
#define UCIRCA              0x8C
#define UUMA                0x8D
#define LACCA               0x8E
#define LGRAVEA             0x8F
#define LCIRCA              0x90
#define LUMA                0x91

#define UACCE               0x92
#define UGRAVEE             0x93
#define UCIRCE              0x94
#define UUME                0x95
#define LACCE               0x96
#define LGRAVEE             0x97
#define LCIRCE              0x98
#define LUME                0x99

#define UACCI               0x9A
#define UGRAVEI             0x9B
#define UCIRCI              0x9C
#define UUMI                0x9D
#define LACCI               0x9E
#define LGRAVEI             0x9F
#define LCIRCI              0xA0
#define LUMI                0xA1

#define UACCO               0xA2
#define UGRAVEO             0xA3
#define UCIRCO              0xA4
#define UUMO                0xA5
#define LACCO               0xA6
#define LGRAVEO             0xA7
#define LCIRCO              0xA8
#define LUMO                0xA9

#define UACCU               0xAA
#define UGRAVEU             0xAB
#define UCIRCU              0xAC
#define UUMU                0xAD
#define LACCU               0xAE
#define LGRAVEU             0xAF
#define LCIRCU              0xB0
#define LUMU                0xB1

#define UCEDILLA            0xB2
#define LCEDILLA            0xB3

#define UNTILDE             0xB4
#define LNTILDE             0xB5

#define FTICK               0xB6
#define BTICK               0xB7
#define UMLAUT              0xB8
#define INVQUEST            0xB9
#define INVEXCL             0xBA

#define LALPHA              0xBB
#define LBETA               0xBC
#define LGAMMA              0xBD
#define UDELTA              0xBE
#define LDELTA              0xBF
#define LEPSILON            0xC0

#define LBRACK              0xC1

#define LLAMBDA             0xC2
#define LMU                 0xC3
#define LPI                 0xC4
#define LRHO                0xC5
#define USIGMA              0xC6
#define LSIGMA              0xC7
#define LTAU                0xC8
#define LPHI                0xC9
#define UOMEGA              0xCA

#define XBAR                0xCB
#define YBAR                0xCC

#define SUPERX              0xCD
#define ELIPSIS             0xCE
#define BACK                0xCF
#define DOTBIG              0xD0
#define FSLASH              0xD1
#define DASH                0xD2
#define SUPER2              0xD3
#define DEG                 0xD4
#define SUPER3              0xD5

#define NEWLINE             0xD6
#define I                   0xD7
#define LCIRCP              0xD8
#define LCHI                0xD9
#define FDIST               0xDA
#define E                   0xDB
#define LIST                0xDC
#define NATS                0xDD
#define DOUBLERPAREN        0xDE
#define RARROW              0xDF

#define CURSOR              0xE0
#define CURSOR2ND           0xE1
#define CURSORALPHA         0xE2
#define CURSORLA            0xE3

#define CURSORINS           0xE4
#define CURSORINS2ND        0xE5
#define CURSORINSALPHA      0xE6
#define CURSORINSLA         0xE7

#define THIN                0xE8
#define THICK               0xE9
#define INEQUP              0xEA
#define INEQDOWN            0xEB

#define LHEX0               0xEC
#define HEX0                0xED

#define DOTTEDLIGHT         0xEE
#define UPBOLD              0xEF
#define DOWNBOLD            0xF0
#define END                 0xF1

#define SUPER4              0xF2
// 0xF3 is the same as 0x03 UP
#define UBETA               0xF4
#define SPACEIND            0xF5
#define FRAC                0xF6
#define CURSORBOX           0xF7
#define DOTTEDBOLD          0xF8
#define DOTSMALL2           0xF9

#ifdef __cplusplus
}
#endif
