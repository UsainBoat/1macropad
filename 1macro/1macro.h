/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define LAYOUT( \
    KA1, KA2, KA3, KA4, \
    KB1, KB2, KB3, KB4, \
    KC1, KC2, KC3, KC4, \
    KD1, KD2, KD3, KD4 \
) \
{ \
    { KA1, KA2, KA3, KA4 }, \
    { KB1, KB2, KB3, KB4 }, \
    { KC1, KC2, KC3, KC4 }, \
    { KD1, KD2, KD3, KD4 } \
}
