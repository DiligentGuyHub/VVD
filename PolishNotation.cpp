#include "PolishNotation.h"

// */ 3, +- 2, ( 1;
// & 3, \ 2, ( 1
// < <= > >= 3, == != 2, ( 1

namespace PolishNotation
{
	void Checkout(LT::LexTable& lex, IT::IdTable& idt)
	{
		for (int i = 0; i < lex.size; i++)
		{
			if (lex.table[i].lexema == ':' || lex.table[i].lexema == 'p' || lex.table[i].lexema == 'r')
			{
				if (!PolishNotation(i + 1, lex, idt))
				{
					throw ERROR_THROW_IN(10, lex.table[i].sn, -1)
				}
			}
			else if (lex.table[i].lexema == '?' || lex.table[i].lexema == 'z')
			{
				PolishNotationBoolean(i + 2, lex, idt);
			}
		}
		return;
	}

	bool PolishNotation(int	lextable_position, LT::LexTable& lex, IT::IdTable& idt)
	{
		if (lex.table[lextable_position].sn == 36)
		{
			int a = 10;
		}

		Lexema temp;

		LT::Entry* result = new LT::Entry[50]{};
		LT::Entry empty = {};
		CurrentPriority priority;
		std::stack <Lexema> Stack;

		int j = 0;
		int parcounter = 0;
		int functionpar = 0;
		for (int i = lextable_position, j = 0; lex.table[i - 1].lexema != LEX_SEMICOLON; i++)
		{
			if (lex.table[lextable_position + 1].lexema == LEX_SEMICOLON)
			{
				return true;
			}
			switch (lex.table[i].lexema)
			{
			case 'v':
				temp.entry = lex.table[i];
				// */ 3, +- 2, ( 1;
				// & 3, \ 2, ( 1
				switch (lex.table[i].operation)
				{
					case '+':
						temp.priority = MIDDLE;
						break;
					case '-':
						temp.priority = MIDDLE;
						break;
					case '*':
						temp.priority = HIGH;
						break;
					case '/':
						temp.priority = HIGH;
						break;
					case '&':
						temp.priority = HIGH;
						break;
					case '\\':
						temp.priority = MIDDLE;
						break;
					case '>':
						temp.priority = HIGH;
						break;
					case '<':
						temp.priority = HIGH;
						break;
					case '1':
						temp.priority = HIGH;
						break;
					case '2':
						temp.priority = HIGH;
						break;
					case '=':
						temp.priority = MIDDLE;
						break;
					case '!':
						temp.priority = MIDDLE;
						break;
				}

				if (Stack.empty() || Stack.top().entry.lexema == '(')
				{
					Stack.push(temp);
				}
				else
				{
					while (!Stack.empty() && Stack.top().priority >= temp.priority)
					{
						result[j++] = Stack.top().entry;
						Stack.pop();
					}
					Stack.push(temp);
				}
				break;
			case '(':
				temp.entry = lex.table[i];
				temp.priority = LOW;
				Stack.push(temp);
				break;
			case ')':
				while (!Stack.empty() && Stack.top().entry.lexema != '(')
				{
					result[j++] = Stack.top().entry;
					Stack.pop();
				}
				if (!Stack.empty())
				{
					Stack.pop();
				}
				
				break;
			case 'i':
				result[j++] = lex.table[i];
				break;
			case 'l':
				result[j++] = lex.table[i];
				break;
			case ';':
				while (!Stack.empty() && Stack.top().entry.operation)
				{
					result[j++] = Stack.top().entry;
					Stack.pop();
				}
				break;
			}

			temp.entry.lexema = NULL;
			temp.priority = NONE;
		}

		for (int i = lextable_position, j = 0; lex.table[i].lexema != ';'; i++)
		{
			if (result[j].lexema != NULL)
				lex.table[i] = result[j++];
			else
			{
				lex.table[i] = { '\0', '\0', LT::UNDEF, lex.table[i - 1].sn, 0xfffffff };
			}

		}
		if (Stack.empty())
			return true;
		else
			return false;
	}

	bool PolishNotationBoolean(int	lextable_position, LT::LexTable& lex, IT::IdTable& idt)
	{
		if (lex.table[lextable_position].sn == 36)
		{
			int a = 10;
		}

		Lexema temp;

		LT::Entry* result = new LT::Entry[50]{};
		LT::Entry empty = {};
		CurrentPriority priority;
		std::stack <Lexema> Stack;

		int j = 0;
		int parcounter = 0;
		int functionpar = 0;
		for (int i = lextable_position, j = 0; lex.table[i - 1].lexema != ';' || lex.table[i + 1].lexema == '{'; i++)
		{

			switch (lex.table[i].lexema)
			{
			case 'v':
				temp.entry = lex.table[i];
				// < <= > >= 3, == != 2, ( 1
				switch (lex.table[i].operation)
				{
					case '>':
						temp.priority = HIGH;
						break;
					case '<':
						temp.priority = HIGH;
						break;
					case '1':
						temp.priority = HIGH;
						break;
					case '2':
						temp.priority = HIGH;
						break;
					case '=':
						temp.priority = MIDDLE;
						break;
					case '!':
						temp.priority = MIDDLE;
						break;
				}

				if (Stack.empty() || Stack.top().entry.lexema == '(')
				{
					Stack.push(temp);
				}
				else if (!Stack.empty() && Stack.top().priority >= temp.priority)
				{
					result[j++] = Stack.top().entry;
					Stack.pop();
				}
				break;
			case '(':
				temp.entry = lex.table[i];
				temp.priority = LOW;
				Stack.push(temp);
				break;
			case ')':
				while (!Stack.empty() && Stack.top().entry.lexema != '(')
				{
					result[j++] = Stack.top().entry;
					Stack.pop();
				}
				if (!Stack.empty())
				{
					Stack.pop();
				}
				result[j++] = { ')', '\0', LT::UNDEF, lex.table[i].sn, 0xfffffff };
				result[j++] = { '{', '\0', LT::UNDEF, lex.table[i].sn, 0xfffffff };
				break;
			case 'i':
				result[j++] = lex.table[i];
				break;
			case 'l':
				result[j++] = lex.table[i];
				break;
			case ';':
				while (!Stack.empty() && Stack.top().entry.operation)
				{
					result[j++] = Stack.top().entry;
					Stack.pop();
				}
				break;
			}

			temp.entry.lexema = NULL;
			temp.priority = NONE;
		}


		for (int i = lextable_position, j = 0; lex.table[i].lexema != ';'; i++)
		{
			if (result[j].lexema != NULL)
				lex.table[i] = result[j++];
			else
			{
				lex.table[i] = { '\0', '\0', LT::UNDEF, lex.table[i - 1].sn, 0xfffffff };
			}

		}
		if (Stack.empty())
			return true;
		else
			return false;
	}

	//bool PolishNotation(int	lextable_position, LT::LexTable& lex, IT::IdTable& idt)
	//{
	//	if (lex.table[lextable_position].sn == 36)
	//	{
	//		int a = 10;
	//	}
	//	
	//	Lexema temp;

	//	LT::Entry* result = new LT::Entry();
	//	LT::Entry empty = {};
	//	CurrentPriority priority;
	//	std::stack <Lexema> Stack;

	//	int j = 0;
	//	int parcounter = 0;
	//	int functionpar = 0;
	//	for (int i = lextable_position + 1, j = 0; lex.table[i - 1].lexema != ';'; i++)
	//	{

	//		switch (lex.table[i].lexema)
	//		{
	//		case 'v':
	//			temp.entry = lex.table[i];

	//			if (temp.entry.operation == '*' || temp.entry.operation == '/')
	//			{
	//				temp.priority = HIGH;
	//				temp.entry.operationtype = LT::A;
	//			}
	//			else if (temp.entry.operation == '&')
	//			{
	//				temp.priority = HIGH;
	//				temp.entry.operationtype = LT::B;
	//			}
	//			else if (temp.entry.operation == '<' || temp.entry.operation == '>' || \
	//				temp.entry.operation == '1' || temp.entry.operation == '2' \
	//				)
	//			{
	//				temp.priority = HIGH;
	//				temp.entry.operationtype = LT::L;
	//			}
	//			else
	//			{
	//				temp.priority = MIDDLE;
	//				if (temp.entry.operation == '+' || temp.entry.operation == '-')
	//				{
	//					temp.entry.operationtype = LT::A;
	//				}
	//				else if (temp.entry.operation == '\\')
	//				{
	//					temp.entry.operationtype = LT::B;
	//				}
	//				else if (temp.entry.operation == '!' || temp.entry.operation == '=')
	//				{
	//					temp.entry.operationtype = LT::L;
	//				}
	//			}

	//			if (Stack.empty() || Stack.top().priority < temp.priority)
	//			{
	//				Stack.push(temp);
	//			}
	//			else
	//			{
	//				while (Stack.top().priority >= temp.priority)
	//				{
	//					result[j++] = Stack.top().entry;
	//					Stack.pop();
	//				}
	//			}
	//			break;
	//		case '(':
	//			temp.entry.lexema = lex.table[i].lexema;
	//			temp.priority = LOW;
	//			Stack.push(temp);
	//			break;
	//		case ')':
	//			if (functionpar > 0)
	//			{
	//				functionpar -= 1;
	//				result[j++] = { '@', ' ', LT::UNDEF, result[j].sn, parcounter };
	//				parcounter = 0;
	//			}
	//			else
	//			{
	//				while (Stack.top().entry.lexema != '(')
	//				{
	//					result[j++] = Stack.top().entry;
	//					Stack.pop();
	//				}

	//			}
	//			Stack.pop();
	//			break;
	//		case 'i':
	//			if (idt.table[lex.table[i].idxTI].idtype == IT::F)
	//			{
	//				functionpar += 1;
	//			}
	//			else
	//			{
	//				if (functionpar > 0) parcounter++;
	//				result[j++] = lex.table[i];
	//			}
	//			break;
	//		case 'l':
	//			if (functionpar > 0)
	//			{
	//				parcounter++;
	//			}
	//			result[j++] = lex.table[i];
	//			break;
	//		case ';':
	//			while (!Stack.empty() && Stack.top().entry.operation)
	//			{
	//				result[j++] = Stack.top().entry;
	//				Stack.pop();
	//			}
	//			break;
	//		}

	//		temp.entry.lexema = NULL;
	//		temp.priority = NONE;
	//	}


	//	//std::cout << result << std::endl;
	//	for (int i = lextable_position, j = 0; lex.table[i].lexema != ';'; i++)
	//	{
	//		if (result[j].lexema != NULL)
	//			lex.table[i] = result[j++];
	//		else
	//		{
	//			lex.table[i] = empty;
	//			lex.table[i].idxTI = 0xfffffff;
	//		}

	//	}
	//	if (Stack.empty())
	//		return true;
	//	else
	//		return false;
	//}
}
