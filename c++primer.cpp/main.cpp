#include <iostream>
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

class base{
public:
	virtual void print() {
		cout << "base()" << endl;
	}
	void printf() {
		cout << "basef" << endl;
	}
	void printf(int) {
		cout << "basef(int)" << endl;
	}
};

class base1 {
	virtual void printf() {
		cout << "base1f" << endl;
	}
protected:
	int i = 0;
};

class derived : public base , private base1 {
public:
	using base::printf;
	derived() = default;
	void print() override {
		cout << "derived()" << endl;
	}
	void printf() {
		cout << i << endl;
	}
private:
	int j = 1;
};

int main(int argc, char** argv)
{
	std::vector<int> v{ 1,3,4,5 };
	cout << typeid(v.size()).name() << endl;
	cout << UINT_MAX << endl;
	system("pause");
	return 0;
}