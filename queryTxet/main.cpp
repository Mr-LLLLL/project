#include <iostream>
#include <string>
#include "QueryResult.h"
#include "TextQuery.h"
using std::cin;
using std::cout;
using std::endl;

void runQueries(std::ifstream &infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "enter word to look for, or qu to quit: ";
		std::string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " times"
		<< endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") "
		<< *(qr.file->begin() + num) << endl;
	return os;
}

int main(int argc, char** argv)
{
	system("pause");
	return 0;
}

