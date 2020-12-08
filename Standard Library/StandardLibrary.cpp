#include "pch.h"
#include "framework.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

extern "C"
{
	int StrLen(char* str)
	{
		return strlen(str);
	}

	int StrInt(char* str)
	{
		int result = 0;
		for (int i = strlen(str) - 1, j = pow(10, strlen(str) - 1); i > 0; i--, j /= 10)
		{
			if (int(str[i]) > 57 || int(str[i]) < 48)
			{
				return 0;
			}
			result += j * (int(str[i]) - 48);
		}
		return result;
	}

	char* IntStr(int num)
	{
		char result[255] = "";
		int counter = 0;
		int buffer = num;
		while (buffer != 0)
		{
			buffer /= 10;
			counter++;
		}
		for (int i = 0; counter != 0; i++)
		{
			result[i] = char(num / pow(10, --counter) + 48);
			num /= pow(10, counter + 1);
		}
		return result;
	}

	char* PintStr(unsigned int num)
	{
		char result[255] = "";
		int counter = 0;
		int buffer = num;
		while (buffer != 0)
		{
			buffer /= 10;
			counter++;
		}
		for (int i = 0; counter != 0; i++)
		{
			result[i] = char(num / pow(10, --counter) + 48);
		}
		return result;
	}

	int SignInt(char ch)
	{
		return int(ch);
	}

	void print_int(int value)
	{
		std::cout << value << "\n";
	}

	void print_pint(unsigned int value)
	{
		std::cout << value << "\n";
	}

	void print_bool(bool value)
	{
		std::cout << value << "\n";
	}

	void print_str(char* value)
	{
		std::cout << value << "\n";
	}
	void print_sign(char value)
	{
		std::cout << value << "\n";
	}

}
