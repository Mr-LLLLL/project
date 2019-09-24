#include <iostream>
#include <WinSock2.h>

using namespace std;
struct test {
	int i = 3;
	operator int() const {
		return i;
	}
};
void func(char c[]) {
	std::cout << typeid(c).name() << endl;
}
int main(int argc, char* argv[])
{
	void *p = operator new(32);
	new (p) int{ 0 };


	system("pause");
	return 0;
}