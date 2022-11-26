#ifndef LILIB_TYPEDEFS_H
#define LILIB_TYPEDEFS_H

#include <stdio.h>
#include <stddef.h>
// TODO: Write custom assert
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;
typedef float float32;
typedef double float64;

#ifdef _MSC_VER
#define LILIB_INLINE __forceinline
#else
#define LILIB_INLINE ((always_packed)) __attribute__((always_inline))
#endif

namespace liLib {
	template <typename T>
	LILIB_INLINE void Swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
	
	template <typename T>
	LILIB_INLINE T Min(T a, T b) {
		return a < b ? a : b;
	}

	template <typename T>
	LILIB_INLINE T Max(T a, T b) {
		return a > b ? a : b;
	}

	template <typename T>
	LILIB_INLINE T Clamp(T value, T min, T max) {
		return Min(Max(value, min), max);
	}

	typedef unsigned long hash_t;
	template <typename T>
	struct liHash { };

	template <typename T>
	struct liSpan {
		T* data;
		qword size;
	};
}

#endif