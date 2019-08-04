#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <memory>
#include <algorithm>
class QueryResult;	//为了定义函数query的返回类型，这个定义是必须的
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	class QueryResult;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;	//输入文件
	//每个单词到它所在的行号的集合的映射
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class TextQuery::QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
	using line_it = std::set<line_no>::const_iterator;
public:
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), file(f) {}
	
	line_it begin() const {   
		return lines->cbegin();
	}
	line_it end() const {
		return lines->cend();
	}
	std::shared_ptr<std::vector<std::string>> get_file() {
		return file;
	}
	
private:
	std::string sought;		//查询单词
	std::shared_ptr<std::set<line_no>> lines;	//出现的行号
	std::shared_ptr<std::vector<std::string>> file;	//输入文件
};

#endif