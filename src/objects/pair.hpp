#ifndef ELECTRUM_PAIR_HPP
#define ELECTRUM_PAIR_HPP

#include <string>
#include <sstream>

#include "base_object.hpp"

#define ELL_FORLIST(v, l) for(ell::Pair* v = l; v != nullptr; v = (ell::Pair*)v->cdr)
#define ELL_NEW_NIL (ell::make<ell::Pair>(nullptr, nullptr))

namespace ell {

	class Pair: public Object {
	public:

		virtual Object* init(Object* car, Object* cdr)
		{
			this->type = Pair::TYPE;
			this->car = car;
			this->cdr = cdr;
			return this;
		}

		Object* car;
		Object* cdr;

		size_t line_number;

		static const std::string TYPE;

	};

}

#endif /*ELECTRUM_PAIR_HPP*/
