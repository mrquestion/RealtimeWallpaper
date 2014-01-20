#pragma once

#ifndef __RWHANDLER_HPP__
#define __RWHANDLER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "JSocket.hpp"

#define RWHANDLER_RECEIVE 1
#define RWHANDLER_SEND 2

void error(const char *);

#endif
