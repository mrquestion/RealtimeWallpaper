#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../file/JFile.hpp"

int main(int argc, char *args[]) {
	JFile *jf = new JFile("a.txt");
	
	delete jf;
	exit(EXIT_SUCCESS);
}
