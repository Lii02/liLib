#include "Hash.h"

namespace liLib {
	hash_t HashDJB2(byte* buffer, qword size) {
		hash_t hash = 5381;
		for (qword i = 0; i < size; i++)
			hash = ((hash << 5) + hash) + buffer[i];
		return hash;
	}

	hash_t HashSDBM(byte* buffer) {
		hash_t hash = 0;
		int c = *buffer;
		while (c = *buffer++) {
			hash = c + (hash << 6) + (hash << 16) - hash;
		}
		return hash;
	}
}