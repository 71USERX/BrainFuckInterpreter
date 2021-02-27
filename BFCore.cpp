#include <iostream>
#include <algorithm>
#include <stack>

#include "BFCore.h"

using namespace std;

static int getLBracketPos(unordered_map<int, int> map, int RBracket)
{
	for (auto item : map)
	{
		if (item.second == RBracket)
		{
			return item.first;
		}
	}
	return -1;
}

OperatorList preProcess(string str)
{
	OperatorList list;
	stack<char> braketStck;
	stack<int> pos;

	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	list.code = str;

	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (c == '[')
		{
			braketStck.push(c);
			pos.push(i);
		}
		else if (c == ']')
		{
			if (!braketStck.empty())
			{
				list.brackets[pos.top()] = i;
				braketStck.pop();
				pos.pop();
			}
			else
			{
				cerr << "Error:Has no matched brackets at " << i << '\n';
			}
		}
	}
	list.array.resize(8, 0);
	list.iterator = list.array.begin();
	list.ptrPos = 0;
	return list;
}

bool parser(OperatorList& list)
{
	switch (list.code[list.ptrPos])
	{
	case '>':
		if (list.iterator++ == list.array.end())
		{
			list.array.resize(list.array.size() + 8);
		}
		break;
	case '<':
		--list.iterator;
		break;
	case '+':
		++ * list.iterator;
		break;
	case '-':
		-- * list.iterator;
		break;
	case ',':
		*list.iterator = cin.get() % 255;
		break;
	case '.':
		cout << *list.iterator;
		break;
	case '[':
		if (!*list.iterator)
		{
			list.ptrPos = list.brackets.at(list.ptrPos);
		}
		break;
	case ']':
		if (*list.iterator)
		{
			list.ptrPos = getLBracketPos(list.brackets, list.ptrPos);
		}
		break;
	default:
		cerr << "Warnning:Undefined symbol at " << list.ptrPos << '\n';
		return false;
		break;
	}
	return true;
}

void run(string str)
{
	OperatorList list = preProcess(str);
	while (list.ptrPos < list.code.size())
	{
		parser(list);
		list.ptrPos++;
	}
}
