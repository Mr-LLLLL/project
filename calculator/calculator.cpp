#include <stack>
#include <iostream>
#include <string>

using namespace std;

// 采用计算器框架，用于此题等于杀鸡用牛刀
// 此题还提供了逆波兰表达式（逆波兰表达式拥有很高的效率）
class Solution {
public:
	int calculate(string s) {
		s += '\0';
		// 两个栈，一个数值栈一个操作符栈
		stack<char> optr;
		stack<int> opnd;
		// 逆波兰表达式
		string RPN;
		int i = 0;
		optr.push('\0');
		// 当操作符栈为空时，结束循环
		while (!optr.empty()) {
			if (' ' == s[i])
				++i;
			// 如果是数字，存入数值栈
			else if ('0' <= s[i] && s[i] <= '9') {
				RPN += s[i];            // 逆波兰表达式
				opnd.push(s[i] - '0');
				while ('0' <= s[++i] && s[i] <= '9') {
					RPN += s[i];
					int temp = opnd.top() * 10 + (s[i] - '0');
					opnd.pop();
					opnd.push(temp);
				}
			}
			// 如果是操作符，运算或者压入操作符栈
			else {
				switch (orderBetween(optr.top(), s[i])) {
					// 栈顶运算符优先级低于当前运算符，压入栈
				case '<':
					optr.push(s[i++]);
					break;
					// 栈顶运算符和当前运算符优先级相等有两种情况
					// 栈顶为左括号，当前运算符为右括号
					// 栈顶和当前运算符都为\0
				case '=':
					optr.pop();
					++i;
					break;
					// 若栈顶运算符优先级大于当前运算符，直接计算
				case '>': {
					// 取出运算符和所需运算数值进行云算
					char op = optr.top(); optr.pop();
					RPN += op;
					int num1 = opnd.top(); opnd.pop();
					int num2 = opnd.top(); opnd.pop();
					opnd.push(calcu(num2, op, num1));
					break;
				}
						  // 表达式格式错误
				default:
					return -1;
				}
			}
		}
		cout << RPN << endl;
		// 数值栈中最后一个数就是结果
		return opnd.top();
	}
	// 根据运算符求值
	int calcu(const int &num1, const char &op, const int &num2) {
		switch (op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		}
		return 0;
	}
	// 判断优先级
	const char &orderBetween(const char &ch1, const char &ch2) {
		int i, j;
		switch (ch1) {
		case '+':
			i = 0;
			break;
		case '-':
			i = 1;
			break;
		case '(':
			i = 2;
			break;
		case ')':
			i = 3;
			break;
		case '\0':
			i = 4;
			break;
		}
		switch (ch2) {
		case '+':
			j = 0;
			break;
		case '-':
			j = 1;
			break;
		case '(':
			j = 2;
			break;
		case ')':
			j = 3;
			break;
		case '\0':
			j = 4;
			break;
		}
		return pri[i][j];
	}
	// 优先级表， 相同优先级运算符，栈顶大于当前，右括号不可能入栈， 左括号和结束标志优先级最低 
	const char pri[5][5] = {
		/*               当前运算符           */
		/*            +    -    (    )   \0  */
		/* 栈  + */  '>', '>', '<', '>', '>',
		/* 顶  - */  '>', '>', '<', '>', '>',
		/* 运  ( */  '<', '<', '<', '=', ' ',
		/* 算  ) */  ' ', ' ', ' ', ' ', ' ',
		/* 符 \0 */  '<', '<', '<', ' ', '=',
	};
};
// T:O(n) S:O(1)

int main(int argc, char **argv) {
	string s;
	getline(cin, s);
	cout << Solution().calculate(s) << endl;
	system("pause");
	return 0;
}