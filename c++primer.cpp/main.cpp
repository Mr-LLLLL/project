#include <iostream>
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
using std::cin;
using std::cout;
using std::endl;

struct test {
	int i;
	test(int ii = 0) : i(ii) { cout << "test()" << endl; }
	test(int ii, int i2) : i(ii) { cout << "test()" << endl; }
	test(const test &t) : i(t.i) { cout << "test(&)" << endl; }
	test(const test &&t) : i(t.i) { cout << "test(&&)" << endl; }
	~test() {
		cout << "~test()" << endl;
	}
	test& operator = (const test &t) {
		cout << "operator=" << endl;
		i = t.i;
		return *this;
	}
};

void compare() {
	test *p = new test(1);
	throw std::runtime_error("hello");
	delete p;
	cout << "compare()" << endl;
}
int main(int argc, char** argv)
{
	std::allocator<test> alloc;
	std::unique_ptr<test> p(alloc.allocate(10));
	test *q = std::uninitialized_fill_n(p.get(), 10, 2);
	alloc.destroy(p.get());
	alloc.construct(p.get(), 3);
	cout << p->i << endl;
	cout << typeid(std::vector<test>::iterator).name() << endl;
	
	system("pause");
	return 0;
}