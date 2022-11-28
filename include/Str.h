#ifndef LILIB_STR_H
#define LILIB_STR_H
#include "Typedefs.h"
#include "Hash.h"

#ifdef LILIB_UNICODE
typedef wchar_t liChar;
#define liText(x) L##x
#else
typedef char liChar;
#define liText(x) x
#endif

namespace liLib {
	class liString {
	private:
		liChar* buffer;
		qword size, capacity;
	public:
		static void PreInitialize();
		
		liString();
		liString(const liChar* str);
		liString(const liString& copy);
		~liString();

		void Initialize(qword startCapacity);
		void FreeBuffer();
		bool IsEmpty() const;
		void Clear();
		void Resize(qword newSize);
		void Append(liChar c);
		void Append(const liChar* str);
		void Append(const liString& str);
		liChar PopBack();
		void Insert(qword index, liChar c);
		void Erase(qword index);
		void Copy(const liString& copy);
		liChar* CStr();
		liString& operator=(const liString& copy);
		
		LILIB_INLINE qword GetLength() const { return size; }
		LILIB_INLINE qword GetCapacity() const { return size; }
		LILIB_INLINE qword GetAllocated() const { return capacity * sizeof(liChar); }
		LILIB_INLINE liChar& operator[](qword index) { return buffer[index]; }
		LILIB_INLINE const liChar& operator[](qword index) const { return buffer[index]; }
	};

	template <>
	struct liHash<liString> {
		hash_t operator()(const liString& str) {
			return HashDJB2((byte*)&str[0], str.GetLength() * sizeof(liChar));
		}
	};
}

#endif