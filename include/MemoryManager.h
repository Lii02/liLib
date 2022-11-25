#ifndef LILIB_MEMORY_MANAGER_H
#define LILIB_MEMORY_MANAGER_H
#include "Typedefs.h"

namespace liLib {
	typedef void* (*liMemoryAlloc)(qword size);
	typedef void (*liMemoryFree)(void* ptr);

	class liMemoryManager {
	public:
		static void Initialize();
		static void* Allocate(qword size);
		static void Deallocate(void* ptr); // free() and Free() is ambiguous
		static void* Reallocate(void* ptr, qword size);
		static void ResetStats();
		static qword GetUsage();
		static void SetFunctions(liMemoryAlloc newAllocFunc, liMemoryFree newFreeFunc);
	};

}

void* operator new(qword size) noexcept;
void operator delete(void* ptr) noexcept;

#endif