/*
#  Target stuff for the RPOS Kernel
#
##############################################################################
#
#  Copyright (C) 2023 Keegan Powers
#
#  This file is part of the RPOS Kernel
#
#  The RPOS Kernel is free software: you can redistribute it
#  and/or modify it under the terms of the GNU General Public
#  License as published by the Free Software Foundation, either
#  version 3 of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <https://www.gnu.org/licenses/>.
#
#############################################################################
*/

#ifndef TARGET

#ifndef TARGET_STRING

#error "No target specified"

#endif

#define cat(a,b) cat_impl(a, b)
#define cat_impl(a,b) a ## b

#define t_rpc8e 1
#define t_cx16 2
#define t_x86 100
#define t_x86_32 101
#define t_x86_64 102

#define TARGET cat(t_,TARGET_STRING)

#if TARGET == t_rpc8e // CC == cc65
#define packed
#else
#define packed __attribute__((packed))
#endif

#endif