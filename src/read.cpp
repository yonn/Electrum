#include "read.hpp"

namespace ell {

	TokenList read_file(const std::string& filename)
	{
		TokenList tokens;
		std::string line, buffer;
		size_t orig_line_num, line_num = 1;
		bool comment = false, flag = true;

		std::ifstream in(filename);
		if (in) {

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

	static Object* read_impl(const TokenIR& next);
	static Object* read_list();
	static Object* read_atom(const TokenIR& next);

	static TokenList curr_tokens;
	static bool finished;
	
	static TokenIR fetch()
	{
		if (not curr_tokens.empty()) {
			auto token = curr_tokens.front();
			curr_tokens.pop_front();
			return token;
		}

		finished = true;
		return TokenIR();
	}

	static void return_token(TokenIR token)
	{
		curr_tokens.push_front(token);
	}

	Object* read_one(TokenList& tokens)
	{
		if (tokens.empty()) {
			return nullptr;
		} else {
			curr_tokens = tokens;
			finished = false;
			return read_impl(fetch());
		}
	}

	Object* read(const std::string& line)
	{
		if (line == "") return nullptr;

		auto tokens = tokenize(line, 0);
		return read_one(tokens);
	}

	static Object* read_impl(const TokenIR& next)
	{
		if (next.token == "(") {
			return_token(next);
			return read_list();
		} else {
			return read_atom(next);
		}
	}

	static Object* read_list()
	{
		Pair* list = ELL_NEW_NIL;
		list->line_number = fetch().line_number;
		while (not finished) {
			auto token = fetch();
			if (token.token == ")") {
				return list;
			} else {
				push_back(list, read_impl(token));
			}
		}
		error(list->line_number, "Incomplete list!");
		return nullptr;
	}

	static Object* read_atom(const TokenIR& next)
	{
		Object* o;
		if (next.token == "nil") {
			return ELL_NEW_NIL;
		} else if (next.tid == TokenIR::Type::DecimalNum) {
			o = make<Integer>(std::stol(next.token));
		} else if (next.tid == TokenIR::Type::FloatNum) {
			o =  make<Float>(std::stod(next.token));
		} else if (next.tid == TokenIR::Type::String) {
			std::string res;
			for (size_t i = 1; i < next.token.length() - 1; i++) {
				res += next.token[i];
			}
			o = make<String>(res);
		} else if (next.tid == TokenIR::Type::Keyword) {
			o = make<Keyword>(next.token);
		} else if (next.tid == TokenIR::Type::Symbol) {
			o = make<Symbol>(next.token);
		} else if (next.tid == TokenIR::Type::Quote) {
			o = make<Quote>(read_impl(fetch()));
		} else {
			error(next.line_number, "Token `%s' could not be read!", next.token.c_str());
			return nullptr;
		}
		o->line_number = next.line_number;
		return o;
	}
	
}
