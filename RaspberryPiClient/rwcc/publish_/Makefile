# ===============================
# Makefile for RWCClient
#  - Realtime Wallpaper Camera Client -
# ===============================

# -------------------------------

# Compile in C++

# Sub Program
# 1. RWSender

# Custom Library
# 1. JSocket by JAbstractSocket
# 2. JBuffer

# -------------------------------



# Variables

EMPTY=

GCC			=gcc
GPP			=g++
CLANG		=clang
CLANGPP		=clang++
CLANGARGS	=-std=c++11 -stdlib=libc++

CC			=$(GCC)
CPPC		=$(GPP)
ARGS		=$(EMPTY)

PROJECT	=RWCClient
MAIN	=$(PROJECT)

SUB1	=RWSender

WORKSPACE		=/work/rwcc

COMMAND_CLEAN		=clean
COMMAND_UNINSTALL	=uninstall
COMMAND_REMAKE		=remake

SOCKET_LIBRARY_DIR	=../socket


# Build part

build: $(PROJECT)


# Custum Library part

CUSTOM_LIBRARY			+= JAbstractSocket.o
CUSTOM_LIBRARY_HEADER	+= JAbstractSocket.hpp
JAbstractSocket.o: $(SOCKET_LIBRARY_DIR)/JAbstractSocket.cpp
	cp $(SOCKET_LIBRARY_DIR)/$*.hpp .
	$(CPPC) -c $<

CUSTOM_LIBRARY			+= JSocket.o
CUSTOM_LIBRARY_HEADER	+= JSocket.hpp
JSocket.o: $(SOCKET_LIBRARY_DIR)/JSocket.cpp
	cp $(SOCKET_LIBRARY_DIR)/$*.hpp .
	$(CPPC) -c $<

CUSTOM_LIBRARY			+= JBuffer.o
CUSTOM_LIBRARY_HEADER	+= JBuffer.hpp
JBuffer.o: $(SOCKET_LIBRARY_DIR)/JBuffer.cpp
	cp $(SOCKET_LIBRARY_DIR)/$*.hpp .
	$(CPPC) -c $<


# Main part

SUB		+= $(SUB1)
SUBS	+= $(SUB1).o

$(SUB1).o: $(SUB1).cpp
	$(CPPC) -c $<
$(SUB1): $(SUB1).o
	$(CPPC) $< $(CUSTOM_LIBRARY) -o $@


$(PROJECT): $(CUSTOM_LIBRARY) $(MAIN).o $(SUB)
	$(CPPC) $(MAIN).o $(CUSTOM_LIBRARY) -o $@ $(ARGS)
	make $(COMMAND_CLEAN)

$(MAIN).o: $(MAIN).cpp
	$(CPPC) -c $<


# Command part

$(COMMAND_CLEAN):
	cd $(WORKSPACE)
	rm -f $(MAIN).o
	rm -f $(SUBS)
	rm -f $(CUSTOM_LIBRARY)
	rm -f $(CUSTOM_LIBRARY_HEADER)

$(COMMAND_UNINSTALL):
	cd $(WORKSPACE)
	rm -f $(PROJECT)
	rm -f $(SUB)

$(COMMAND_REMAKE):
	make $(COMMAND_CLEAN)
	make $(COMMAND_UNINSTALL)
	make
