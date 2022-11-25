#include "MemoryManager.h"
#include <malloc.h>
#include <string.h>

namespace liLib {
	// TODO: Make these atomic
	static qword usage, allocations, frees;
	static liMemoryAlloc allocFunc;
	static liMemoryFree freeFunc;
	
	void liMemoryManager::Initialize() {
		ResetStats();
		allocFunc = malloc;
		freeFunc = free;
	}
	
	void* liMemoryManager::Allocate(qword size) {
		qword* ptr = (qword*)allocFunc(size + sizeof(qword));
		ptr[0] = size;
		usage += size;
		allocations++;
		return (void*)&ptr[1];
	}
	
	void liMemoryManager::Deallocate(void* ptr) {
		if (!ptr)
			return;
		qword* block64 = (qword*)ptr;
		size_t memory_size = block64[-1];
		allocations--;
		usage -= memory_size;
		freeFunc(&block64[-1]);
	}
	
	void* liMemoryManager::Reallocate(void* ptr, qword size) {
		void* newBlock = Allocate(size);
		memcpy(newBlock, ptr, size);
		Deallocate(ptr);
		return newBlock;
	}

	void liMemoryManager::ResetStats() {
		usage = 0;
		allocations = 0;
		frees = 0;
	}

	qword liMemoryManager::GetUsage() {
		return usage;
	}

	void liMemoryManager::SetFunctions(liMemoryAlloc newAllocFunc, liMemoryFree newFreeFunc) {
		allocFunc = newAllocFunc;
		freeFunc = newFreeFunc;
	}
}

void* operator new(qword size) noexcept {
	return liLib::liMemoryManager::Allocate(size);
}

void operator delete(void* ptr) noexcept {
	liLib::liMemoryManager::Deallocate(ptr);
}