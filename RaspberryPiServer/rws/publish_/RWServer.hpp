#pragma once

#ifndef __RWSERVER_HPP__
#define __RWSERVER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "JServerSocket.hpp"
#include "JSocket.hpp"

#define RW_PORT 9123

#define RW_EXIT "rws.exit"

#define FILE_SUCCESS 0
#define FILE_ERROR -1

typedef struct {
	pid_t pid;
	int count;
} ThreadData;

void *waitExitTask(void *);
void *waitChildTask(void *);
void error(const char *);

#endif
