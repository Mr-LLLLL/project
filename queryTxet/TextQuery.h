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
// 保存文件内容
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	// 构造函数
	TextQuery(std::ifstream&);
	// 查询单词
	QueryResult query(const std::string&) const;
private:
	// 文件内容用只能指针保存
	std::shared_ptr<std::vector<std::string>> file;
	// 保存每个单词行号
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};



#endif