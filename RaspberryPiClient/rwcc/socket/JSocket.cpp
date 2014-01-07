#include "JSocket.hpp"

JSocket::JSocket(): super(this->socket, this->address) {

}
JSocket::JSocket(const char *host, int port): super(this->socket, this->address, host, port) {
	this->connect(this->host, this->port);
}
JSocket::JSocket(int socket, struct sockaddr_in address): super(this->socket, this->address) {
	this->socket = socket;
	this->address = address;
}

int JSocket::connect(const char *host, int port) {
	if (this->address.sin_addr.s_addr == (int)NULL) setAddress(this->socket, this->address, host, port);
	int result = ::connect(this->socket, (struct sockaddr *)&this->address, sizeof(this->address));
	if (result == SOCKET_ERROR) this->socketError("connect()");
	return result;
}

int JSocket::read() {
	byte b;
	int r = ::read(this->socket, &b, 1);
	if (r <= 0) return SOCKET_ERROR;
	else return b;
}
int JSocket::read(JBuffer &jb) {
	byte *bs = new byte[jb.getSize()];
	int r = ::read(this->socket, bs, jb.getSize());
	jb.setBytes(bs, 0, jb.getSize());
	return r;
}
int JSocket::write(byte b) {
	int r = ::write(this->socket, &b, 1);
	return r;
}
int JSocket::write(byte *bs, int offset, int length) {
	int r = ::write(this->socket, bs+offset, length);
	return r;
}
int JSocket::write(JBuffer &jb) {
	return this->write(jb, 0, jb.getSize());
}
int JSocket::write(JBuffer &jb, int offset, int length) {
	byte *bs = jb.getBytes();
	int r = ::write(this->socket, bs+offset, length);
	delete [] bs;
	return r;
}
int JSocket::write(const char *s) {
	int r = ::write(this->socket, s, strlen(s));
	return r;
}
void JSocket::flush() {
	int r = write((byte)NULL);
}
char *JSocket::getHostName() {
	return inet_ntoa(address.sin_addr);
}
void JSocket::close() {
	super::close(socket);
}
