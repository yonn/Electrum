#include "state.hpp"

namespace ell {

	State::State()
	{
		this->locals.push_front(LocalState());
	}

	void State::make_global(std::string name, Object* val)
	{
		if (this->globals.count(name) == 1) {
			error("The variable `%s' already exists", name.c_str());
		} else {
			this->globals[name] = val;
		}
	}

	void State::make_local(std::string name, Object* val)
	{
		this->locals.front().front()[name] = val;
	}

	void State::push_local_scope()
	{
		this->locals.front().push_front(std::map<std::string, Object*>());
	}
	
	void State::pop_local_scope()
	{
		this->locals.front().pop_front();
	}

	bool State::exists_variable(std::string name)
	{
		for (auto& scope: this->locals.front()) {
			if (scope.count(name) == 1) {
				return true;
			}
		}
		return (this->globals.count(name) == 1);
	}

	Object* State::get_variable(std::string name)
	{
		if (this->exists_variable(name)) {
			for (auto& scope: this->locals.front()) {
				if (scope.count(name) == 1) {
					return scope[name];
				}
			}
			return this->globals[name];
		} else {
			error("Could not find variable `%s'", name.c_str());
			return nullptr;
		}
	}

	void State::set_variable(std::string name, ell::Object* val)
	{
		
		if (this->exists_variable(name)) {
			for (auto& scope: this->locals.front()) {
				if (scope.count(name) == 1) {
					scope[name] = val;
					return;
				}
			}
			this->globals[name] = val;
		} else {
			error("Could not find variable `%s'", name.c_str());
		}
	}

}
