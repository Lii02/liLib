#ifndef LILIB_HASH_H
#define LILIB_HASH_H
#include "Typedefs.h"

namespace liLib {
	hash_t HashDJB2(byte* buffer, qword size);
	hash_t HashSDBM(byte* buffer);
}

#endif