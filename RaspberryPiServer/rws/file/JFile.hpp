#pragma once

#ifndef __JFILE_HPP__
#define __JFILE_HPP__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FILE_SUCCESS 0
#define FILE_ERROR -1
#define FILE_EXIST 1
#define FILE_SAME 2

#define FILENAME_LENGTH 256

#define DIRECTORY_MODE 0755
#define FILE_MODE 0644

typedef unsigned char boolean;
#define true 1
#define false 0

class JFile {
	public:
	JFile();
		JFile(const char *);
		JFile(JFile &);
		~JFile();

		int create();
		int mkdir();
		int size();
		char *getName() { return filename; };
		boolean exist();
		boolean isFile();
		boolean isDirectory();
		int rename(const char *);
		boolean remove();

	private:
		FILE *file;
		char *filename;
};

#endif
