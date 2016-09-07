#ifndef ELECTRUM_STRING_HPP
#define ELECTRUM_STRING_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class String: public Object {
	public:

		virtual Object* init(std::string value)
		{
			this->type = String::TYPE;
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			return '"' + this->value + '"';
		}

		std::string value;
		
		static const std::string TYPE;

	};

}

#endif /*ELECTRUM_STRING_HPP*/
