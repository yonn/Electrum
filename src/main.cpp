#include <iostream>

#include "electrum.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		ell::repl();
	} else {
		ell::execute_file(argv[1]);
	}

	return 0;
}
