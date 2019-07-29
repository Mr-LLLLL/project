#include <sstream>
#include "QueryResult.h"
#include "TextQuery.h"

// 构造函数
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
	// 文件中的每一行
	std::string text;
	while (getline(is, text)) {
		// 保存此行文本
		file->push_back(text);
		// 行号从0开始
		int n = file->size() - 1;
		// 将每行存入istringstream
		std::istringstream line(text);
		// 记录每个单词
		std::string word;
		while (line >> word) {
			// 返回指向该单词的智能指针 
			auto &lines = wm[word];
			// 若指针位空，说明wm中有一个刚好创建的智能指针
			if (!lines)
				// 将该指针指向一个新的行号
				lines.reset(new std::set<line_no>);
			// 插入单词行号				
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