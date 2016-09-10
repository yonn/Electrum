#ifndef ELECTRUM_QUOTE_HPP
#define ELECTRUM_QUOTE_HPP

#include "base_object.hpp"

#include <string>

namespace ell {

	class Quote: public Object {
	public:

		virtual Object* init(Object* o)
		{
			this->type = Quote::TYPE;
			this->o = o;
			return this;
		}

		virtual std::string repr()
		{
			return ("'" + o->repr());
		}
		
		Object* o;
		const static std::string TYPE;
		
	};

}

#endif /*ELECTRUM_QUOTE_HPP*/
