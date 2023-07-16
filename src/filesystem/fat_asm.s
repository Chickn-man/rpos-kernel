;#
;#  FAT12 assembly functions for the RPOS Kernel
;#
;##############################################################################
;#
;#  Copyright (C) 2023 Keegan Powers
;#
;#  This file is part of the RPOS Kernel
;#
;#  The RPOS Kernel is free software: you can redistribute it
;#  and/or modify it under the terms of the GNU General Public
;#  License as published by the Free Software Foundation, either
;#  version 3 of the License, or (at your option) any later version.
;#
;#  This program is distributed in the hope that it will be useful,
;#  but WITHOUT ANY WARRANTY without even the implied warranty of
;#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;#  GNU General Public License for more details.
;#
;#  You should have received a copy of the GNU General Public License
;#  along with this program. If not, see <https://www.gnu.org/licenses/>.
;#
;#############################################################################

.setcpu	"65816"
.smart	on
.autoimport	on
.importzp sp, tmp1, tmp2, ptr1
.import popax

.export	_getFatEntry

.segment "CODE"

.proc _getFatEntry: near
    phy
    php
    xba
    txa
    xba
    rep #$30
    sta ptr1
    sep #$30
    jsr popax
    xba
    txa
    xba
    rep #$30
    sta tmp1
    lda #2
    sta 254
    lda #3
    sta 252
    lda tmp1
    clc
    .byte $6f, 254, 0
    clc
    .byte $2f, 252, 0
    sta tmp2
    clc 
    adc ptr1
    sta 250
    lda tmp1
    sep #$30
    and #1
    cmp #1
    beq odd_entry
even_entry:
    lda (250)
    xba 
    ldy #1
    lda (250), y
    and #$0f
    xba
    bra exitrf
odd_entry:
    ldy #2
    lda (250), y
    xba
    ldy #1
    lda (250), y
    and #$f0
    xba
    rep #$30
    clc
    cmp #$8000
    rol
    cmp #$8000
    rol
    cmp #$8000
    rol
    cmp #$8000
    rol
exitrf:
    sep #$30
    xba
    tax
    xba
    plp
    ply
    rts 
.endproc