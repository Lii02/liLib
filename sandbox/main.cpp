#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liList<int> list;
	for(int i = 0; i < 11; i++)
		list.Push(i);
	liHash<liList<int>> hash;
	printf("%ld\n", hash(list));
	return 0;
}