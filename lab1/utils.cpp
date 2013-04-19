#include "utils.h"

namespace Random {
	unsigned int generate(unsigned int up)
	{
		struct timeval tp;
		gettimeofday(&tp, nullptr);
		srand(tp.tv_usec);

		return rand() % (up + 1);
	}
}

namespace math {
	unsigned long long power(unsigned long long a,
							 unsigned long long b,
							 unsigned long long c)
	{
		a %= c;
		unsigned long long res = 1;
		while (b) {
			if (b & 1)
				res =(res*a)%c;
			a = (a * a) % c;
			b >>= 1;
		}

		return res;
	}
}
