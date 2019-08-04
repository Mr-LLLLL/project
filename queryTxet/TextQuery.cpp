#include "TextQuery.h"



using namespace std;

TextQuery::TextQuery(ifstream &is) : file(new std::vector<std::string>)
{
	string text;
	while (getline(is, text)) {		//���ļ���ÿһ��
		file->push_back(text);		//��������ı�
		int n = file->size() - 1;	//��ǰ�к�
		istringstream line(text);	//�����ı��ֽ�Ϊ����
		string word;
		while (line >> word) {		//������ÿ������
			//������ʲ���wn�У���֮Ϊ�±���wm�����һ��
			auto &lines = wm[word];	//lines��һ��shared_ptr
			
			if (!lines)				//�����ǵ�һ�������������ʱ����ָ��Ϊ��
				lines.reset(new set<line_no>);		//����һ���µ�set
			lines->insert(n);		//�����кŲ���set��
		}
	}
}

TextQuery::QueryResult TextQuery::query(const string &sought) const
{
	//���δ�ҵ�sought�����ǽ�����һ��ָ���set��ָ��
	shared_ptr<set<line_no>> nodata(new set<line_no>);
	//ʹ��fingd�������±�����������ҵ��ʣ����⽫������ӵ�wm�У�
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return TextQuery::QueryResult(sought, nodata, file);	//δ�ҵ�
	else
		return TextQuery::QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const TextQuery::QueryResult &qr)
{
	//����ҵ��˵��ʣ���ӡ���ִ��������г��ֵ�λ��
	os << qr.sought << " occurs " << qr.lines->size() << " times" << std::endl;;
	//��ӡ��γ��ֵ�ÿһ��
	for (auto num : *qr.lines)	//��set��ÿ������
		//�����кŴ�0��ʼ���û�����������
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;;
	return os;
}
