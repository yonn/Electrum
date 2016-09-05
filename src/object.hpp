#ifndef ELECTRUM_OBJECT_HPP
#define ELECTRUM_OBJECT_HPP

#include "error.hpp"

#include "objects/base_object.hpp"
#include "objects/pair.hpp"
#include "objects/string.hpp"
#include "objects/integer.hpp"
#include "objects/float.hpp"

#define ELL_FORLIST(v, l) for(Pair* v = l; v != nullptr; v = (Pair*)v->cdr)

namespace ell {


	bool is_empty(Pair* p);
	bool is_not_empty(Pair* p);

	void push_back(Pair* p, Object* o);
	Object* pop_back(Pair* p);

}

#endif /*ELECTRUM_OBJECT_HPP*/
