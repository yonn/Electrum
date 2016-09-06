#ifndef ELECTRUM_KEYWORD_HPP
#define ELECTRUM_KEYWORD_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class Keyword: public Object {
	public:

		virtual Object* init(std::string keyword)
		{
			this->keyword = keyword;
			return this;
		}

		virtual std::string repr()
		{
			return this->keyword;
		}
		
		std::string keyword;
		
	};

}

#endif /*ELECTRUM_KEYWORD_HPP*/
