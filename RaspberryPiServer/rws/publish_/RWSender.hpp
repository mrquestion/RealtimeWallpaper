#pragma once

#ifndef __RWSENDER_HPP__
#define __RWSENDER_HPP__

#include <stdio.h>

#include "JSocket.hpp"

#define FILE_PATH "output"
#define FILE_LATEST "latest.png"

#define SEND_SUCCESS 0
#define SEND_FAILURE 1

void error(const char *);

#endif
