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
			this->type = Float::TYPE;
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			std::ostringstream s;
			s << this->value;
			return s.str();
		}

		virtual bool boolean()
		{
			if (this->value) {
				return true;
			} else {
				return false;
			}
		}

		virtual bool equals(Object* o)
		{
			if (this->type != o->type) {
				return false;
			}
			return (((Float*)o)->value == this->value);
		}

		virtual bool is_a_number()
		{
			return true;
		}

		virtual long double number()
		{
			return this->value;
		}
		
		long double value;

		static const std::string TYPE;
		
	};

}

#endif /*ELECTRUM_FLOAT_HPP*/
