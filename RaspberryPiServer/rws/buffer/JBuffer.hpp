#pragma once

#ifndef __JBUFFER_HPP__
#define __JBUFFER_HPP__

#include <string.h>

#define BUFFER_SIZE 1024
#define BUFFER_ERROR -1

typedef unsigned char byte;
typedef unsigned char boolean;
//const unsigned char true = 1;
//const unsigned char false = 0;
#define true 1
#define false 0

class JBuffer {
	public:
		JBuffer();
		JBuffer(int);
		JBuffer(JBuffer &);
		~JBuffer();

		int get(int);
		boolean set(int, byte);
		byte *getBytes();
		int setBytes(byte *, int, int);
		void clear();
		int getSize() { return size; };
		void setSize(int);

	private:
		byte *buffer;
		int size;
};

#endif
