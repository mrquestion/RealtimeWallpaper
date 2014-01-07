#pragma once

#ifndef __JSERVERSOCKET_HPP__
#define __JSERVERSOCKET_HPP__

#include "JAbstractSocket.hpp"
#include "JSocket.hpp"

#define SOCKET_BACKLOG 5

class JServerSocket: public JAbstractSocket {
	public:
		JServerSocket(int);

		int bind();
		int listen();
		int listen(int);
		JSocket *accept();
		void close();
};

#endif
