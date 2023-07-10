#
#  Makefile for building the startup code for the RPOS Kernel on the RPC8e
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
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <https://www.gnu.org/licenses/>.
#
##############################################################################

PROGNAME = rpc8e

CC = cl65 -I /usr/share/cc65/include
AS = ca65 -I /usr/share/cc65/asminc
AR = ar65

INCS = 
LIBS = 

LDS = ./cc65/rpc8.cfg
CFLAGS = -L $(LIBS) -I $(INCS) --cpu 65816 -Osir -g -T -t none
ASFLAGS = --cpu 65816 -g -t none
LDFLAGS = -C $(LDS) -L $(LIBS)

SRCDIR := lib
OBJDIR := ./
BUILDDIR := ./

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.c)
SSRC = $(call rwildcard,$(SRCDIR),*.s)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SSRC))
DIRS = $(wildcard $(SRCDIR)/*)

.PHONY: build
build: setup archive

.PHONY: archive
archive: $(OBJS)
	@ echo !==== ARCHIVING $^
	@ cp /usr/share/cc65/lib/supervision.lib $(BUILDDIR)/$(PROGNAME).lib
	$(AR) a $(BUILDDIR)/$(PROGNAME).lib $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo !==== COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $^
	@

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@ echo !==== ASSEMBLING $^
	@ mkdir -p $(@D)
	$(AS) $(ASFLAGS) $^  -o $@

.PHONY: setup
setup:
	@ mkdir -p $(SRCDIR)
	@ mkdir -p $(OBJDIR)
	@ mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	-@ rm *.o
	-@ rm *.lib