#include "eval.hpp"

namespace ell {

	static Object* eval_list(Pair* list);

	Object* eval(Object* o)
	{
		if (o->type == Pair::TYPE) {
			return eval_list((Pair*)o);
		} else {
			return o;
		}
	}

	static Object* eval_list(Pair* list)
	{
		if (is_empty(list)) {
			return list;
		} else {
			Object* name = get_arg<Symbol>(list);
			//return function_call(name, list);
			return nullptr;
		}
	}


}
