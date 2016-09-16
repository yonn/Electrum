#include "builtins.hpp"

namespace ell {

	std::map<std::string, BuiltinFunction> builtin_functions = { { "type", &type },
	                                                             { "if", &if_ },
	                                                             { "str", &str },
								     { "int", &int_ },
								     { "float", &float_ },
								     { "?", &boolean },
								     { "list", &list },
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
	                                                             { "atan", &atan },
								     { "printf", &printf },
								     { "printfln", &printfln },
								     { "format", &format } };

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
	 *  Flow Control
	 *----------------------------------------------------------*/

	Object* if_(Pair* args)
	{
		if (get_arg<Object>(args)->boolean()) {
			return get_arg<Object>(args);
		} else {
			nd_pop_front(args);
			if (is_empty(args)) {
				return args;
			} else {
				return get_arg<Object>(args);
			}
		}
	}

	/*------------------------------------------------------------
	 *  Type Conversions
	 *----------------------------------------------------------*/

	Object* str(Pair* args)
	{
		auto o = get_arg<Object>(args);
		if (o->type == String::TYPE) {
			return o;
		}
		return make<String>(o->str());
	}


	Object* int_(Pair* args)
	{
		auto o = get_arg<Object>(args);
		if (o->type == Float::TYPE) {
			return make<Integer>((long)((Float*)o)->value);
		} else if (o->type == String::TYPE) {
			try {
				return make<Integer>(std::stol(((String*)o)->value));
			} catch (const std::invalid_argument& e) {
				error("Could not convert argument to %s", Integer::TYPE.c_str());
				return nullptr;
			}
		} else if (o->type == Integer::TYPE) {
			return o;
		} else {
			error("Unable to convert `%s' to %s", o->type.c_str(), Integer::TYPE.c_str());
			return nullptr;
		}
	}
	
	Object* float_(Pair* args)
	{
		auto o = get_arg<Object>(args);
		if (o->type == Integer::TYPE) {
			try {
				return make<Float>(std::stold(((String*)o)->value));
			} catch (const std::invalid_argument& e) {
				error("Could not convert argument to %s", Float::TYPE.c_str());
				return nullptr;
			}
		} else if (o->type == String::TYPE) {
			return make<Float>(std::stold(((String*)o)->value));
		} else if (o->type == Float::TYPE) {
			return o;
		} else {
			error("Unable to convert `%s' to %s", o->type.c_str(), Float::TYPE.c_str());
			return nullptr;
		}
	}

	Object* boolean(Pair* args)
	{
		auto o = get_arg<Object>(args);
		if (o->type == Boolean::TYPE) {
			return o;
		}
		return make<Boolean>(o->boolean());
	}

	Object* list(Pair* args)
	{
		if (is_not_empty(args)) {
			ELL_FORLIST(e, args) {
				e->car = eval(e->car);
			}
		}
		return args;
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

	/*------------------------------------------------------------
	 *  IO
	 *----------------------------------------------------------*/

	static std::string format_(Pair* args)
	{
		std::ostringstream s;
		std::string format = get_arg<String>(args)->value;
		bool flag = false;
		
		for (const auto c: format) {
			if (flag) {
				flag = false;
				switch (c) {
				case '~':
					s << '~';
					break;
				case '%':
					s << '\n';
					break;
				case 's':
					s << nd_pop_front(args)->str();
					break;
				case 'r':
					s << nd_pop_front(args)->repr();
					break;
				default:
					error("Could not identify format flag `%c'", c);
				}
			} else {
				if (c == '~') {
					flag = true;
				} else {
					s << c;
				}
			}
		}
		return s.str();
	}

	Object* printf(Pair* args)
	{
		std::cout << format_(args);
		return ELL_NEW_NIL;
	}
	
	Object* printfln(Pair* args)
	{
		std::cout << format_(args) << std::endl;
		return ELL_NEW_NIL;
	}

	Object* format(Pair* args)
	{
		return make<String>(format_(args));
	}
	
}
