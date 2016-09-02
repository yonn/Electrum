#include "lexer.hpp"

namespace electrum {

	static bool comment = false;
	static bool separator = false;

	static bool is_token(const std::string& token);

	static TokenIR classify(const std::string& token, size_t line_num);

	static bool is_whitespace(char c);
	static bool is_number(char c);
	static bool is_separator(char c);

	static bool is_number_token(const std::string& token);
	static bool is_string_token(const std::string& token);
	static bool is_comment_token(const std::string& token);

	static std::set<char> separators = { '(', ')', '[', ']', '{', '}' }; 

	const std::string TokenIR::str() const
	{
		const static std::array<std::string, 8> Type_str = { "Keyword",
		                                                     "Symbol",
							             "String",
							             "DecNum",
							             "FloatNum",
							             "Separator" };

		std::ostringstream s;
		s << Type_str[(size_t)this->tid] << "[ " << this->token << " ]";
		return s.str();
	}

	TokenList tokenize(const std::string& line, size_t line_num)
	{
		std::vector<std::string> tokens;
		std::string buf = "";
		for (size_t i = 0; i < line.size(); i++) {
			const char c = line[i];

			if (not is_token(buf + c)) {
				if (comment) {
					comment = false;
					buf = "";
					continue;
				}
				if (buf != "") {
					tokens.push_back(buf);
				}
				buf = "";
				if (not is_whitespace(c)) {
					buf += c;
				}
				if (separator) {
					tokens.push_back(buf);
					buf = "";
					separator = false;
				}
			} else {
				buf += c;
			}
		}
		if (buf != "") {
			tokens.push_back(buf);
		}
		
		TokenList res;

		for (const auto& t: tokens) {
			res.push_back(classify(t, line_num));
		}

		return res;
	}

	bool is_token(const std::string& token)
	{
		if (is_comment_token(token)) return true; 
		else if (is_string_token(token)) return true;
		else if (is_whitespace(token[token.size() - 1])) return false;
		else if (is_separator(token[token.size() - 1])) {
			separator = true;
			return false;
		}
		else if (is_number_token(token)) return true;
		else return true;
	}

	TokenIR classify(const std::string& token, size_t line_num)
	{
		TokenIR res;
		res.line_number = line_num;
		res.token = token;

		if (token[0] == '"' and token[token.size() - 1] == '"') {
			res.tid = TokenIR::Type::String;
		} else if (is_number_token(token)) {
			auto fn = std::count(token.begin(), token.end(), '.');
			if (fn != 0) {
				res.tid = TokenIR::Type::FloatNum;
			} else {
				res.tid = TokenIR::Type::DecimalNum;
			}
		} else if (separators.count(token[0]) == 1) {
			res.tid = TokenIR::Type::Separator;
		} else {
			if (token[0] == ':') {
				res.tid = TokenIR::Type::Keyword;
			} else {
				res.tid = TokenIR::Type::Symbol;
			}
		}

		return res;
	}

	bool is_whitespace(char c)
	{
		return c == ' '  or
		       c == '\t' or
		       c == '\n';
	}

	bool is_number(char c)
	{
		return c >= '0' and c <= '9';
	}

	bool is_separator(char c)
	{
		return (separators.count(c) == 1);
	}

	bool is_number_token(const std::string& token)
	{
		bool period = false;

		for (size_t i = 0; i < token.size(); i++) {
			auto c = token[i];

			if (c == '.' and not period) {
				period = true;
				continue;	
			} else if (not is_number(c) and not (c == '_')) {
				return false;
			}
		}
		return true;
	}



	bool is_string_token(const std::string& token)
	{
		if (token[0] == '"') {
			if (token.size() > 2 and token[token.size() - 2] == '"') {
				if (token.size() > 2 and token[token.size() - 2] == ';') {
					return true;
				}
				return false;
			}
			return true;
		}
		return false;
	}

	bool is_comment_token(const std::string& token)
	{
		if (token[0] != ';' and token[0] != '#') return false;

		comment = true;

		if (token[0] == '#') {
			if (token[1] == '|') {
				return not (token[token.size() - 2] == '#' and token[token.size() - 3] == '|');
			} else {
				goto not_a_comment;
			}
		} else if (token[0] == ';') {
			return not (token[token.size() - 1] == '\n');
		} else {
		not_a_comment:
			comment = false;
			return false;
		}

		return true;
	}

}
