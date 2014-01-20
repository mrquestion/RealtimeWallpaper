#pragma once

#ifndef __RWSENDER_HPP__
#define __RWSENDER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "JSocket.hpp"

#define RW_HOST "192.168.0.100"
#define RW_PORT 9123
#define RW_CLIENT 1

#define FILE_PATH "output"

void error(const char *);

#endif
