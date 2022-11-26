#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liList<int> list;
	list.Push(23);
	liList<int> list2 = list;
	list2.Push(42);
	list2.Push(69);
	list2.Push(420);
	list2.Push(666);
	return 0;
}