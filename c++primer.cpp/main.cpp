#include <iostream>
#include <tuple>
#include <string>
#include <Windows.h>
#include <process.h>
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
		cout << "base(int)" << endl;
	}
	virtual void print() {
		cout << "base pritn()" << endl;
	}
	void printf(int) {
		cout << "base::printf(int)" << endl;
	}
	void printf() {
		cout << "base::printf()" << endl;
	}
	int _elem;
	~base() {
		cout << "~base()" << endl;
	}
	void printPrivate() {
		cout << pri_elem << endl;
	}
private:
	int pri_elem = 0;
};

class derived1 : virtual public base {
public:
	derived1() : base(0), _elem(1) {}
	void print() override {
		cout << "derived1 print()" << endl;
	}
	void printf() {
		cout << "derived1::printf()" << endl;
	}
	void printPrivate() {
		base::printPrivate();
	}
	int _elem;
};

class derived2 : virtual public base {
public:
	derived2() : base(2) {}
};

using namespace std::placeholders;

template<typename T>
void test(T&& t) {
}
int main(int argc, char** argv)
{
	void merge(std::vector<int>, int, int, int);
	std::vector<int> v{ 1,4,5,6,2,3,4,5 };
	merge(v, 0, 4, v.size());
	for (auto& i : v)
		cout << i << endl;

	system("pause");
	return 0;
}

void merge(std::vector<int>& v, int lo, int mi, int hi) {
	std::vector<int> A;
	for (int i = lo; i < mi; i++)
		A.push_back(v[i]);
	for (int i = 0, j = lo, k = mi; i < mi;) {
		if (k == hi)
			v[j++] = A[i++];
		v[j++] = A[i] <= v[k] ? A[i++] : v[k++];
	}
}

unsigned WINAPI ThreadFunc(void *arg) {
	int i;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; ++i) {
		Sleep(1000);
		cout << "running thread" << endl;
	}
	return 0;
}
#include <tuple>