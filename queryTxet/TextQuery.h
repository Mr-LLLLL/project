#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <fstream>

class QueryResult;
// �����ļ�����
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	// ���캯��
	TextQuery(std::ifstream&);
	// ��ѯ����
	QueryResult query(const std::string&) const;
private:
	// �ļ�������ֻ��ָ�뱣��
	std::shared_ptr<std::vector<std::string>> file;
	// ����ÿ�������к�
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};



#endif