#ifndef ELECTRUM_STRING_HPP
#define ELECTRUM_STRING_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class String: public Object {
	public:

		virtual Object* init(std::string value)
		{
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			return '"' + this->value + '"';
		}

		std::string value;
		
	};

}

#endif /*ELECTRUM_STRING_HPP*/
