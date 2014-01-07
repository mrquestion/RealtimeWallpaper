#pragma once

#ifndef __JSOCKET_HPP__
#define __JSOCKET_HPP__

#include "JAbstractSocket.hpp"

class JSocket: public JAbstractSocket {
	public:
		JSocket();
		JSocket(const char *, int);
		JSocket(int, struct sockaddr_in);

		int connect(const char *, int);
		int read();
		int read(JBuffer &);
		int write(byte);
		int write(byte *, int, int);
		int write(JBuffer &);
		int write(JBuffer &, int, int);
		int write(const char *);
		void flush();
		char *getHostName();
		void close();
};

#endif
