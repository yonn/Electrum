#ifndef ELECTRUM_BUILTINS_HPP
#define ELECTRUM_BUILTINS_HPP

#include <map>
#include <string>

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

	/*------------------------------------------------------------
	 *  Arithmetic
	 *----------------------------------------------------------*/

	Object* add(Pair* args);
	Object* multiply(Pair* args);
	Object* subtract(Pair* args);
	Object* divide(Pair* args);
}

#endif /*ELECTRUM_BUILTINS_HPP*/
