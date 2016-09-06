#include "electrum.hpp"

namespace ell {

	void repl()
	{
		init_error("stdin", ErrorMode::REPL);
		int index = -1;
		
		for ever {
			try {
				index++;
				std::string buffer;
				
				std::cout << "In [" << index << "]: ";
				std::getline(std::cin, buffer);

				if (buffer == ":q") {
					break;
				} else if (buffer == ":cls") {
					std::system("clear");
					continue;
				} else if (buffer == "") {
					index--;
					std::cout << std::endl;
					continue;
				}
				
				Object* o = read(buffer + '\n');
				//if (o) o = eval(o);
				if (o) std::cout << "Out [" << index << "]: " << o->repr() << std::endl << std::endl;
				
				//gc();
			} catch (ErrorException& e) { }
		}
	}

}
