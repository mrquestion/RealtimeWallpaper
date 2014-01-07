#pragma once

#ifndef __JFILE_HPP__
#define __JFILE_HPP__

#include <stdio.h>
#include <string.h>

class JFile {
	public:
		JFile(const char *);
		JFile(JFile &);
		~JFile();

		int create();
		int size();
		char *getName() { return filename; };
	//		int delete();

	private:
		FILE *file;
		char *filename;

		FILE *getFile() { return file; };
};

#endif
