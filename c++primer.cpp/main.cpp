#include <iostream>
#include <cassert>
#include <array>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include "Sales_data.h"
#include <vector>
using std::cin;
using std::cout;
using std::endl;




template <int N>
constexpr int getsize(int (&a)[N]) {
	return N;
}

void go(int) {
	cout << "num" << endl;
}
void go(void*) {
	cout << "*p" << endl;
}

int main(int argc, char** argv)
{
	go(NULL);
	system("pause");
	return 0;
}