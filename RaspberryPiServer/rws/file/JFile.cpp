#include "JFile.hpp"

#define logh(x) printf(#x": 0x%08x\n",x)

JFile::JFile(const char *filename) {
	this->filename = new char[FILENAME_LENGTH];
	strcpy(this->filename, filename);
}
JFile::JFile(JFile &jf) {
	this->filename = new char[FILENAME_LENGTH];
	strcpy(this->filename, jf.getName());
}
JFile::~JFile() {
	delete [] this->filename;
}

int JFile::create() {
	JFile *jf = new JFile(this->filename);
	boolean exist = jf->exist();
	if (exist) return FILE_EXIST;
	else {
		int result = creat(this->filename, FILE_MODE);
		if (result == FILE_ERROR) return result;
		else return FILE_SUCCESS;
	}
}
int JFile::mkdir() {
	JFile *jf = new JFile(this->filename);
	boolean exist = jf->exist();
	if (exist) return FILE_EXIST;
	else {
	    int result = ::mkdir(this->filename, DIRECTORY_MODE);
		return result;
	}
}
int JFile::size() {
	struct stat status;
	int result = ::stat(this->filename, &status);
	if (result == FILE_SUCCESS) return status.st_size;
	else return FILE_ERROR;
}
boolean JFile::exist() {
	int result = ::access(this->filename, F_OK);
	if (result == FILE_SUCCESS) return true;
	else return false;
}
boolean JFile::isFile() {
	struct stat status;
	int result = ::stat(this->filename, &status);
	if (result == FILE_SUCCESS) {
	    if (S_ISDIR(status.st_mode) == false) {
			return true;
		}
		else return false;
	}
	else return false;
}
boolean JFile::isDirectory() {
	struct stat status;
	int result = ::stat(this->filename, &status);
	if (result == FILE_SUCCESS) {
		if (S_ISDIR(status.st_mode)) {
			return true;
		}
		else return false;
	}
	else return false;
}
int JFile::rename(const char *filename) {
	if (strcmp(this->filename, filename) == 0) {
		return FILE_SAME;
	}
	else {
		JFile *jf = new JFile(filename);
		boolean exist = jf->exist();
		delete jf;
		if (exist) return FILE_EXIST;
   		else {
			int result = ::rename(this->filename, filename);
			if (result == FILE_SUCCESS) {
				strcpy(this->filename, filename);
			}
			return result;
		}
	}
}
boolean JFile::remove() {
	int result = ::remove(this->filename);
	if (result == FILE_SUCCESS) return true;
	else return false;
}
