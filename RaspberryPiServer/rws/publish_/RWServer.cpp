#include "RWServer.hpp"

int main(int argc, char *args[]) {
	puts("[Realtime Wallpaper Server] Start");

	JServerSocket *jss = new JServerSocket(RW_PORT);
	printf("\tServer open: localhost:%d\n", RW_PORT);

	pthread_t ptExit;
	boolean run = false;
	pthread_create(&ptExit, NULL, waitExitTask, (void *)&run);

	int count = 0;
	pid_t pid;
	run = true;
	while (run) {
		printf("\tWait client %d...\n", count);
		JSocket *js = jss->accept();
		printf("\tAccepted client %d: %s\n", count, js->getHostName());

		if (run) {
			pid = fork();
			if (pid < 0) {
				error("fork()");
				break;
			}
			else if (pid > 0) {
				ThreadData td = { pid, count };
				pthread_t ptChild;
				pthread_create(&ptChild, NULL, waitChildTask, (void *)&td);

				count++;
			}
			else {
				char socketString[9];
				sprintf(socketString, "%d", js->getSocket());
				delete js;

				execl("RWHandler", "RWHandler", socketString, NULL);
			}
		}
	}

	jss->close();
	delete jss;

	pthread_join(ptExit, NULL);
	puts("[RWServer] End");

	exit(EXIT_SUCCESS);
}

void *waitExitTask(void *vp) {
	boolean *bp = (boolean *)vp;
	puts("[RWServer] Exit File Check Thread Start");
	while (true) {
		int result = ::access(RW_EXIT, F_OK);
		if (result == FILE_SUCCESS) break;
		sleep(1);
	}
	puts("\tExit file discovered.");

	int result = ::remove(RW_EXIT);
	if (result == FILE_SUCCESS) puts("\tExit file delete success.");
	else puts("\tExit file delete fail.");

	*bp = false;

	JSocket *js = new JSocket("localhost", RW_PORT);
	js->close();
	delete js;
}
void *waitChildTask(void *vp) {
	ThreadData *td = (ThreadData *)vp;
	pid_t pid = td->pid;
	int count = td->count;
	int status;
	waitpid(pid, &status, 0);
	printf("\tTask %d finished: PID=%d (%d)\n", count, pid, status);
}
void error(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
}
