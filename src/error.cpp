#include "error.hpp"

namespace ell {
	
	std::string error_filename;
	std::map<size_t, std::string> lines;
	size_t error_line_number;
	ErrorMode mode;


	void init_error(const std::string& filename, ErrorMode m)
	{
		error_filename = filename;
		mode = m;
	}
	
	void general_error(std::string fmt, ...)
	{
		fmt += '\n';
		fmt += '\n';
		std::va_list args;
		va_start(args, fmt.c_str());

		std::fprintf(stderr, "Fatal Error: \n");
		std::vfprintf(stderr, fmt.c_str(), args);

		va_end(args);

		if (mode == ErrorMode::REPL) {
			throw ErrorException();
		} else {
			exit(1);
		}
	}
	
	void error(std::string fmt, ...)
	{
		std::va_list args;
		va_start(args, fmt.c_str());
		
		std::fprintf(stderr, "In file: \"%s\"::%zu: Fatal Error: ", error_filename.c_str(), error_line_number);
		std::vfprintf(stderr, fmt.c_str(), args);
		std::fprintf(stderr, "\n\t%s\n\n", lines[error_line_number].c_str());

		va_end(args);
		
		if (mode == ErrorMode::REPL) {
			throw ErrorException();
		} else {
			exit(1);
		}
	}
	
}
