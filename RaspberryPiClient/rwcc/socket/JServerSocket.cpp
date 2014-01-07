#include "JServerSocket.hpp"

JServerSocket::JServerSocket(int port): super(this->socket, this->address, port) {
	this->bind();
	this->listen();
}

int JServerSocket::bind() {
	int result = ::bind(this->socket, (struct sockaddr *)&this->address, sizeof(this->address));
	if (result == SOCKET_ERROR) socketError("bind()");
	return result;
}
int JServerSocket::listen() {
	return this->listen(SOCKET_BACKLOG);
}
int JServerSocket::listen(int backlog) {
	int result = ::listen(this->socket, backlog);
	if (result == SOCKET_ERROR) socketError("listen()");
	return result;
}
JSocket *JServerSocket::accept() {
	JSocket *js = NULL;
	struct sockaddr_in address;
	socklen_t size = sizeof(address);
	int socket = ::accept(this->socket, (struct sockaddr *)&this->address, &size);
	if (socket == SOCKET_INVALID) socketError("accept()");
	else js = new JSocket(socket, address);
	return js;
}
void JServerSocket::close() {
	super::close(socket);
}
