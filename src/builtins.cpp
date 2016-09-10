#include "builtins.hpp"

namespace ell {

	std::map<std::string, BuiltinFunction> builtin_functions = { {"type", &type} };

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

}
