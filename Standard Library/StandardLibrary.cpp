#include "pch.h"
#include "framework.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

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

	char* Concat(char* source, char* destination)
	{
		char result[255] = "";
		for (int i = 0; i < strlen(destination); i++)
		{
			result[i] = destination[i];
		}
		for (int i = strlen(destination), j = 0; i < strlen(destination) + strlen(source); i++)
		{
			result[i] = source[j++];
		}
		result[strlen(destination) + strlen(source)] = '\n';
		return result;
	}

	void print_int(int value)
	{
		std::cout << value;
	}

	void print_pint(unsigned int value)
	{
		std::cout << value;
	}

	void print_bool(bool value)
	{
		std::cout << value;
	}
}
