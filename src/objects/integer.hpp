#ifndef ELECTRUM_INTEGER_HPP
#define ELECTRUM_INTEGER_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class Integer: public Object {
	public:

		virtual Object* init(long value)
		{
			this->type = Integer::TYPE;
			this->value = value;
			return this;
		}

		virtual std::string repr()
		{
			return std::to_string(value);
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
			return (((Integer*)o)->value == this->value);
		}

		virtual bool is_a_number()
		{
			return true;
		}

		virtual long double number()
		{
			return (long double)this->value;
		}

		long value;

		static const std::string TYPE;
		
	};

}

#endif /*ELECTRUM_INTEGER_HPP*/
