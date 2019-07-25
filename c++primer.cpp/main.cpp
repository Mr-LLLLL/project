#include <Bits.h>
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


int main(int argc, char** argv)
{
	Screen s1(5, 3);
	const Screen s2(3, 2);
	s1.move(2, 1).set('&').display(cout);
	s2.display(cout);
	system("pause");
	return 0;
}