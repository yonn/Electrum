#ifndef ELECTRUM_STATE_HPP
#define ELECTRUM_STATE_HPP

#include <string>
#include <map>
#include <deque>

#include "object.hpp"
#include "error.hpp"

namespace ell {

	using GlobalState = std::map<std::string, Object*>;
	using LocalState = std::deque<std::map<std::string, Object*>>;
	
	class State {
	public:

		State();

		void make_global(std::string name, Object* val);
		void make_local(std::string name, Object* val);

		void push_local_scope();
		void pop_local_scope();

		bool exists_variable(std::string name);

		Object* get_variable(std::string name);
		void set_variable(std::string name, Object* val);
		
	private:

		GlobalState globals;
		std::deque<LocalState> locals;
		
	};

}

#endif /*ELECTRUM_STATE_HPP*/
