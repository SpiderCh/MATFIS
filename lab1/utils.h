#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>
#include <stdlib.h>

namespace math {
	unsigned long long power(unsigned long long a,
							 unsigned long long b,
							 unsigned long long c);
}

namespace Random {
	unsigned int generate(unsigned int up);
}

namespace types {
	typedef unsigned long long ull;
}

#endif // UTILS_H
