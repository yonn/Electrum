#ifndef ELECTRUM_BUILTINS_HPP
#define ELECTRUM_BUILTINS_HPP

#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>

#include "state.hpp"
#include "eval.hpp"
#include "object.hpp"
#include "error.hpp"

namespace ell {

	extern thread_local State* state;

	using BuiltinFunction = Object* (*)(Pair*);
	extern std::map<std::string, BuiltinFunction> builtin_functions;

	/*------------------------------------------------------------
	 *  Builtin Functions
	 *----------------------------------------------------------*/


	/*------------------------------------------------------------
	 *  General
	 *----------------------------------------------------------*/

	Object* type(Pair* args);
	Object* defvar(Pair* args);
	Object* let(Pair* args);
	Object* set(Pair* args);
	
	/*------------------------------------------------------------
	 *  Flow Control
	 *----------------------------------------------------------*/

	Object* if_(Pair* args);

	/*------------------------------------------------------------
	 *  Type conversions
	 *----------------------------------------------------------*/

	Object* str(Pair* args);
	Object* int_(Pair* args);
	Object* float_(Pair* args);
	Object* boolean(Pair* args);
	Object* list(Pair* args);

	/*------------------------------------------------------------
	 *  Logical Operators
	 *----------------------------------------------------------*/

	Object* not_(Pair* args);
	Object* or_(Pair* args);
	Object* and_(Pair* args);

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

	/*------------------------------------------------------------
	 *  IO
	 *----------------------------------------------------------*/
	
	Object* printf(Pair* args);
	Object* printfln(Pair* args);
	Object* format(Pair* args);
	
}

#endif /*ELECTRUM_BUILTINS_HPP*/
