#include "TextQuery.h"



using namespace std;

TextQuery::TextQuery(ifstream &is) : file(new std::vector<std::string>)
{
	string text;
	while (getline(is, text)) {		//对文件中每一行
		file->push_back(text);		//保存此行文本
		int n = file->size() - 1;	//当前行号
		istringstream line(text);	//将行文本分界为单词
		string word;
		while (line >> word) {		//对行中每个单词
			//如果单词不在wn中，以之为下标在wm中添加一项
			auto &lines = wm[word];	//lines是一个shared_ptr
			
			if (!lines)				//在我们第一次遇到这个单词时，此指针为空
				lines.reset(new set<line_no>);		//分配一个新的set
			lines->insert(n);		//将此行号插入set中
		}
	}
}

TextQuery::QueryResult TextQuery::query(const string &sought) const
{
	//如果未找到sought，我们将返回一个指向此set的指针
	shared_ptr<set<line_no>> nodata(new set<line_no>);
	//使用fingd而不是下标运算符来查找单词，避免将单词添加到wm中！
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return TextQuery::QueryResult(sought, nodata, file);	//未找到
	else
		return TextQuery::QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const TextQuery::QueryResult &qr)
{
	//如果找到了单词，打印出现次数和所有出现的位置
	os << qr.sought << " occurs " << qr.lines->size() << " times" << std::endl;;
	//打印打次出现的每一行
	for (auto num : *qr.lines)	//对set中每个单词
		//避免行号从0开始给用户带来的困扰
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;;
	return os;
}
