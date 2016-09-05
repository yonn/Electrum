#include "error.hpp"

namespace ell {
	
	std::string error_filename;
	std::map<size_t, std::string> lines;


	void init_error(const std::string& filename)
	{
		error_filename = filename;
	}
	
	void error(std::string fmt, ...)
	{
		fmt += '\n';
		fmt += '\n';
		std::va_list args;
		va_start(args, fmt.c_str());

		std::fprintf(stderr, "Fatal Error: \n");
		std::vfprintf(stderr, fmt.c_str(), args);

		va_end(args);

		exit(1);
	}
	
	void error(size_t line_number, std::string fmt, ...)
	{
		std::va_list args;
		va_start(args, fmt.c_str());
		
		std::fprintf(stderr, "In file: \"%s\"::%zu: Fatal Error: ", error_filename.c_str(), line_number);
		std::vfprintf(stderr, fmt.c_str(), args);
		std::fprintf(stderr, "\n\t%s\n\n", lines[line_number].c_str());

		va_end(args);

		exit(1);
	}
	
}
