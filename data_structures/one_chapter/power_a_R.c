#include <iostream>

using namespace std;

inline int sqr(int a) {
	return a * a;
}

int power(int n, int a) {
	if (0 == n)
		return 1;
	return (n & 1) ? sqr(power(n >> 1, a)) * a : sqr(power(n >> 1, a));
}

int main(int argc, char** argv)
{
	int n, a;
	while (cout << "input base, power: ",cin >> a >> n)
		cout << "the " << n << " power of " << a << " is " << power(n, a) << endl;

	return 0;
}
