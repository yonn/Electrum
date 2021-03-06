#include "builtins.hpp"

namespace ell {

	thread_local State* state;

	std::map<std::string, BuiltinFunction> builtin_functions = { { "type", &type },
	                                                             { "defvar", &defvar },
	                                                             { "let", &let },
	                                                             { "set", &set },
	                                                             { "if", &if_ },
	                                                             { "while", &while_ },
	                                                             { "str", &str },
								     { "int", &int_ },
								     { "float", &float_ },
								     { "?", &boolean },
								     { "list", &list },
								     { "not", &not_ },
								     { "or", &or_ },
								     { "and", &and_ },
	                                                             { "=", &equals },
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

	static void ensure_not_empty(Pair* args)
	{
		if (is_empty(args)) {
			nd_pop_front(args);
		}
	}

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

	Object* defvar(Pair* args)
	{
		auto name = get_raw_arg<Symbol>(args);
		auto o = get_arg<Object>(args);
		state->make_global(name->symbol, o);
		return o;
	}

	Object* let(Pair* args)
	{
		auto bindings = get_raw_arg<Pair>(args);
		state->push_local_scope();
		while (is_not_empty(bindings)) {
			auto pair = get_raw_arg<Pair>(bindings);
			auto name = get_raw_arg<Symbol>(pair)->symbol;
			auto o = get_arg<Object>(pair);
			state->make_local(name, o);
		}
		
		Object* res = nullptr;
		while (is_not_empty(args)) {
			res = get_arg<Object>(args);
		}
		
		state->pop_local_scope();
		
		return (res? res : ELL_NEW_NIL);
	}

	Object* set(Pair* args)
	{
		auto name = get_raw_arg<Symbol>(args)->symbol;
		if (state->exists_variable(name)) {
			auto o = get_arg<Object>(args);
			state->set_variable(name, o);
			return o;
		} else {
			error("Can't find variable `%s'", name.c_str());
			return nullptr;
		}
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

	Object* while_(Pair* args)
	{
		auto pred = get_raw_arg<Object>(args);
		auto exprs = args;
		Object* res = nullptr;
		while (eval(pred)->boolean()) {
			while (is_not_empty(exprs)) {
				res = get_arg<Object>(exprs);
			}
			exprs = args;
		}
		return (res? res : ELL_NEW_NIL);
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
	 *  Logical Operators
	 *----------------------------------------------------------*/

	Object* not_(Pair* args)
	{
		auto o = get_arg<Object>(args);
		return make<Boolean>(not o->boolean());
	}

	Object* or_(Pair* args)
	{
		ensure_not_empty(args);
		Object* o;
		while (is_not_empty(args)) {
			o = get_arg<Object>(args);
			if (o->boolean()) {
				return o;
			}
		}
		return o;
	}


	Object* and_(Pair* args)
	{
		ensure_not_empty(args);
		Object* o;
		while (is_not_empty(args)) {
			o = get_arg<Object>(args);
			if (not o->boolean()) {
				return o;
			}
		}
		return o;	
	}

	/*------------------------------------------------------------
	 *  Comparison
	 *----------------------------------------------------------*/

	Object* equals(Pair* args)
	{
		auto l = get_arg<Object>(args);
		bool res = false;
		do {
			auto r = get_arg<Object>(args);
			if (l->type == r->type) {
				res = l->equals(r);
				if (not res) break;
			} else if (l->is_a_number() and r->is_a_number()) {
				res = (l->number() == r->number());
				if (not res) break;
			} else {
				res = false;
				break;
			}
		} while (is_not_empty(args));
		return make<Boolean>(res);
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
					s << get_arg<Object>(args)->str();
					break;
				case 'r':
					s << get_arg<Object>(args)->repr();
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
