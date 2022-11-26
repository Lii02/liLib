#ifndef LILIB_ARRAY_H
#define LILIB_ARRAY_H
#include "Typedefs.h"

namespace liLib {
	template <typename T, qword size>
	class liArray {
	private:
		T buffer[size];
		qword index;
	public:
		liArray(bool setZero = true) {
			this->index = 0;
			memset(buffer, 0, size * sizeof(T));
		}

		void ResetIndex() {
			this->index = 0;
		}

		void Push(const T& data) {
			assert(index < size);
			buffer[index++] = data;
		}

		T Pop() {
			return buffer[--index];
		}

		LILIB_INLINE qword GetSize() { return size; }
		LILIB_INLINE qword GetAllocated() { return size * sizeof(T); }
		LILIB_INLINE T& operator[](qword index) { return buffer[index]; }
		LILIB_INLINE const T& operator[](qword index) const { return buffer[index]; }
	};
}

#endif