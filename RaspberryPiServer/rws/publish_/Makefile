# ===============================
# Makefile for RWServer
#  - Realtime Wallpaper Server -
# ===============================

# -------------------------------

# Compile in C++

# Sub Program
# 1. RWHandler
# 2. RWReceiver
# 3. RWSender

# Custom Library
# 1. JServerSocket by JAbstractSocket
# 2. JSocket by JAbstractSocket
# 3. JBuffer

# Use Library
# 1. pthread

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
ARGUMENTS	=$(EMPTY)

MAIN	=RWServer

SUB1	=RWHandler
SUB2	=RWReceiver
SUB3	=RWSender
SUBS		= $(SUB1) $(SUB2) $(SUB3)
SUBS_SOURCE	= $(SUB1).cpp $(SUB2).cpp $(SUB3).cpp
SUBS_OBJECT	= $(SUB1).o $(SUB2).o $(SUB3).o

PROJECT	=$(MAIN) $(SUBS)

WORKSPACE	=/work/rws

COMMAND_CLEAN		=clean
COMMAND_UNINSTALL	=uninstall
COMMAND_REMAKE		=remake

SOCKET_LIBRARY_DIR	=$(WORKSPACE)/socket
BUFFER_LIBRARY_DIR	=$(WORKSPACE)/buffer
INCLUDE_DIR			= -I $(SOCKET_LIBRARY_DIR) -I $(BUFFER_LIBRARY_DIR)

LIBRARY	= -l pthread

ARGUMENTS	+= $(LIBRARY)


# Build part

build: $(PROJECT)
	make $(COMMAND_CLEAN)


# Custum Library part

CUSTOM_LIBRARY	+= JAbstractSocket.o JSocket.o JServerSocket.o JBuffer.o
$(CUSTOM_LIBRARY):
	$(CPPC) -c $(SOCKET_LIBRARY_DIR)/$*.cpp


# Main part

$(PROJECT): $(MAIN).o $(SUBS_OBJECT)
	$(CPPC) $@.o $(CUSTOM_LIBRARY) -o $@ $(INCLUDE_DIR) $(ARGUMENTS)

$(MAIN).o: $(MAIN).cpp $(CUSTOM_LIBRARY)
	$(CPPC) -c $< $(INCLUDE_DIR)

$(SUBS_OBJECT): $(SUBS_SOURCE) $(CUSTOM_LIBRARY)
	$(CPPC) -c $*.cpp $(INCLUDE_DIR)


# Command part

$(COMMAND_CLEAN):
	cd $(WORKSPACE)
	rm -f $(MAIN).o
	rm -f $(SUBS_OBJECT)
	rm -f $(CUSTOM_LIBRARY)

$(COMMAND_UNINSTALL):
	cd $(WORKSPACE)
	rm -f $(PROJECT)

$(COMMAND_REMAKE):
	make $(COMMAND_CLEAN)
	make $(COMMAND_UNINSTALL)
	make
