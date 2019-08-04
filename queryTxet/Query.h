#ifndef QUERY_H
#define QUERY_H

#include <cassert>
#include <string>
#include <memory>
#include "TextQuery.h"



//这是一个抽象基类，具体的查询类型从中派生，所有的成员都是private的
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;			//用于eval函数
	virtual ~Query_base() = default;
private:
	//eval返回与当前Query匹配的QueryResult
	virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
	//ret是表示查询的一个string
	virtual std::string rep() const = 0;
};

class WordQuery : public Query_base {
	friend class Query;			//Query使用WordQuery构造函数
	WordQuery(const std::string &);				//具体的类：Word_Query将定义所有继承而来的纯虚函数
	TextQuery::QueryResult eval(const TextQuery &) const override;
	std::string rep() const override;
	std::string query_word;						//要查找的单词
};

//这是一个管理Query_base继承体系的接口类
class Query {
	//这些运算符需要访问接受shred_ptr的构造函数，而该函数是私有的
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&);
	//接口函数：调用对应的Query_base操作
	TextQuery::QueryResult eval(const TextQuery &) const;
	std::string rep() const;
private:
	Query(std::shared_ptr<Query_base> query);
	std::shared_ptr<Query_base> q;
};

class NotQuery : public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q);
	//具体的类：NotQuery将定义所有继承而来的纯虚函数
	std::string rep() const override;
	TextQuery::QueryResult eval(const TextQuery&) const override;
	Query query;
};

class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s);
	//抽象类：BinaryQuery不定义eval
	std::string rep() const override;
	Query lhs, rhs;					//左侧和右侧运算对象
	std::string opSym;				//运算符的名字
};

class AndQuery : public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right);
	//具体的类：AndQuery继承了rep并且定义了其他虚函数
	TextQuery::QueryResult eval(const TextQuery&) const;
};

class OrQuery : public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right);
	TextQuery::QueryResult eval(const TextQuery&) const;
};

// class WordQuery's member
inline WordQuery::WordQuery(const std::string &s) : query_word(s) { }

inline TextQuery::QueryResult WordQuery::eval(const TextQuery &t) const
{
	assert(std::cout << "WordQuery eval()" << std::endl);
	return t.query(query_word);
}

inline std::string WordQuery::rep() const
{
	assert(std::cout << "WordQuery rep()" << std::endl);
	return query_word;
}

// class Query's member
inline Query::Query(const std::string& s) : q(new WordQuery(s))
{
	assert(std::cout << "Query(const std::string&)" << std::endl);
}		//构建一个新的WordQuery

inline TextQuery::QueryResult Query::eval(const TextQuery &t) const
{
	assert(std::cout << "Query eval()" << std::endl);
	return q->eval(t);
}

inline std::string Query::rep() const
{
	assert(std::cout << "Query rep()" << std::endl);
	return q->rep();
}

inline Query::Query(std::shared_ptr<Query_base> query) : q(query)
{
	assert(std::cout << "Query(std::shared_ptr<Query_base>)" << std::endl);
}

// class NotQuery's member
inline NotQuery::NotQuery(const Query &q) : query(q) { 
	assert(std::cout << "NotQuery(cosnt Query&)" << std::endl);
}

inline std::string NotQuery::rep() const
{
	assert(std::cout << "NotQuery rep()" << std::endl);
	return "~(" + query.rep() + ")";
}

// class BinaryQuery's member
inline BinaryQuery::BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s)
{
	assert(std::cout << "BinaryQuery(const Query &, const Query &, std::string" << std::endl);
}

inline std::string BinaryQuery::rep() const {
	assert(std::cout << "BinaryQuery rep()" << std::endl);
	return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
}

// class AndQuery's member
inline AndQuery::AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&")
{
	assert(std::cout << "AndQuery(const Query &left, const Query &right)" << std::endl);
}

// class OrQuery's member
inline OrQuery::OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|")
{
	assert(std::cout << "OrQuery(const Query &left,const Query &right" << std::endl);
}



Query operator~(const Query &operand);
Query operator&(const Query &lhs, const Query &rhs);
Query operator|(const Query &lhs, const Query &rhs);
std::ostream &operator<<(std::ostream &os, const Query &query);
#endif