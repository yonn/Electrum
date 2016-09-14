#include "eval.hpp"

namespace ell {

	static Object* eval_list(Pair* list);
	static Object* function_call(Pair* args);

	Object* eval(Object* o)
	{
		if (o->type == Pair::TYPE) {
			return eval_list((Pair*)o);
		} else if (o->type == Quote::TYPE) {
			return ((Quote*)o)->o;
		} else {
			return o;
		}
	}

	static Object* eval_list(Pair* list)
	{
		error_line_number = list->line_number;
		if (is_empty(list)) {
			return list;
		} else {
			return function_call(list);
			return nullptr;
		}
	}

	static Object* function_call(Pair* args)
	{
		auto f = get_arg<Object>(args);
		if (f->type == Symbol::TYPE) {
			std::string name = type_check<Symbol>(f)->symbol;
			if (builtin_functions.count(name) == 1) {
				auto f = builtin_functions[name];
				return f(args);
			} else {
				error("Could not find a function `%s'", name.c_str());
				return nullptr;
			}
		}
		error("Can not call object of type `%s' as a function", f->type.c_str());
		return nullptr;
	}

}
