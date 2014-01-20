#include "RWCClient.hpp"

int main(int argc, char *args[]) {
	puts("[Realtime Wallpaper Camera Client]");

	time_t now;
	struct tm *nowtm;
	char filename[50], command[100];
	int delay = 0;

	while (true) {
		mkdir(FILE_PATH, 0755);

		time(&now);
		nowtm = localtime(&now);
		strftime(filename, sizeof(filename), FILE_NAME_FORMAT, nowtm);
		sprintf(command, "raspistill -o %s/%s.%s -t %d -w %d -h %d -e %s -n", FILE_PATH, filename, FILE_EXTENTION, 0, FILE_WIDTH, FILE_HEIGHT, FILE_EXTENTION);
		printf("- File: %s/%s.%s\n", FILE_PATH, filename, FILE_EXTENTION);
		system(command);

		sprintf(command, "./RWSender %s.%s", filename, FILE_EXTENTION);
		system(command);

		time(&now);
		nowtm = localtime(&now);
		delay = 60 - nowtm->tm_sec;
		if (delay >= 60) delay -= 60;
		if (delay < 0) delay = 0;
		printf("\tWait %d second(s).\n", delay);
		sleep(delay);

		break;
	}

	exit(EXIT_SUCCESS);
}
