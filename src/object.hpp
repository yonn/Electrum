#ifndef ELECTRUM_OBJECT_HPP
#define ELECTRUM_OBJECT_HPP

#include "error.hpp"

#include "objects/base_object.hpp"
#include "objects/pair.hpp"

namespace electrum {


	bool is_empty(Pair* p);
	bool is_not_empty(Pair* p);

	void push_back(Pair* p, Object* o);
	Object* pop_back(Pair* p);

}

#endif /*ELECTRUM_OBJECT_HPP*/
