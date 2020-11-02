#pragma once
#include "VVD.h"

#define AMOUNT 8

namespace FST {

	struct RELATION { // �����:������ -> ������� ����� ��������� �� (?)
		char symbol; // ������ �������� (r, q, s, c, p, e)
		short nnode; // ����� ������� ������� (?)
		RELATION( // (?)
			char c = 0x00, // ������ �������� 
			short ns = NULL // ����� ��������� (?)
		);
	};

	struct NODE { // ������� ����� ���������
		short n_relation; // ���������� ������������ ����� (?)
		RELATION* relations;
		NODE();
		NODE(
			short n, // ���������� ������������ �����
			RELATION rel, ... // ������ �����
		);
	};


	struct FST {
		const char* string; // �������
		short position; // ������� ������� � �������
		short nstates; // ���������� ��������� ��������
		NODE* nodes; // ���� ���������: [0] - ��������� ���������, [nstate-1] - �������� ���������
		short* rstates; // ��������� ��������� �� ������ �������
		FST(
			const char* s,
			short ns,
			NODE n, ...
		);
	};

	bool execute(FST& fst, int line);
}