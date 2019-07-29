#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <string>
#include <vector>
#include <set>
#include <memory>
class QueryResult {
	// ��ӡ����
	friend std::ostream& print(std::ostream&, const QueryResult&);
	using line_no = std::vector<std::string >::size_type;
public:
	// ���캯��
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}
private:
	std::string sought;									// ��ѯ����
	std::shared_ptr<std::set<line_no>> lines;			// ���ֵ��к�
	std::shared_ptr<std::vector<std::string>> file;		// �����ļ�
};


#endif