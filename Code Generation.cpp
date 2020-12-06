#include "Code Generation.h"


namespace Generation
{
	void CodeGeneration(LT::LexTable& lex, IT::IdTable& idt, char* outfile)
	{
		std::ofstream* file;
		if (!file->is_open())
		{
			throw ERROR_THROW(8);
		}
		*file << MASM_HEAD;
		*file << MASM_LIBS;
		*file << MASM_PROTO;
		*file << MASM_STACK;
	}

	void LiteralGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream *file)
	{
		*file << MASM_CONST;
	}
}