#include <Typedefs.h>
#include <MemoryManager.h>
#include <List.h>
#include <Str.h>

using namespace liLib;

int main(int argc, char** argv) {
	liMemoryManager::Initialize();
	liString::PreInitialize();
	liString str = "Hello world!";
	str.Append("Test");
	liString str2 = "Li";
	str.Append(str2);
	liHash<liString> hash;
	printf("%s %d\n", str.CStr(), hash(str));
	return 0;
}