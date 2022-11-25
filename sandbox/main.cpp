#include <Typedefs.h>
#include <MemoryManager.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	int* ptr = new int(5);
	delete ptr;
	return 0;
}