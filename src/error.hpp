#ifndef ELECTRUM_ERROR_HPP
#define ELECTRUM_ERROR_HPP

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>

namespace ell {
	
	extern std::map<size_t, std::string> lines;

	void init_error(const std::string& filename);
	
	void error(std::string fmt, ...);
	void error(size_t line_number, std::string fmt, ...);
	
}

#endif /*ELECTRUM_ERROR_HPP*/
