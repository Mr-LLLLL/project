#include <sstream>
#include "QueryResult.h"
#include "TextQuery.h"

// ���캯��
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
	// �ļ��е�ÿһ��
	std::string text;
	while (getline(is, text)) {
		// ��������ı�
		file->push_back(text);
		// �кŴ�0��ʼ
		int n = file->size() - 1;
		// ��ÿ�д���istringstream
		std::istringstream line(text);
		// ��¼ÿ������
		std::string word;
		while (line >> word) {
			// ����ָ��õ��ʵ�����ָ�� 
			auto &lines = wm[word];
			// ��ָ��λ�գ�˵��wm����һ���պô���������ָ��
			if (!lines)
				// ����ָ��ָ��һ���µ��к�
				lines.reset(new std::set<line_no>);
			// ���뵥���к�				
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const {
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}