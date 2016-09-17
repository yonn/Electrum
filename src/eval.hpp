#ifndef ELECTRUM_EVAL_HPP
#define ELECTRUM_EVAL_HPP

#include "object.hpp"
#include "builtins.hpp"
#include "state.hpp"
#include "error.hpp"

namespace ell {

	Object* eval(Object* o);

	template<typename O>
	static O* type_check(Object* o)
	{
		if (O::TYPE == Object::TYPE) {
			return (O*)o;
		} else if (o->type != O::TYPE) {
			error("Expected `%s', received `%s'", o->type.c_str(), O::TYPE.c_str());
			return nullptr;
		} else {
			return (O*)o;
		}
	}
	
	template<typename O>
	static O* get_arg(Pair*& list)
	{
		return type_check<O>(eval(nd_pop_front(list)));
	}
	
	template<typename O>
	static O* get_raw_arg(Pair*& list)
	{
		return type_check<O>(nd_pop_front(list));
	}

}

#endif /*ELECTRUM_EVAL_HPP*/
