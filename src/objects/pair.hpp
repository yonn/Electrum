#ifndef ELECTRUM_PAIR_HPP
#define ELECTRUM_PAIR_HPP

#include <string>
#include <sstream>

#include "base_object.hpp"

#define ELL_FORLIST(v, l) for(ell::Pair* v = l; v != nullptr; v = (ell::Pair*)v->cdr)
#define ELL_NEW_NIL (ell::make<ell::Pair>(nullptr, nullptr, true))

namespace ell {

	class Pair: public Object {
	public:

		virtual Object* init(Object* car, Object* cdr, bool head = false)
		{
			this->type = Pair::TYPE;
			this->car = car;
			this->cdr = cdr;
			this->head = head;
			return this;
		}

		virtual std::string repr()
		{
			std::ostringstream s;

			if (this->car or this->cdr) {
				if (this->head) {
					s << "(";
				}
			
				if (this->car) {
					s << this->car->repr() << " ";
				}
				
				if (this->cdr) {
					s << this->cdr->repr() << " ";
				} else {
					s << "\b)";
				}
			} else {
				s << "nil";
			}
			
			return s.str();
		}

		void clean_head()
		{
			this->head = true;
			ELL_FORLIST(p, (Pair*)this->cdr) {
				p->head = false;
			}
		}
		
		Object* car;
		Object* cdr;
		bool head;

		static const std::string TYPE;

	};

}

#endif /*ELECTRUM_PAIR_HPP*/
