#pragma once

#ifndef __JABSTRACTSOCKET_HPP__
#define __JABSTRACTSOCKET_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <errno.h>

#include "JBuffer.hpp"

#define SOCKET_INVALID -1
#define SOCKET_ERROR -1

class JAbstractSocket {
	public:
		JAbstractSocket(int &, struct sockaddr_in &, int);
		JAbstractSocket(int &, struct sockaddr_in &, const char *, int);

		int getSocket() { return socket; };
		void close(int &);

	protected:
		JAbstractSocket(int &, struct sockaddr_in &);
		~JAbstractSocket();

		int socket;
		struct sockaddr_in address;
		char *host;
		int port;

		void setAddress(int &, struct sockaddr_in &, const char *, int);

		void socketError(const char *);
};

typedef JAbstractSocket super;

#endif
