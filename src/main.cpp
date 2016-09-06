#include <iostream>

#include "electrum.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		ell::repl();
	}
	
	return 0;
}
