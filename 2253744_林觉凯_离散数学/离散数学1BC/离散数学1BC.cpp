#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;
//typedef map<int, bool> Map_ib;

Map_ci priority;

Map_ic getProposition(string formula);
int findProposition(Map_ic, char p);
int pow2(int n);
Map_ii toBinary(int n_proposition, int index);
int calculate(string formula, Map_ic pSet, Map_ii value);
void check(stack<int>& value, stack<char>& opter);
int Judgecorrect(string str);		//检查输入的公式是否合法的函数
//主函数的实现
int main()
{
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//运算符优先级

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "请输入一个合法的命题公式: " << endl;
	string formula;//检查输入的命题公式是否合法
enter:	cin >> formula;
	int Flag = Judgecorrect(formula);
	switch (Flag)
	{
	case 1:
		cout << "存在括号的不匹配！输入失败！请再次输入：" << endl;
		goto enter;
		break;
	case 2:
		cout << "在连接词后无命题变项！输入失败！请再次输入：" << endl;
		goto enter;
		break;
	case 3:
		cout << "开头的连接词输入错误！输入失败！请再次输入：" << endl;
		goto enter;
		break;
	case 4:
		cout << "表达式中含有非法输入字符！输入失败！请再次输入：" << endl;
		goto enter;
		break;
	case 5:
		cout << "合法的变量或连接词不能连续出现！输入失败！请再次输入：" << endl;
		goto enter;
		break;
	default:
		break;
	}
	Map_ic proposition_set = getProposition(formula);
	cout << "该式子中的变量个数为：" << proposition_set.size() << endl << "输出真值表如下：" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++) 
		cout << proposition_set[i] << "\t";
	cout << formula << endl;
	int* m;
	m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //该数组依次存放命题公式的各行(0或1)的运算结果的值
	// int z = pow2(proposition_set.size());
	// cout << z << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		Map_ii bina_set = toBinary(proposition_set.size(), i);
		for (unsigned int j = 0; j < bina_set.size(); j++)
		{
			cout << bina_set[j] << "\t";
		}
		int result = calculate(formula, proposition_set, bina_set);
		//m[i] = result;
		*(m + i) = result;
		cout << result << endl;
	}
	int n_m = 0, n_M = 0;
	cout << "该命题公式的主析取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 1)//主析取范式，值为真
		{
			if (n_m == 0)//第一个范式
				cout << "m<" << i << ">";
			else
				cout << " \\/ m<" << i << "> ";
			n_m++;
		}
	}
	if (n_m == 0)//没有范式
	{
		cout << "0";
	}
	cout << endl;
	cout << "该命题公式的主合取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 0)//主合取范式，值为假
		{
			if (n_M == 0)//第一个范式
				cout << "M<" << i << ">";
			else
				cout << " /\\ M<" << i << "> ";
			n_M++;
		}
	}
	if (n_M == 0)//没有范式
		cout << "0";
	cout << endl;
	return 0;
}
//判断错误输入
int Judgecorrect(string formula)
{
	stack<char> Judge_Stack;		//设置一个栈来暂存符号
	size_t i = 0, length = formula.length();	//循环变量i，表达式的长度length
	//检查括号是否匹配
	while (i < length)
	{
		if (formula[i] == '(')//如果是左括号
			Judge_Stack.push(formula[i]);
		else if (formula[i] == ')' && !Judge_Stack.empty())//如果有右括号并且栈内存在左括号
			Judge_Stack.pop();
		else if (formula[i] == ')')//如果栈内不存在左括号但是存在右括号
			return 1;
		i++;
	}
	if (!Judge_Stack.empty())
		return 1;
	//return 1说明括号检测不匹配
	i = 0;
	//检查在操作符后是否都有命题变项
	if (formula[length - 1] == '!' || formula[length - 1] == '|' ||
		formula[length - 1] == '&' || formula[length - 1] == '~' ||
		formula[length - 1] == '^')
		return 2;
	//return 2说明在操作符后不存在命题变项
	//检查开头是否存在非法操作符
	if (formula[0] == '|' || formula[0] == '&' || formula[0] == '~' || formula[0] == '^')
		return 3;
	//return 3表示开头的符号非法
	//检查命题公式中是否存在非法符号
	while (i < length)
	{
		if (formula[i] == '(' || formula[i] == ')' ||
			(formula[i] >= 'a' && formula[i] <= 'z') ||
			(formula[i] >= 'A' && formula[i] <= 'Z') ||
			formula[i] == '!' || formula[i] == '|' ||
			formula[i] == '&' || formula[i] == '^' ||
			formula[i] == '~')
			i++;
		else
			return 4;
	}
	//return 4说明在公式中存在非法字符
	//检查合法字符是否出现连续的情况
	i = 0;
	while (i < length)
	{
		if ((formula[i] >= 'a' && formula[i] <= 'z') ||
			(formula[i] >= 'A' && formula[i] <= 'Z'))
			if ((formula[i + 1] >= 'a' && formula[i + 1] <= 'z') ||
				(formula[i + 1] >= 'A' && formula[i + 1] <= 'Z'))
				return 5;
		if (formula[i] == '!' || formula[i] == '|' ||
			formula[i] == '&' || formula[i] == '^' ||
			formula[i] == '~')
			if (formula[i + 1] == '!' || formula[i + 1] == '|' ||
				formula[i + 1] == '&' || formula[i + 1] == '^' ||
				formula[i + 1] == '~')
				return 5;
		i++;
	}
	//return 5说明存在合法字符出现连续的情况
	return 0;
}
//返回-1，表示该命题变项尚未被遍历过，可计数；否则说明该命题变项已被遍历过，则不重复计数。另外，还可以返回指定命题变项的下标
int findProposition(Map_ic pSet, char p) 
{
	Map_ic::iterator it = pSet.begin();
	while (it != pSet.end())
	{
		if (it->second == p)
			return it->first;
		it++;
	}
	return -1;
}
//该函数返回所输入公式中的命题变项(不包括运算符)
Map_ic getProposition(string formula) 
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//遍历所有命题变项
			int r = findProposition(proposition, c);
			//cout << r << endl;
			if (r == -1)
			{
				//说明该命题变项尚未被遍历过
				proposition[n_proposition] = c;
				n_proposition++;
			}
		}
		else if (!priority.count(c))
		{
			cout << c << " is undefined!" << endl;
			exit(2);
		}
	}
	return proposition;
}
//该函数返回命题变项的二进制(0或1)取值
Map_ii toBinary(int n_proposition, int index)  
{
	Map_ii result;
	for (int i = 0; i < n_proposition; i++)
	{
		int r = index % 2;
		result[n_proposition - 1 - i] = r;
		index = index / 2;
	}
	return result;
}
//该函数返回指定数字的二次方的值
int pow2(int n)    
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}
//该函数返回给定，命题变项(值取0或1，可含括号)组合的运算结果
int calculate(string formula, Map_ic pSet, Map_ii value) 
{
	stack<char> opter;
	stack<int> pvalue;
	opter.push('#');
	formula = formula + "#";
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			pvalue.push(value[findProposition(pSet, c)]);
		else
		{
			//此时遍历的是运算符
			char tmp = opter.top();
			if (priority[tmp] > priority[c])
			{
				while (priority[tmp] > priority[c] && tmp != '(')
				{
					check(pvalue, opter);
					tmp = opter.top();
					if (tmp == '#' && c == '#')
						return pvalue.top();
				}
				opter.push(c);
			}
			else
				opter.push(c);
		}
	}
	return -1;
}
//该函数返回两个命题变项(取值0或1)的各种运算结果(0或1)
void check(stack<int>& value, stack<char>& opter) 
{
	int p, q, result;
	char opt = opter.top();

	switch (opt)
	{
	case '&':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p && q;
		value.push(result);
		opter.pop();
		break;

	case '|':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p || q;
		value.push(result);
		opter.pop();
		break;

	case '!':
		p = value.top();
		value.pop();
		result = !p;
		value.push(result);
		opter.pop();
		break;

	case '^':
		q = value.top();
		value.pop();
		p = value.top();
		value.pop();
		result = !p || q;
		value.push(result);
		opter.pop();
		break;

	case '~':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = (!p || q) && (p || !q);
		value.push(result);
		opter.pop();
		break;

	case '#':
		break;

	case '(':
		break;

	case ')':
		opter.pop();
		while (opter.top() != '(')
			check(value, opter);
		if (opter.top() == '(')
			opter.pop();
		break;
	default:
		break;
	}
}