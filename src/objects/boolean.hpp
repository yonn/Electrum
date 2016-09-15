#ifndef ELECTRUM_BOOLEAN_HPP
#define ELECTRUM_BOOLEAN_HPP

#include "base_object.hpp"

namespace ell {

	class Boolean: public Object {
	public:

		virtual Object* init(bool v)
		{
			this->type = Boolean::TYPE;
			this->value = v;
			return this;
		}

		virtual std::string repr()
		{
			if (this->value) {
				return "true";
			} else {
				return "false";
			}
		}

		virtual bool boolean()
		{
			return (this->value);
		}

		bool value;
		
		const static std::string TYPE; 
		
	};

}

#endif /*ELECTRUM_BOOLEAN_HPP*/
