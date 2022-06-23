# makefile for primordial graphical framework
# have this compile linux or windows
# use os=linux/windows on make command

# --- Config ---
flags = -Wall -O2

# --- OS Dependent ---
ifeq ($(os),linux)

	cc = g++
	name = pgf
	links = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl# -lm
	
	clean_shaders = rm -f bin/linux/shaders/*
	copy_shaders = cp shaders/* bin/linux/shaders/
	
else ifeq ($(os),windows)

 	cc = x86_64-w64-mingw32-g++.exe
 	name = pgf.exe
 	links = -lglfw3
	
	clean_shaders = del /q bin\windows\shaders\*
	copy_shaders = xcopy shaders bin\windows\shaders
	
else
 	$(error invalid os name)
endif

# --- Paths ---
source_path = src
include_path = include
library_path = lib/$(os)
object_path = obj/$(os)
output_path = bin/$(os)

raw_sources = main.cpp glad.c

sources = $(addprefix $(source_path)/, $(raw_sources))
output = $(output_path)/$(name)

# --- Recipes ---

all: shaders
	@echo Building pgf for $(os)...
	$(cc) $(flags) $(sources) -o $(output) -I$(include_path) -L$(library_path) $(links)

.PHONY: shaders
shaders:
	$(clean_shaders)
	$(copy_shaders)

.PHONY: clean
clean:
	@echo cleaning up...
	del /S *.o
