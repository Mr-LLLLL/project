#include<iostream>
#include<fstream>
#include<string>
#include "TextQuery.h"
#include "Query.h"

using namespace std;

void runQueries(ifstream &);

int main(int argc, char* argv[])
{
	//���ļ����������в�ѯ�û�ָ���ĵ���
	ifstream infile("test.txt");
	//open������void,���������ö�������������صڶ�����������ֵ��
	//���infile��״̬
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
	//infile��һ��ifstream,ָ������Ҫ������ļ�
	TextQuery tq(infile);	//�����ļ���������ѯMap
							//���û���������ʾ�û�����Ҫ��ѯ�ĵ��ʣ���ɲ�ѯ����ӡ���
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string word;
		string s;
		getline(cin, s);
		istringstream line(s);
		Query q(""), q1 = q;
		//�������ļ�β���û�������"q"��ѭ����ֹ
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