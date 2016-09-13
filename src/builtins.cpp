#include "builtins.hpp"

namespace ell {

	std::map<std::string, BuiltinFunction> builtin_functions = { { "type", &type },
	                                                             { "+", &add },
	                                                             { "*", &multiply },
	                                                             { "-", &subtract },
	                                                             { "/", &divide },
	                                                             { "^", &power },
	                                                             { "sqrt", &sqrt } };

	/*------------------------------------------------------------
	 *  Builtin Functions
	 *----------------------------------------------------------*/


	/*------------------------------------------------------------
	 *  General
	 *----------------------------------------------------------*/


	Object* type(Pair* args)
	{
		auto o = get_arg<Object>(args);
		return make<String>(o->type);
	}

	/*------------------------------------------------------------
	 *  Arithmetic
	 *----------------------------------------------------------*/

	static bool check_numeric(std::string name, Pair* args)
	{
		bool f;
		ELL_FORLIST(e, args) {
			if (e->car->type == Float::TYPE) {
				f = true;
			} else if (e->car->type != Integer::TYPE) {
				error(e->car->line_number, "`%s' recieved a `%s', expected a numeric type.",
				      name.c_str(),
				      e->car->type.c_str());
			}
		}
		return f;
	}

	Object* add(Pair* args)
	{
		if (is_empty(args)) {
			return make<Integer>(0);
		}
		if (check_numeric("+", args)) {
			auto res = make<Float>(0.0);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value += ((Float*)eval(e->car))->value;
				} else {
					res->value += ((Integer*)eval(e->car))->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(0);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value += ((Float*)eval(e->car))->value;
				} else {
					res->value += ((Integer*)eval(e->car))->value;
				}
			}
			return res;
		}
	}

	Object* multiply(Pair* args)
	{
		if (is_empty(args)) {
			return make<Integer>(1);
		}
		if (check_numeric("*", args)) {
			auto res = make<Float>(1.0);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value *= ((Float*)eval(e->car))->value;
				} else {
					res->value *= ((Integer*)eval(e->car))->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(1);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value *= ((Float*)eval(e->car))->value;
				} else {
					res->value *= ((Integer*)eval(e->car))->value;
				}
			}
			return res;
		}
	}

	Object* subtract(Pair* args)
	{
		if (is_empty(args)) {
			return nd_pop_front(args);
		}
		if (check_numeric("-", args)) {
			auto res = make<Float>(0.0);

			Object* o = eval(nd_pop_front(args));
			
			if (o->type == Float::TYPE) {
				res->value += ((Float*)o)->value;
			} else {
				res->value += ((Integer*)o)->value;
			}

			if (is_empty(args)) {
				res->value = -res->value;
				return res;
			}
			
			o = eval(nd_pop_front(args));
			if (o->type == Float::TYPE) {
				res->value -= ((Float*)o)->value;
			} else {
				res->value -= ((Integer*)o)->value;
			}
			return res;
		} else {
			auto res = make<Integer>(0);

			Object* o = eval(nd_pop_front(args));

			if (o->type == Float::TYPE) {
				res->value += ((Float*)o)->value;
			} else {
				res->value += ((Integer*)o)->value;
			}

			if (is_empty(args)) {
				res->value = -res->value;
				return res;
			}
			
			o = eval(nd_pop_front(args));
			if (o->type == Float::TYPE) {
				res->value -= ((Float*)o)->value;
			} else {
				res->value -= ((Integer*)o)->value;
			}
			return res;
		}
	}

	Object* divide(Pair* args)
	{
		if (is_empty(args)) {
			return nd_pop_front(args);
		}

		check_numeric("/", args);

		auto res = make<Float>(1.0);

		Object* o = eval(nd_pop_front(args));
		
		if (o->type == Float::TYPE) {
			res->value *= ((Float*)o)->value;
		} else {
			res->value *= ((Integer*)o)->value;
		}
		
		if (is_empty(args)) {
			res->value = 1 / res->value;
			return res;
		}
		
		o = eval(nd_pop_front(args));
		if (o->type == Float::TYPE) {
			if (((Float*)o)->value == 0.0) {
				error(o->line_number, "Divide by zero error!");
			}
			res->value /= ((Float*)o)->value;
		} else {
			if (((Integer*)o)->value == 0) {
				error(o->line_number, "Divide by zero error!");
			}
			res->value /= ((Integer*)o)->value;
		}
		return res;
	}

	Object* power(Pair* args)
	{
		if (is_empty(args)) {
			return nd_pop_front(args);
		}

		check_numeric("^", args);

		Object* bo = eval(nd_pop_front(args));
		Object* eo = eval(nd_pop_front(args));

		long double b, e;

		if (bo->type == Float::TYPE) {
			b = ((Float*)bo)->value;
		} else {
			b = ((Integer*)bo)->value;
		}

		if (eo->type == Float::TYPE) {
			e = ((Float*)eo)->value;
		} else {
			e = ((Integer*)eo)->value;
		}
		
		return make<Float>(std::pow(b, e));
	}

	Object* sqrt(Pair* args)
	{
		if (is_empty(args)) {
			return nd_pop_front(args);
		}

		check_numeric("^", args);

		Object* o = eval(nd_pop_front(args));

		long double v;

		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}
		
		return make<Float>(std::sqrt(v));
	}
	
}
