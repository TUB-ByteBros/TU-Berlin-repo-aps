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

.PHONY: all run_ex build_ex run_pr build_pr nob clean

all: clean run_ex run_pr

# Build nob tool first, then use it to build and run
run_ex: build_ex
		cd $(WORKDIR) && ./nob -rex

# Just build with nob
build_ex: nob
		cd $(WORKDIR) && ./nob -bex

run_pr: build_pr
		cd $(WORKDIR) && ./nob -rpr

build_pr: nob
		cd $(WORKDIR) && ./nob -bpr

# Build the nob tool
nob: $(WORKDIR)/nob.c
		$(CC) -o $(WORKDIR)/nob $(WORKDIR)/nob.c

# Clean build artifacts
clean: nob
		cd $(WORKDIR) && ./nob --clean && rm -f ./nob.old
