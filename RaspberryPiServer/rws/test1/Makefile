# ===============================
# Makefile for RWServer
#  - Realtime Wallpaper Server -
# ===============================

# -------------------------------

# Compile in C++

# Custom Library
# 1. JBuffer
# 2. JServerSocket by JAbstractSocket
# 3. JSocket by JAbstractSocket

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

PROJECT	=RWServer
MAIN	=$(PROJECT)

WORKSPACE		=/work/rws

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

CUSTOM_LIBRARY			+= JServerSocket.o
CUSTOM_LIBRARY_HEADER	+= JServerSocket.hpp
JServerSocket.o: $(SOCKET_LIBRARY_DIR)/JServerSocket.cpp
	cp $(SOCKET_LIBRARY_DIR)/$*.hpp .
	$(CPPC) -c $<

CUSTOM_LIBRARY			+= JBuffer.o
CUSTOM_LIBRARY_HEADER	+= JBuffer.hpp
JBuffer.o: $(SOCKET_LIBRARY_DIR)/JBuffer.cpp
	cp $(SOCKET_LIBRARY_DIR)/$*.hpp .
	$(CPPC) -c $<


# Main part

$(PROJECT): $(CUSTOM_LIBRARY) $(MAIN).o
	$(CPPC) $(MAIN).o $(CUSTOM_LIBRARY) -o $(PROJECT) $(ARGS)
#	$(CPPC) -c test.cpp
#	$(CPPC) test.o $(CUSTOM_LIBRARY) -o test
	$(CPPC) -o test test.cpp $(CUSTOM_LIBRARY)
	make $(COMMAND_CLEAN)

$(MAIN).o: $(MAIN).cpp
	$(CPPC) -c $(MAIN).cpp


# Command part

$(COMMAND_CLEAN):
	cd $(WORKSPACE)
	rm -f $(MAIN).o
	rm -f $(CUSTOM_LIBRARY)
	rm -f $(CUSTOM_LIBRARY_HEADER)

$(COMMAND_UNINSTALL):
	cd $(WORKSPACE)
	rm -f $(PROJECT)
	rm -f test

$(COMMAND_REMAKE):
	make $(COMMAND_CLEAN)
	make $(COMMAND_UNINSTALL)
	make
