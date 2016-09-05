#ifndef ELECTRUM_READ_HPP
#define ELECTRUM_READ_HPP

#include <string>
#include <fstream>

#include "lexer.hpp"
#include "object.hpp"
#include "error.hpp"

namespace ell {

	TokenList read_file(const std::string& filename);
	
}

#endif /*ELECTRUM_READ_HPP*/
