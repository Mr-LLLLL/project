#include <iostream>
#include <string>
#include <array>
#include <vector>

using std::cout;
using std::endl;

class test {
private:
	int i;
public:
	int get() {
		return i;
	}
};

void go(int num) {
	cout << "go num" << endl;
}


int main(int argc, char** argv)
{
	int *p = NULL;
	go(p);
	system("pause");
	return 0;
}
int i = 1;