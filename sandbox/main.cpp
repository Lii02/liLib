#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>
#include <Str.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liString::PreInitialize();
	return 0;
}