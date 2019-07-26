#include <iostream>
#include <cassert>
#include <array>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include "Sales_data.h"
#include <vector>
#include "Screen.h"
#include "WindowMgr.h"
using std::cin;
using std::cout;
using std::endl;

int get() {
	return 2;
}

struct test {
	int i = 0;
	test() = default;
	const int ii = i;
};

int main(int argc, char** argv)
{
	mutable const int i = 5;
	int&& t = 5;
	const int &r = t;
	cout << r << endl;
	system("pause");
	return 0;           
}