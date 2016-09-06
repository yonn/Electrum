#ifndef ELECTRUM_SYMBOL_HPP
#define ELECTRUM_SYMBOL_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class Symbol: public Object {
	public:

		virtual Object* init(std::string symbol)
		{
			this->symbol = symbol;
			return this;
		}

		virtual std::string repr()
		{
			return this->symbol;
		}

		std::string symbol;
		
	};

}

#endif /*ELECTRUM_SYMBOL_HPP*/
