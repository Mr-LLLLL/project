#include <stack>
#include <iostream>
#include <string>

using namespace std;

// ���ü�������ܣ����ڴ������ɱ����ţ��
// ���⻹�ṩ���沨�����ʽ���沨�����ʽӵ�кܸߵ�Ч�ʣ�
class Solution {
public:
	int calculate(string s) {
		s += '\0';
		// ����ջ��һ����ֵջһ��������ջ
		stack<char> optr;
		stack<int> opnd;
		// �沨�����ʽ
		string RPN;
		int i = 0;
		optr.push('\0');
		// ��������ջΪ��ʱ������ѭ��
		while (!optr.empty()) {
			if (' ' == s[i])
				++i;
			// ��������֣�������ֵջ
			else if ('0' <= s[i] && s[i] <= '9') {
				RPN += s[i];            // �沨�����ʽ
				opnd.push(s[i] - '0');
				while ('0' <= s[++i] && s[i] <= '9') {
					RPN += s[i];
					int temp = opnd.top() * 10 + (s[i] - '0');
					opnd.pop();
					opnd.push(temp);
				}
			}
			// ����ǲ��������������ѹ�������ջ
			else {
				switch (orderBetween(optr.top(), s[i])) {
					// ջ����������ȼ����ڵ�ǰ�������ѹ��ջ
				case '<':
					optr.push(s[i++]);
					break;
					// ջ��������͵�ǰ��������ȼ�������������
					// ջ��Ϊ�����ţ���ǰ�����Ϊ������
					// ջ���͵�ǰ�������Ϊ\0
				case '=':
					optr.pop();
					++i;
					break;
					// ��ջ����������ȼ����ڵ�ǰ�������ֱ�Ӽ���
				case '>': {
					// ȡ�������������������ֵ��������
					char op = optr.top(); optr.pop();
					RPN += op;
					int num1 = opnd.top(); opnd.pop();
					int num2 = opnd.top(); opnd.pop();
					opnd.push(calcu(num2, op, num1));
					break;
				}
						  // ���ʽ��ʽ����
				default:
					return -1;
				}
			}
		}
		cout << RPN << endl;
		// ��ֵջ�����һ�������ǽ��
		return opnd.top();
	}
	// �����������ֵ
	int calcu(const int &num1, const char &op, const int &num2) {
		switch (op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		}
		return 0;
	}
	// �ж����ȼ�
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
	// ���ȼ��� ��ͬ���ȼ��������ջ�����ڵ�ǰ�������Ų�������ջ�� �����źͽ�����־���ȼ���� 
	const char pri[5][5] = {
		/*               ��ǰ�����           */
		/*            +    -    (    )   \0  */
		/* ջ  + */  '>', '>', '<', '>', '>',
		/* ��  - */  '>', '>', '<', '>', '>',
		/* ��  ( */  '<', '<', '<', '=', ' ',
		/* ��  ) */  ' ', ' ', ' ', ' ', ' ',
		/* �� \0 */  '<', '<', '<', ' ', '=',
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