#pragma once

#ifndef __RWRECEIVER_HPP__
#define __RWRECEIVER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "JSocket.hpp"

#define FILE_PATH "output"
#define FILE_LATEST "latest.png"

void error(const char *);

#endif
