#include "JAbstractSocket.hpp"

JAbstractSocket::JAbstractSocket(int &socket, struct sockaddr_in &address) {
	socket = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket == SOCKET_INVALID) this->socketError("socket()");
	else {
		memset(&address, 0, sizeof(address));
		address.sin_family = AF_INET;
	}
}
JAbstractSocket::JAbstractSocket(int &socket, struct sockaddr_in &address, int port) {
	JAbstractSocket(socket, address, NULL, port);
}
JAbstractSocket::JAbstractSocket(int &socket, struct sockaddr_in &address, const char *host, int port) {
	JAbstractSocket(socket, address);
	setAddress(socket, address, host, port);
}
JAbstractSocket::~JAbstractSocket() {
}

void JAbstractSocket::close(int &socket) {
  ::close(socket);
}

void JAbstractSocket::setAddress(int &socket, struct sockaddr_in &address, const char *host, int port) {
	if (host) {
		struct hostent *he = gethostbyname(host);
		while (*he->h_addr_list) {
			host = inet_ntoa(*(struct in_addr *)(*he->h_addr_list++));
			break;
		}
	}

	address.sin_addr.s_addr = host ? inet_addr(host) : htonl(INADDR_ANY);
	address.sin_port = htons(port);
}

void JAbstractSocket::socketError(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	if (errno != 0) {
		fputc('\t', stderr);
		char buffer[1024];
		char errnoPath[] = "/usr/include/asm-generic";
		char format[] = "cat %s/errno.h | grep -P '\t%d\t'";
		sprintf(buffer, format, errnoPath, errno);
		system(buffer);
		fputs("", stderr);
	}
}
