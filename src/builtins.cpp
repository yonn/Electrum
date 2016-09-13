#include "builtins.hpp"

namespace ell {

	std::map<std::string, BuiltinFunction> builtin_functions = { { "type", &type },
	                                                             { "+", &add },
	                                                             { "*", &multiply } };

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
					res->value += ((Float*)e->car)->value;
				} else {
					res->value += ((Integer*)e->car)->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(0);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value += ((Float*)e->car)->value;
				} else {
					res->value += ((Integer*)e->car)->value;
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
					res->value *= ((Float*)e->car)->value;
				} else {
					res->value *= ((Integer*)e->car)->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(1);
			ELL_FORLIST(e, args) {
				if (e->car->type == Float::TYPE) {
					res->value *= ((Float*)e->car)->value;
				} else {
					res->value *= ((Integer*)e->car)->value;
				}
			}
			return res;
		}
	}

}
