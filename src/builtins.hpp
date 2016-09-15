#ifndef ELECTRUM_BUILTINS_HPP
#define ELECTRUM_BUILTINS_HPP

#include <map>
#include <string>
#include <cmath>

#include "eval.hpp"
#include "object.hpp"
#include "error.hpp"

namespace ell {

	using BuiltinFunction = Object* (*)(Pair*);
	extern std::map<std::string, BuiltinFunction> builtin_functions;

	/*------------------------------------------------------------
	 *  Builtin Functions
	 *----------------------------------------------------------*/


	/*------------------------------------------------------------
	 *  General
	 *----------------------------------------------------------*/

	Object* type(Pair* args);
	Object* str(Pair* args);

	/*------------------------------------------------------------
	 *  Arithmetic
	 *----------------------------------------------------------*/

	Object* add(Pair* args);
	Object* multiply(Pair* args);
	Object* subtract(Pair* args);
	Object* divide(Pair* args);
	Object* power(Pair* args);
	Object* sqrt(Pair* args);
	Object* sin(Pair* args);
	Object* cos(Pair* args);
	Object* tan(Pair* args);
	Object* asin(Pair* args);
	Object* acos(Pair* args);
	Object* atan(Pair* args);
	
}

#endif /*ELECTRUM_BUILTINS_HPP*/
