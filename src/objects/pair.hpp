#ifndef ELECTRUM_PAIR_HPP
#define ELECTRUM_PAIR_HPP

#include <string>
#include <sstream>

#include "base_object.hpp"

#define ELL_NEW_NIL (make<Pair>(nullptr, nullptr, true))

namespace ell {

	class Pair: public Object {
	public:

		virtual Object* init(Object* car, Object* cdr, bool head = false)
		{
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
		
		Object* car;
		Object* cdr;
		bool head;
	};

}

#endif /*ELECTRUM_PAIR_HPP*/
