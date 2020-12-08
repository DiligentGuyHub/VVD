#include "Parameters.h"
#include "Error.h"

//strlen(wchar_t* str) - ����� ������ str
//strstr(wchar_t* str1, wchar_t* str2) - ��������� �� ������ ��������� ������� ������ (str2) � �������� (str1) ��� nullptr
//strcpy_s(wchar_t* destination, wchar_t* source) - �������� source � destination
//strcat_s(wchar_t* destination, const wchar_t* source) - ������������ source ������ destination

namespace Parm
{
	PARM GetParm(int argc, char* argv[])
	{ // ������ �������� ������� ���������� � ��������� ���� PARM

		PARM parm;
		strcpy_s(parm.log, "0");
		bool in_ = 0, log_ = 0, out_ = 0;

		for (int i = 1; i < argc; i++) 
		{

			if (strlen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(3);

			if (strstr(argv[i], PARM_IN)) 
			{ // �������� �� ������� ��������� -in (strict)
				strcpy_s(parm.in, argv[i] + strlen(PARM_IN));
				in_ = 1; // ��������� ��������
			}

			if (strstr(argv[i], PARM_OUT))
			{ // �������� �� ������� ��������� -out
				strcpy_s(parm.out, argv[i] + strlen(PARM_OUT));
				out_ = 1; // ��������� ��������
			}

			if (strstr(argv[i], PARM_LOG)) 
			{ // �������� �� ������� ��������� -log
				strcpy_s(parm.log, argv[i] + strlen(PARM_LOG));
				log_ = 1; // ��������� ��������
			}
		}
		if (!in_)
		{
			throw ERROR_THROW(2); // ������, -in �������� ������������ ����������
		}
		if (!out_)
		{
			strcpy_s(parm.out, parm.in); // ����������, out = in
			strcat_s(parm.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log_) 
		{
			strcpy_s(parm.log, parm.in); // ����������, log = in
			strcat_s(parm.log, PARM_LOG_DEFAULT_EXT);
		}
		return parm;
	}
}