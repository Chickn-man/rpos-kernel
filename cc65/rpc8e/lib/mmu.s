;#
;#  MMU opcode wrappers for cc65
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
;#  but WITHOUT ANY WARRANTY; without even the implied warranty of
;#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;#  GNU General Public License for more details.
;#
;#  You should have received a copy of the GNU General Public License
;#  along with this program. If not, see <https://www.gnu.org/licenses/>.
;#
;#############################################################################

.export _setMappedRedbusDev, _getMappedRedbusDev, _setRedbusWindowOffset, _getRedbusWindowOffset
.export _enableRedbus, _disableRedbus, _setMemoryMappedWindow, _getMemoryMappedWindow
.export _setBrkAddress, _getBrkAddress, _setPorAddress, _getPorAddress, _logRegisterA

.segment "CODE"

.smart

.proc _setMappedRedbusDev: near
    php
	.byte $EF
	.byte $00
    plp
	rts
.endproc

.proc _getMappedRedbusDev: near
	.byte $EF
	.byte $80
	rts
.endproc

.proc _setRedbusWindowOffset: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $01
    plp
    rts
.endproc

.proc _getRedbusWindowOffset: near
    php
    sep #$30
	.byte $EF
	.byte $81
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _enableRedbus: near
	.byte $EF
	.byte $02
	rts
.endproc

.proc _disableRedbus: near
	.byte $EF
	.byte $82
	rts
.endproc

.proc _setMemoryMappedWindow: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $03
    plp
    rts
.endproc

.proc _getMemoryMappedWindow: near
    php
    sep #$30
	.byte $EF
	.byte $83
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _setBrkAddress: near
    php
    sep #$30
    xba
    txa
    xba
	.byte $EF
	.byte $05
    plp
    rts
.endproc

.proc _getBrkAddress: near
    php
    sep #$30
	.byte $EF
	.byte $85
    xba
    tax
    xba
    plp
    rts
.endproc

.proc _setPorAddress: near
	.byte $EF
	.byte $06
    rts
.endproc

.proc _getPorAddress: near
	.byte $EF
	.byte $86
    rts
.endproc

.proc _logRegisterA: near
	.byte $EF
	.byte $FF
    rts
.endproc
