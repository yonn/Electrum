#ifndef ELECTRUM_ELECTRUM_HPP
#define ELECTRUM_ELECTRUM_HPP

#include <iostream>
#include <cstdlib>

#include "lexer.hpp"
#include "read.hpp"
#include "eval.hpp"
#include "error.hpp"

#define ever (;;)

namespace ell {

	void repl();
	void execute_file(const std::string& filename);

}

#endif /*ELECTRUM_ELECTRUM_HPP*/
