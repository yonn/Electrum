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

		virtual std::string str()
		{
			return this->value;
		}

		virtual bool boolean()
		{
			if (this->value == "") {
				return false;
			} else {
				return true;
			}
		}

		virtual bool equals(Object* o)
		{
			if (this->type != o->type) {
				return false;
			}
			return (this->value == o->str());
		}

		std::string value;
		
		static const std::string TYPE;

	};

}

#endif /*ELECTRUM_STRING_HPP*/
