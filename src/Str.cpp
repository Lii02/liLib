#include "Str.h"
#include <string.h>

namespace liLib {
	typedef char* (*StringCopy)(liChar* dest, const liChar* src);
	static StringCopy copyFunction;

	void liString::PreInitialize() {
#ifdef LILIB_UNICODE
		copyFunction = wcscpy;
#else
		copyFunction = strcpy;
#endif
	}

	liString::liString() {
		Initialize(1);
	}
	
	liString::liString(const liChar* str) {
		qword len = strlen(str);
		Initialize(len + 1);
		copyFunction(buffer, str);
		this->size = capacity;
		buffer[len] = '\0';
	}

	liString::liString(const liString& copy) {
		this->buffer = nullptr;
		*this = copy;
	}
	
	liString::~liString() {
		FreeBuffer();
	}
	
	void liString::Initialize(qword startCapacity) {
		capacity = startCapacity;
		size = 0;
		buffer = new liChar[startCapacity];
	}

	void liString::FreeBuffer() {
		if (!buffer)
			delete[] buffer;
		this->size = 0;
		this->capacity = 0;
	}

	bool liString::IsEmpty() const {
		return size == 0;
	}

	void liString::Clear() {
		this->size = 0;
		buffer[0] = '\0';
	}

	void liString::Resize(qword newSize) {
		this->capacity = newSize;
		liChar* newBuffer = new liChar[capacity + 1];
		copyFunction(newBuffer, buffer);
		delete[] buffer;
		this->buffer = newBuffer;
	}

	void liString::Append(liChar c) {
		if (size >= capacity)
			Resize(capacity *= 2);
		buffer[size - 1] = c;
		buffer[size++] = '\0';
	}

	void liString::Append(const liChar* str) {
		qword len = strlen(str);
		for (qword i = 0; i < len; i++)
			Append(str[i]);
	}

	liChar liString::PopBack() {
		if (size == 0)
			return '\0';
		liChar c = buffer[size - 1];
		buffer[--size] = '\0';
		return c;
	}

	void liString::Copy(const liString& copy) {
		FreeBuffer();
		Initialize(copy.capacity + 1);
		copyFunction(buffer, copy.buffer);
		this->size = copy.size;
		buffer[size] = '\0';
	}

	liChar* liString::CStr() {
		return buffer;
	}

	liString& liString::operator=(const liString& copy) {
		Copy(copy);
		return *this;
	}
}