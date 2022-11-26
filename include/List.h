#ifndef LILIB_LIST_H
#define LILIB_LIST_H
#include "Typedefs.h"
#include <string.h>

namespace liLib {
	template <typename T>
	class liList {
	private:
		T* buffer;
		qword size, capacity;
	public:
		liList(qword startCapacity = 1) {
			assert(startCapacity > 0);
			Initialize(startCapacity);
		}

		~liList() {
			FreeBuffer();
		}

		void Initialize(qword startCapacity) {
			this->size = 0;
			this->capacity = startCapacity;
			this->buffer = new T[capacity];
		}

		void FreeBuffer() {
			if (!buffer)
				return;
			delete[] buffer;
			this->size = 0;
			this->capacity = 0;
		}

		void Resize(qword newSize) {
			if (size == capacity)
				return;
			T* newBuffer = new T[capacity];
			memcpy(newBuffer, buffer, sizeof(T) * size);
			delete[] buffer;
			this->buffer = newBuffer;
			this->capacity = newSize;
		}

		bool IsEmpty() const {
			return size == 0;
		}

		void Clear() {
			this->size = 0;
		}

		void Push(const T& val) {
			if (size < capacity)
				Resize(capacity *= 2);
			buffer[size++] = val;
		}

		T Pop() {
			return buffer[--size];
		}

		void OptimizeMemory() {
			if (size == capacity)
				return;
			T* newBuffer = new T[size];
			memcpy(newBuffer, buffer, sizeof(T) * size);
			delete[] buffer;
			this->buffer = newBuffer;
			this->capacity = size;
		}
		
		LILIB_INLINE qword GetSize() const { return size; }
		LILIB_INLINE qword GetCapacity() const { return capacity; }
		LILIB_INLINE qword GetAllocated() const { return capacity * sizeof(T); }
		LILIB_INLINE T& operator[](qword index) { return buffer[index]; }
		LILIB_INLINE const T& operator[](qword index) const { return buffer[index]; }
	};
}

#endif