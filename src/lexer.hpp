#ifndef ELECTRUM_LEXER_HPP
#define ELECTRUM_LEXER_HPP

#include <list>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

#include "error.hpp"

namespace ell {

	class TokenIR {
	public:
		
		enum class Type {
			Keyword,
			Symbol,
			String,
			DecimalNum,
			FloatNum,
			Quote,
			Separator
		} tid;

		std::string token;

		size_t line_number;

		const std::string str() const;
	};
	
	using TokenList = std::list<TokenIR>;
	
	TokenList tokenize(const std::string& line, size_t line_num);

}

#endif /*ELECTRUM_LEXER_HPP*/
