#include<iostream>
#include<fstream>
#include<string>
#include "TextQuery.h"
#include "Query.h"

using namespace std;

void runQueries(ifstream &);

int main(int argc, char* argv[])
{
	//打开文件，将在其中查询用户指定的单词
	ifstream infile("test.txt");
	//open本身返回void,所以我们用逗号运算符（返回第二个运算对象的值）
	//检查infile的状态
	if (!infile) {
		cerr << "no input file" << endl;
		return EXIT_FAILURE;
	}
	runQueries(infile);
	system("pause");
	return 0;
}


void runQueries(ifstream &infile)
{
	//infile是一个ifstream,指向我们要处理的文件
	TextQuery tq(infile);	//保存文件并建立查询Map
							//与用户交互：提示用户输入要查询的单词，完成查询并打印结果
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string word;
		string s;
		getline(cin, s);
		istringstream line(s);
		Query q(""), q1 = q;
		//若遇到文件尾或用户输入了"q"是循环终止
		line >> word;
		if (word == "q")
			break;
		if (word[0] == '~')
			q = ~Query(string(word.begin() + 1, word.end()));
		else
			q = Query(word);
		cout << "one countinue" << endl;
		while (line >> word) {
			if (word == "&") {
				line >> word;
				if (word[0] == '~')
					q1 = ~Query(string(word.begin() + 1, word.end()));
				else
					q1 = Query(word);
				q = q & q1;
				cout << "two point one continue and " << q << endl;
			}
			else {
				line >> word;
				if (word[0] == '~')
					q1 = ~Query(string(word.begin() + 1, word.end()));
				else
					q1 = Query(word);
				q = q | q1;
				cout << "two opint two continue and " << q << endl;
			}
			cout << q;	
		}
		print(cout, q.eval(tq)) << endl;
	}
}