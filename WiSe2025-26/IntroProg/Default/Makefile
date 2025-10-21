# Copyright (c) 2025 mcpeaps_HD
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

CC = cc
WORKDIR = .

# If windows use clang
ifeq ($(OS),Windows_NT)
		CC = clang
endif

.PHONY: all run build nob clean

all: clean run

# Build nob tool first, then use it to build and run
run: build
		cd $(WORKDIR) && ./nob -r

# Just build with nob
build: nob
		cd $(WORKDIR) && ./nob -b

# Build the nob tool
nob: $(WORKDIR)/nob.c
		$(CC) -o $(WORKDIR)/nob $(WORKDIR)/nob.c

# Clean build artifacts
clean: nob
		cd $(WORKDIR) && ./nob --clean && rm -f ./nob.old
