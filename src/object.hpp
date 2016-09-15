#ifndef ELECTRUM_OBJECT_HPP
#define ELECTRUM_OBJECT_HPP

#include "error.hpp"

#include "objects/base_object.hpp"
#include "objects/pair.hpp"
#include "objects/string.hpp"
#include "objects/integer.hpp"
#include "objects/float.hpp"
#include "objects/keyword.hpp"
#include "objects/symbol.hpp"
#include "objects/quote.hpp"
#include "objects/boolean.hpp"

namespace ell {


	bool is_empty(Pair* p);
	bool is_not_empty(Pair* p);

	void push_back(Pair* p, Object* o);
	Object* pop_back(Pair* p);
	Object* nd_pop_front(Pair*& p);

}

#endif /*ELECTRUM_OBJECT_HPP*/
