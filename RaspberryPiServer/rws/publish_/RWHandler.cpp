#include "RWHandler.hpp"

int main(int argc, char *args[]) {
	puts("[RWHandler] Start");

	if (argc == 2) {
		struct sockaddr_in a;
		JSocket *js = new JSocket(atoi(args[1]), a);
		int r = js->read();
		delete js;

		if (r == RWHANDLER_RECEIVE) {
			execl("RWReceiver", "RWReceiver", args[1], NULL);
		}
		else if (r == RWHANDLER_SEND) {
			execl("RWSender", "RWSender", args[1], NULL);
		}
		else error("RWHandler: Invalid flag data received.");
	}
	else error("RWHandler: Invalid arguments.");

	puts("[RWHandler] End");

	exit(EXIT_SUCCESS);
}

void error(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	exit(EXIT_FAILURE);
}
