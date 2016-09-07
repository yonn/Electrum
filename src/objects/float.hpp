#ifndef ELECTRUM_FLOAT_HPP
#define ELECTRUM_FLOAT_HPP

#include "base_object.hpp"

#include <string>
#include <sstream>

namespace ell {

	class Float: public Object {
	public:

		virtual Object* init(long double value)
		{
			this->type = TYPE;
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			std::ostringstream s;
			s << this->value;
			return s.str();
		}
		
		long double value;

		static const std::string TYPE;
		
	};

}

#endif /*ELECTRUM_FLOAT_HPP*/
