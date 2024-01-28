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
int Judgecorrect(string str);		//�������Ĺ�ʽ�Ƿ�Ϸ��ĺ���
//��������ʵ��
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
	//��������ȼ�

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "������һ���Ϸ������⹫ʽ: " << endl;
	string formula;//�����������⹫ʽ�Ƿ�Ϸ�
enter:	cin >> formula;
	int Flag = Judgecorrect(formula);
	switch (Flag)
	{
	case 1:
		cout << "�������ŵĲ�ƥ�䣡����ʧ�ܣ����ٴ����룺" << endl;
		goto enter;
		break;
	case 2:
		cout << "�����Ӵʺ�������������ʧ�ܣ����ٴ����룺" << endl;
		goto enter;
		break;
	case 3:
		cout << "��ͷ�����Ӵ������������ʧ�ܣ����ٴ����룺" << endl;
		goto enter;
		break;
	case 4:
		cout << "���ʽ�к��зǷ������ַ�������ʧ�ܣ����ٴ����룺" << endl;
		goto enter;
		break;
	case 5:
		cout << "�Ϸ��ı��������Ӵʲ����������֣�����ʧ�ܣ����ٴ����룺" << endl;
		goto enter;
		break;
	default:
		break;
	}
	Map_ic proposition_set = getProposition(formula);
	cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << "�����ֵ�����£�" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++) 
		cout << proposition_set[i] << "\t";
	cout << formula << endl;
	int* m;
	m = (int*)malloc(sizeof(int) * pow2(proposition_set.size()));   //���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
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
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 1)//����ȡ��ʽ��ֵΪ��
		{
			if (n_m == 0)//��һ����ʽ
				cout << "m<" << i << ">";
			else
				cout << " \\/ m<" << i << "> ";
			n_m++;
		}
	}
	if (n_m == 0)//û�з�ʽ
	{
		cout << "0";
	}
	cout << endl;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)
	{
		if (*(m + i) == 0)//����ȡ��ʽ��ֵΪ��
		{
			if (n_M == 0)//��һ����ʽ
				cout << "M<" << i << ">";
			else
				cout << " /\\ M<" << i << "> ";
			n_M++;
		}
	}
	if (n_M == 0)//û�з�ʽ
		cout << "0";
	cout << endl;
	return 0;
}
//�жϴ�������
int Judgecorrect(string formula)
{
	stack<char> Judge_Stack;		//����һ��ջ���ݴ����
	size_t i = 0, length = formula.length();	//ѭ������i�����ʽ�ĳ���length
	//��������Ƿ�ƥ��
	while (i < length)
	{
		if (formula[i] == '(')//�����������
			Judge_Stack.push(formula[i]);
		else if (formula[i] == ')' && !Judge_Stack.empty())//����������Ų���ջ�ڴ���������
			Judge_Stack.pop();
		else if (formula[i] == ')')//���ջ�ڲ����������ŵ��Ǵ���������
			return 1;
		i++;
	}
	if (!Judge_Stack.empty())
		return 1;
	//return 1˵�����ż�ⲻƥ��
	i = 0;
	//����ڲ��������Ƿ����������
	if (formula[length - 1] == '!' || formula[length - 1] == '|' ||
		formula[length - 1] == '&' || formula[length - 1] == '~' ||
		formula[length - 1] == '^')
		return 2;
	//return 2˵���ڲ������󲻴����������
	//��鿪ͷ�Ƿ���ڷǷ�������
	if (formula[0] == '|' || formula[0] == '&' || formula[0] == '~' || formula[0] == '^')
		return 3;
	//return 3��ʾ��ͷ�ķ��ŷǷ�
	//������⹫ʽ���Ƿ���ڷǷ�����
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
	//return 4˵���ڹ�ʽ�д��ڷǷ��ַ�
	//���Ϸ��ַ��Ƿ�������������
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
	//return 5˵�����ںϷ��ַ��������������
	return 0;
}
//����-1����ʾ�����������δ�����������ɼ���������˵������������ѱ������������ظ����������⣬�����Է���ָ�����������±�
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
//�ú������������빫ʽ�е��������(�����������)
Map_ic getProposition(string formula) 
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//���������������
			int r = findProposition(proposition, c);
			//cout << r << endl;
			if (r == -1)
			{
				//˵�������������δ��������
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
//�ú��������������Ķ�����(0��1)ȡֵ
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
//�ú�������ָ�����ֵĶ��η���ֵ
int pow2(int n)    
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}
//�ú������ظ������������(ֵȡ0��1���ɺ�����)��ϵ�������
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
			//��ʱ�������������
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
//�ú������������������(ȡֵ0��1)�ĸ���������(0��1)
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