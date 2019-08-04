#include <iostream>
#include <algorithm>
#include <iterator>
#include "TextQuery.h"
#include "Query.h"

//�����������Ľ��set�в����ڵ���
TextQuery::QueryResult NotQuery::eval(const TextQuery& text) const
{
	assert(std::cout << "NotQuery eval()" << std::endl);
	//ͨ��Query��������eval���������
	auto result = query.eval(text);
	//��ʼʱ���setΪ��
	auto ret_lines = std::make_shared<std::set<line_no>>();
	//���Ǳ��������������ֵ��������н��е���
	auto beg = result.begin(), end = result.end();
	//���������ļ��е�ÿһ�У�������в���result���У�������ӵ�ret_lines
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n) {
		//������ǻ�û�д�����result��������
		//��鵱ǰ���Ƿ����
		if (beg == end || *beg != n)
			ret_lines->insert(n);		//�������result���У������һ��
		else if (beg != end)
			++beg;		//���������ȡresult����һ�У�����еĻ���
	}
	return TextQuery::QueryResult(rep(), ret_lines, result.get_file());
}

TextQuery::QueryResult AndQuery::eval(const TextQuery& text) const
{
	assert(std::cout << "AndQuery eval()" << std::endl);
	//ͨ��Query���������е�����ã��Ի���������Ĳ�ѯ���set
	auto left = lhs.eval(text), right = rhs.eval(text);
	//����left��right������set
	auto ret_lines = std::make_shared<std::set<line_no>>();
	//��������Χ�Ľ���д��һ��Ŀ�ĵ�������
	//���ε��õ�Ŀ�ĵ�������ret���Ԫ��
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return TextQuery::QueryResult(rep(), ret_lines, left.get_file());
}

TextQuery::QueryResult OrQuery::eval(const TextQuery& text) const
{
	assert(std::cout << "OrQuery eval()" << std::endl);
	//ͨ��Query��Աlhs��rhs���е������
	//����eval����ÿ����������QueryResult
	auto right = rhs.eval(text), left = lhs.eval(text);
	//��������������кſ��������set��
	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	//�����Ҳ�����������õ��к�
	ret_lines->insert(right.begin(), right.end());
	//����һ���µ�QueryResult������ʾlhs��rhs�Ĳ���
	return TextQuery::QueryResult(rep(), ret_lines, left.get_file());
}

Query operator~(const Query &operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

Query operator&(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}


std::ostream &operator<<(std::ostream &os, const Query &query)
{
	//Query::repͨ������Query_baseָ���rep()�����������
	return os << query.rep();
}

