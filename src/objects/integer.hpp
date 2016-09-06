#ifndef ELECTRUM_INTEGER_HPP
#define ELECTRUM_INTEGER_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class Integer: public Object {
	public:

		virtual Object* init(long value)
		{
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			return std::to_string(value);
		}

		long value;
	};

}

#endif /*ELECTRUM_INTEGER_HPP*/