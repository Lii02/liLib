#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liList<int> list;
	list.Resize(10);
	list.Push(23);
	printf("%d\n", list.Pop());
	list.OptimizeMemory();
	return 0;
}