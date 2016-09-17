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

		void make_global(std::string name, Object* val);

		bool exists_variable(std::string name);

		Object* get_variable(std::string name);
		void set_variable(std::string name, Object* val);
		
	private:

		GlobalState globals;
		
	};

}

#endif /*ELECTRUM_STATE_HPP*/
