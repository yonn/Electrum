#include "read.hpp"

namespace electrum {

	TokenList read_file(const std::string& filename)
	{
		TokenList tokens;
		std::string line, buffer;
		size_t orig_line_num, line_num = 1;
		bool comment = false, flag = true;

		std::ifstream in(filename);
		if (in) {

			init_error(filename);

			while (std::getline(in, line)) {
				if (line.find("#|") != std::string::npos) {
					comment = true;
					orig_line_num = line_num;
				}
				if (comment) {
					buffer += "\n" + line;
					flag = false;
				}
				if (line.find("|#") != std::string::npos) {
					comment = false;
					lines[orig_line_num] = buffer + '\n';
					buffer = "";
					goto end;

				}
				if (flag) {
					lines[line_num] =  line + '\n';
				}
			end:
				line_num++;
				flag = true;
			}
		} else {
			error("Could not open file: %s", filename.c_str());
		}
		
		for (const auto& l: lines) {
			auto ts = tokenize(l.second, l.first);
			for (auto& t: ts) {
				tokens.push_back(t);
			}
		}

		return tokens;
	 }
	
}
