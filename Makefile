# Makefile for the Cataract Diagnosis Software
#
# Creators:
#		- João Pedro de Amorim Paula
#		- Felipe C. Ramos Filho
PROJ_NAME = catarata

# Makefile conventions
SHELL = /bin/sh

# Directories
incdir = ./include
srcdir = ./src
objdir = ./obj
bindir = ./bin

# Macros
CC = gcc
CFLAGS = -Wall -Wextra -g -ggdb -std=c11 -lm -I. -I$(incdir)
RM = -rm 
OBJS = $(addprefix $(objdir)/,read.o process.o write.o util.o)

# Phony targets (for more information, visit https://www.gnu.org/software/make/manual/make.html#Phony-Targets)
.PHONY: clean cleanobj cleanbin cleanimg
.PHONY: all main build read process write

# Use "make" to execute everything
all: build main 

# Use "make main" to compile the main
main: $(PROJ_NAME)

# Use "make build" to build all the modules
build: util read process write

# Use "make util" to build only the util module
util: $(objdir)/util.o

# Use "make read" to build only the read module
read: $(objdir)/read.o

# Use "make process" to build only the process module
process: $(objdir)/process.o

# Use "make write" to build only the write module
write: $(objdir)/write.o

# Compiles the main
catarata: $(srcdir)/main.c $(OBJS)
	# mkdir -p $(bindir)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Builds only the util module
$(objdir)/util.o: $(srcdir)/util.c $(incdir)/util.h
	mkdir -p $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

# Builds only the reading module (use "make read")
$(objdir)/read.o: $(srcdir)/read.c $(incdir)/read.h $(incdir)/util.h
	mkdir -p $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

# Builds only the processing module (use "make process")
$(objdir)/process.o: $(srcdir)/process.c $(incdir)/process.h $(incdir)/util.h
	mkdir -p $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

# Builds only the writing module (use "make write")
$(objdir)/write.o: $(srcdir)/write.c $(incdir)/write.h $(incdir)/util.h
	mkdir -p $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

# Removes all objects
cleanobj:
	$(RM) -rf $(objdir)

# Removes all executables
cleanbin:
	$(RM) -rf $(bindir)
	$(RM) $(PROJ_NAME)

# Removes all images
cleanimg:
	$(RM) ./test/*

# Removes all executables and all objects
clean: cleanobj cleanbin cleanimg
