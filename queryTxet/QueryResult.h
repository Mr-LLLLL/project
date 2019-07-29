#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <string>
#include <vector>
#include <set>
#include <memory>
class QueryResult {
	// 打印函数
	friend std::ostream& print(std::ostream&, const QueryResult&);
	using line_no = std::vector<std::string >::size_type;
public:
	// 构造函数
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}
private:
	std::string sought;									// 查询单词
	std::shared_ptr<std::set<line_no>> lines;			// 出现的行号
	std::shared_ptr<std::vector<std::string>> file;		// 输入文件
};


#endif