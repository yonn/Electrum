#include "builtins.hpp"

namespace ell {

	std::map<std::string, BuiltinFunction> builtin_functions = { { "type", &type },
	                                                             { "+", &add },
	                                                             { "*", &multiply },
	                                                             { "-", &subtract },
	                                                             { "/", &divide },
	                                                             { "^", &power },
	                                                             { "sqrt", &sqrt },
	                                                             { "sin", &sin },
	                                                             { "cos", &cos },
	                                                             { "tan", &tan },
	                                                             { "asin", &asin },
	                                                             { "acos", &acos },
	                                                             { "atan", &atan } };

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

		if (is_empty(args)) {
			return false;
		}
		
		ELL_FORLIST(e, args) {
			if (eval(e->car)->type == Float::TYPE) {
				f = true;
			} else if (eval(e->car)->type != Integer::TYPE) {
				error("`%s' recieved a `%s', expected a numeric type.",
				      name.c_str(),
				      e->car->type.c_str());
			}
		}
		args->clean_head();
		return f;
	}

	Object* add(Pair* args)
	{
		if (check_numeric("+", args)) {
			auto res = make<Float>(0.0);
			Object* o;
			while (is_not_empty(args)) {
				o = get_arg<Object>(args);
				if (o->type == Float::TYPE) {
					res->value += ((Float*)o)->value;
				} else {
					res->value += ((Integer*)o)->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(0);
			Object* o;
			while (is_not_empty(args)) {
				o = get_arg<Object>(args);
				if (o->type == Float::TYPE) {
					res->value += ((Float*)o)->value;
				} else {
					res->value += ((Integer*)o)->value;
				}
			}
			return res;
		}
	}

	Object* multiply(Pair* args)
	{
		if (check_numeric("*", args)) {
			auto res = make<Float>(1.0);
			Object* o;
			while (is_not_empty(args)) {
				o = get_arg<Object>(args);
				if (o->type == Float::TYPE) {
					res->value *= ((Float*)o)->value;
				} else {
					res->value *= ((Integer*)o)->value;
				}
			}
			return res;
		} else {
			auto res = make<Integer>(1);
			Object* o;
			while (is_not_empty(args)) {
				o = get_arg<Object>(args);
				if (o->type == Float::TYPE) {
					res->value *= ((Float*)o)->value;
				} else {
					res->value *= ((Integer*)o)->value;
				}
			}
			return res;
		}
	}

	Object* subtract(Pair* args)
	{
		Object* o;
		
		if (check_numeric("-", args)) {
			auto res = make<Float>(0.0);

			o = get_arg<Object>(args);

			if (o->type == Float::TYPE) {
				res->value += ((Float*)o)->value;
			} else {
				res->value += ((Integer*)o)->value;
			}

			if (is_empty(args)) {
				res->value = -res->value;
				return res;
			}

			o = get_arg<Object>(args);

			if (o->type == Float::TYPE) {
				res->value -= ((Float*)o)->value;
			} else {
				res->value -= ((Integer*)o)->value;
			}		
			
			return res;
		} else {
			auto res = make<Integer>(0);

			o = get_arg<Object>(args);

			if (o->type == Float::TYPE) {
				res->value += ((Float*)o)->value;
			} else {
				res->value += ((Integer*)o)->value;
			}

			if (is_empty(args)) {
				res->value = -res->value;
				return res;
			}

			o = get_arg<Object>(args);

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
		
		check_numeric("/", args);
		
		auto res = make<Float>(1.0);
		
		Object* o = get_arg<Object>(args);
		
		if (o->type == Float::TYPE) {
			res->value *= ((Float*)o)->value;
		} else {
			res->value *= ((Integer*)o)->value;
		}
		
		if (is_empty(args)) {

			if (res->value == 0.0) {
				goto divide_by_zero_error;
			}
			
			res->value = 1 / res->value;
			return res;
		}
		
		o = get_arg<Object>(args);
		
		if (o->type == Float::TYPE) {

			if (((Float*)o)->value == 0.0) {
			divide_by_zero_error:
				error("Divide by zero error!");
			}
			
			res->value /= ((Float*)o)->value;
		} else {

			if (((Integer*)o)->value == 0) {
				error("Divide by zero error!");
			}
			
			res->value /= ((Integer*)o)->value;
		}		
		
		return res;
	}
	
	Object* power(Pair* args)
	{
		check_numeric("^", args);

		auto res = make<Float>(0.0);
		long double b, e;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			b = ((Float*)o)->value;
		} else {
			b = ((Integer*)o)->value;
		}

		o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			e = ((Float*)o)->value;
		} else {
			e = ((Integer*)o)->value;
		}

		return res->init(std::pow(b, e));
	}

	Object* sqrt(Pair* args)
	{
		check_numeric("^", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		if (v < 0.0) {
			error("Negative square root error");
		}

		return res->init(std::sqrt(v));
	}

	Object* sin(Pair* args)
	{
		check_numeric("sin", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		return res->init(std::sin(v));
	}

	Object* cos(Pair* args)
	{
		check_numeric("cos", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		return res->init(std::cos(v));
	}

	Object* tan(Pair* args)
	{
		check_numeric("tan", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		return res->init(std::tan(v));
	}


	Object* asin(Pair* args)
	{
		check_numeric("asin", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		if (v > 1.0 or v < -1.0) {
			error("Argument must be between -1 and 1");
		}

		return res->init(std::asin(v));
	}

	Object* acos(Pair* args)
	{
		check_numeric("acos", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		if (v > 1.0 or v < -1.0) {
			error("Argument must be between -1 and 1");
		}

		return res->init(std::acos(v));
	}

	Object* atan(Pair* args)
	{
		check_numeric("atan", args);

		auto res = make<Float>(0.0);
		long double v;

		Object* o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			v = ((Float*)o)->value;
		} else {
			v = ((Integer*)o)->value;
		}

		if (v > 1.0 or v < -1.0) {
			error("Argument must be between -1 and 1");
		}

		return res->init(std::atan(v));
	}
	
}
