#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>
#include <Str.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liString::PreInitialize();

	liString str = liText("Hello World!");
	str.Append('!');
	liChar c = str.PopBack();
	printf("%s %c\n", str.CStr(), c);
	return 0;
}