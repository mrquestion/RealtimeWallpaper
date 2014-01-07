#include "JBuffer.hpp"

#include <stdio.h>

JBuffer::JBuffer() {
	JBuffer(BUFFER_SIZE);
}
JBuffer::JBuffer(int size) {
	this->size = size;
	this->buffer = new byte[size];
}
JBuffer::JBuffer(JBuffer &jb) {
	JBuffer(jb.getSize());
	int i, max = this->size;
	for (i=0; i<max; i++) {
		this->buffer[i] = jb.get(i);
	}
}
JBuffer::~JBuffer() {
	delete [] buffer;
}

int JBuffer::get(int i) {
	if (i > this->size-1) return BUFFER_ERROR;
	return this->buffer[i];
}
boolean JBuffer::set(int i, byte b) {
	if (i > this->size-1) return false;
	else {
		this->buffer[i] = b;
		return true;
	}
}
byte *JBuffer::getBytes() {
	byte *bs = new byte[this->size];
	int i, max = this->size;
	for (i=0; i<max; i++) {
		bs[i] = this->buffer[i];
	}
	return bs;
}
int JBuffer::setBytes(byte *bs, int offset, int length) {
	if (offset > this->size-1) return false;
	else {
		int i, max = this->size < offset+length ? this->size : offset + length;
		for (i=offset; i<max; i++) {
			this->buffer[i] = bs[i-offset];
		}
		return max - offset;
	}
}
void JBuffer::clear() {
	memset(this->buffer, 0, this->size);
}
void JBuffer::setSize(int size) {
	byte *bs = new byte[size];
	memset(bs, 0, size);

	int i, max = this->size < size ? this->size : size;
	for (i=0; i<max; i++) {
		bs[i] = buffer[i];
	}

	delete [] buffer;

	this->size = size;
	buffer = bs;
}
