#include "state.hpp"

namespace ell {

	void State::make_global(std::string name, Object* val)
	{
		if (this->globals.count(name) == 1) {
			error("The variable `%s' already exists", name.c_str());
		} else {
			this->globals[name] = val;
		}
	}

	bool State::exists_variable(std::string name)
	{
		return (this->globals.count(name) == 1);
	}

	Object* State::get_variable(std::string name)
	{
		if (this->globals.count(name) == 1) {
			return this->globals[name];
		} else {
			error("Could not find variable `%s'", name.c_str());
			return nullptr;
		}
	}

	void State::set_variable(std::string name, ell::Object* val)
	{
		if (this->globals.count(name) == 1) {
			this->globals[name] = val;
		} else {
			error("Could not find variable `%s'", name.c_str());
		}
	}

}
