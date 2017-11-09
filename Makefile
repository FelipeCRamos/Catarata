# Makefile for the Cataract Diagnosis Software
#
# Creators:
# 	- João Pedro de Amorim Paula
# 	- Felipe C. Ramos Filho

# Makefile conventions
SHELL = /bin/sh

# Directories
incdir = ./include
srcdir = ./src
objdir = ./obj
bindir = ./bin

# Macros
CC = gcc
CFLAGS = -Wall -std=c11 -I. -I$(incdir)
RM = -rm 

OBJS = $(objdir)/read.o $(objdir)/process.o $(objdir)/write.o

# Phony targets (for more information, visit https://www.gnu.org/software/make/manual/make.html#Phony-Targets)
.PHONY: clean cleanobj cleanbin
.PHONY: all

# Use "make" to execute everything
all: main read process write
	$(bindir)/main

# Use "make main" to execute the main (same as all)
main: $(bindir)/main

# Use "make read" to build only the read module
read: $(objdir)/read.o

# Use "make process" to build only the process module
process: $(objdir)/process.o

# Use "make write" to build only the write module
write: $(objdir)/write.o

# Executes the main
$(bindir)/main: $(srcdir)/main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile only the reading module (use "make read")
$(objdir)/read.o: $(srcdir)/read.c $(incdir)/read.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile only the processing module (use "make process")
$(objdir)/process.o: $(srcdir)/process.c $(incdir)/process.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile only the writing module (use "make write")
$(objdir)/write.o: $(srcdir)/write.c $(incdir)/write.h
	$(CC) $(CFLAGS) -c $< -o $@

# Removes all objects
cleanobj:
	$(RM) $(objdir)/*.o

# Removes all executables
cleanbin:
	$(RM) $(bindir)/*

# Removes all executables and all objects
clean: cleanobj cleanbin
