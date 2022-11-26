#ifndef LILIB_LIST_H
#define LILIB_LIST_H
#include "Typedefs.h"
#include "Hash.h"
#include <string.h>

#define liStack(T) liLib::liList<T>
#define liQueue(T) liStack(T)

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

		liList(const liList& copy) {
			buffer = nullptr;
			*this = copy;
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
			if (size >= capacity)
				Resize(capacity *= 2);
			buffer[size++] = val;
		}

		T PopBack() {
			return buffer[--size];
		}

		T PopFront() {
			T ret = buffer[0];
			for (qword i = 0; i < size - 1; i++)
				buffer[i] = buffer[i + 1];
			size--;
			return ret;
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

		void Copy(const liList& copy) {
			FreeBuffer();
			this->size = copy.size;
			this->capacity = copy.capacity;
			this->buffer = new T[capacity];
			memcpy(buffer, copy.buffer, sizeof(T) * size);
		}

		liList& operator=(const liList& copy) {
			Copy(copy);
			return *this;
		}
		
		LILIB_INLINE qword GetSize() const { return size; }
		LILIB_INLINE qword GetCapacity() const { return capacity; }
		LILIB_INLINE qword GetAllocated() const { return capacity * sizeof(T); }
		LILIB_INLINE T& operator[](qword index) { return buffer[index]; }
		LILIB_INLINE const T& operator[](qword index) const { return buffer[index]; }
	};

	typedef liList<byte> liByteBuffer;
	typedef liList<float> liFloatBuffer;

	template <typename T>
	struct liHash<liList<T>> {
		hash_t operator()(const liList<T>& list) const {
			byte* buffer = (byte*)&list[0];
			return HashDJB2(buffer, list.GetSize() * sizeof(T));
		}
	};
}

#endif