#include "Error.h"

namespace Error {

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYS] ������������ ��� ������"),
		ERROR_ENTRY(1, "[SYS] ��������� ����"),
		ERROR_ENTRY(2, "[SYS] �������� -in ������ ���� �����"), //
		ERROR_ENTRY(3, "[SYS] ��������� ����� �������� ���������"), //
		ERROR_ENTRY(4, "[SYS] ������ ��� �������� ����� � �������� ����� (-in)"), //
		ERROR_ENTRY(5, "[SYS] ������������ ������ � �������� ����� (-in)"), //
		ERROR_ENTRY(6, "[SYS] ������ ��� �������� ����� ��������� (-log)"), //
		ERROR_ENTRY(7, "[SYS] ������ ��� �������� ����� ������ (-out)"), //
		ERROR_ENTRY(8, "[SYS] ������ ��� �������� ����� ������ ������������� ���� (-outfile)"),
		ERROR_ENTRY(9, ""),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "[LEX] LT::Create: ��������� ������������ ������� ������� ������"),
		ERROR_ENTRY(101, "[LEX] LT::Add: ������������ ������� ������"),
		ERROR_ENTRY(102, "[LEX] LT::GetEntry: ������� ������� ������ �� ������"),
		ERROR_ENTRY(103, "[LEX] LT::Delete: ������� ������ �����������"),
		// 
		// �������, ��� ��� ��������� � ������������� ��������
		ERROR_ENTRY(104, "[LEX] LT::CreateEntry: ����� ����� main �� ����� ���� ���������������� ������"),
		ERROR_ENTRY(105, "[LEX] LT::CreateEntry: ����� ����� main ������� ���� ���������������"),
		//
		ERROR_ENTRY(106, "[LEX] IT::Create: ��������� ������������ ������� ������� ���������������"),
		ERROR_ENTRY(107, "[LEX] IT::Add: ������������ ������� ���������������"),
		ERROR_ENTRY(108, "[LEX] IT::GetEntry: ������� ������� ��������������� �� ������"),
		ERROR_ENTRY(109, "[LEX] IT::Delete: ������� �������������� �����������"),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200, "[SYN]: �������� ��������� ���������"),
		ERROR_ENTRY(201, "[SYN]: ��������� ��������"),
		ERROR_ENTRY(202, "[SYN]: ������ � ���������"),
		ERROR_ENTRY(203, "[SYN]: ������ � ���������� �������"),
		ERROR_ENTRY(204, "[SYN]: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(205, "[SYN]: ������ � �������������� ��������"),
		ERROR_ENTRY(206, "[SYN]: ������ � ������� ��������"),
		ERROR_ENTRY(207, "[SYN]: ������ � ���������� ��������"),
		ERROR_ENTRY(208, "[SYN]: ������ � �������� �����������"),
		ERROR_ENTRY(209, "[SYN]: ������ � ��������� �������� �����������"),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),

		ERROR_ENTRY(300, "[SEM] ����� ����� main ������� ���� �������� ����������������"),
		ERROR_ENTRY(301, "[SEM] ��� �������������� �� ����� ��������� � �������� ������"),
		ERROR_ENTRY(302, "[SEM] ������ ������������ ����� �������"),
		ERROR_ENTRY(303, "[SEM] ������ ������������ ����� ��������������"),
		ERROR_ENTRY(304, "[SEM] ������ ������������� ������������� �������"),
		ERROR_ENTRY(305, "[SEM] ������ ������������� ������������� ����������"),
		ERROR_ENTRY(306, "[SEM] ������ �������������� ���������� ���������� ������� �� ���������"),
		ERROR_ENTRY(307, "[SEM] ���������� ���������� �������� �������������� ��������"),
		ERROR_ENTRY(308, "[SEM] ���������� ���������� �������� �������������� ������������ ��������"),
		ERROR_ENTRY(309, "[SEM] ���������� ���������� �������� ����������� ��������"),
		ERROR_ENTRY(310, "[SEM] ���������� ���������� �������� ���������� ��������"),
		ERROR_ENTRY(311, "[SEM] ������ ���� ������������� ���������"), // � if(...) ������ ���������� �������
		ERROR_ENTRY(312, "[SEM] ������ ������������� ���������� ����� �������� � �������� ������ ���������"),
		ERROR_ENTRY(313, "[SEM] ������ ������������� ����� ������/�������� � �������� ������ ���������"),
		ERROR_ENTRY(314, "[SEM] ������ ������������� ���������"),
		ERROR_ENTRY(315, "[SEM] "),
		ERROR_ENTRY(316, "[SEM] "),
		ERROR_ENTRY(317, "[SEM]"),
		ERROR_ENTRY(318, "[SEM]"),
		ERROR_ENTRY(319, "[SEM]"),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800)
	};

	ERROR GetError(int id) {
		ERROR trouble;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			trouble = errors[0];
		else
			trouble = errors[id];
		return trouble;
	}

	ERROR GetErrorIn(int id, int line = -1, int col = -1) {
		ERROR trouble;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			trouble = errors[0];
		else {
			trouble = errors[id];
			trouble.inext.line = line;
			trouble.inext.col = col;
		}
		return trouble;
	}
}

