#ifndef ELECTRUM_ERROR_HPP
#define ELECTRUM_ERROR_HPP

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <exception>

namespace ell {
	
	extern std::map<size_t, std::string> lines;
	extern size_t error_line_number;

	enum class ErrorMode {
		REPL,
		Script
	};

	class ErrorException: public std::exception {
	public:

		virtual const char* what() const throw()
		{
			return "";
		}
		
	};

	void init_error(const std::string& filename, ErrorMode m);
	
	void general_error(std::string fmt, ...);
	void error(std::string fmt, ...);
	
}

#endif /*ELECTRUM_ERROR_HPP*/
