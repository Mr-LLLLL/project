#include <iostream>
#include <queue>
#include <iomanip>
#include <random>
#include <regex>
#include <bitset>
#include <functional>
#include <unordered_set>
#include <set>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <stack>
#include <sstream>
#include <fstream>
#include <cassert>
#include <array>
#include <string>
#include <array>
#include <vector>
#include <bitset>	
#include <unordered_map>
#include "Sales_data.h"
#include <vector>
#include "Screen.h"
#include "WindowMgr.h"
#include <Windows.h>
#include <iterator>
#include <forward_list>
#include <memory>
#include <exception>
#include <new>
using std::cin;
using std::cout;
using std::endl;

class base {
public:
	base() : _elem(0) {}
	base(int i) : _elem(i) {
		cout << "base()" << endl;
	}
	virtual void vv() {}
	int _elem;
	~base() {
		cout << "~base()" << endl;
	}
};

class derived1 : virtual public base {
public:
	derived1() : base(1) {}
};

class derived2 : virtual public base {
public:
	derived2() : base(2) {}
};

class deri : public derived2, public derived1 {
};
class out {
	using hello = int;
public:
	class in;
	out(int j) : i(j) {
		cout << "out" << endl;
	}
	int i;
	void print() {
		cout << "print() " << endl;
	}
	~out() {
		cout << "~out()" << endl;
	}
};
class out::in {
public:
	hello i = 0;
};
int main(int argc, char** argv)
{
	std::unordered_multimap<int, int> m{ { 2, 3} };
	m.insert({ 2, 4 });
	std::unordered_map<int, int> m1{ { 1,3 } };
	m1.insert({ 2, 4 });
	for (auto &i : m)
		cout << i.second << endl;



	system("pause");
	return 0;
}