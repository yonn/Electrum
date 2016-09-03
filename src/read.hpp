#ifndef ELECTRUM_READ_HPP
#define ELECTRUM_READ_HPP

#include <string>
#include <fstream>

#include "lexer.hpp"
#include "error.hpp"

namespace electrum {

	TokenList read_file(const std::string& filename);
	
}

#endif /*ELECTRUM_READ_HPP*/
