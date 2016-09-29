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

		virtual std::string repr()
		{
			if (not this->car and not this->cdr) {
				return "nil";
			}
			
			std::ostringstream s;
			s << "(";
			ELL_FORLIST(e, this) {
				s << e->car->repr() << " "; 
			}
			s << "\b)";
			return s.str();
		}

		virtual bool boolean()
		{
			if (not this->car and not this->cdr) {
				return false;
			} else {
				return true;
			}
		}

		virtual bool equals(Object* o)
		{
			bool res;
			if (o->type != Pair::TYPE) {
				return false;
			}

			Pair* p = (Pair*)o;

			if (not this->car and not this->cdr) {
				return (not p->car and not p->cdr);
			}

			if (not p->car and not p->cdr) {
				return false;
			}
			
			if (this->cdr == nullptr) {
				res = (p->cdr == nullptr);
			} else {
				if (this->cdr->type == p->cdr->type) {
					res = this->cdr->equals(p->cdr);
				} else if (this->cdr->is_a_number() and p->cdr->is_a_number()) {
					res = (this->cdr->number() == p->cdr->number());
				} else {
					return false;
				}
			}
			
			if (this->car->type == p->car->type) {
				return (res and this->car->equals(p->car));
			} else if (this->car->is_a_number() and p->car->is_a_number()) {
				return (res and (this->car->number() == p->car->number()));
			} else {
				return false;
			}
		}

		Object* car;
		Object* cdr;

		size_t line_number;

		static const std::string TYPE;

	};

}

#endif /*ELECTRUM_PAIR_HPP*/
