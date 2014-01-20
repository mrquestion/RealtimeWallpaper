#pragma once

#ifndef __RWCCLIENT_HPP__
#define __RWCCLIENT_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define true 1
#define false 0

#define FILE_NAME_FORMAT "%Y%m%d_%H%M%S"
#define FILE_PATH "output"
#define FILE_WIDTH 800
#define FILE_HEIGHT 600
#define FILE_EXTENTION "png"

void error(const char *);

#endif
