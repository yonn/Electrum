#ifndef ELECTRUM_BASE_OBJECT_HPP
#define ELECTRUM_BASE_OBJECT_HPP

#include <string>
#include <sstream>

#define ELL_CORE_TYPE(t) ("ell.core." + std::string(#t))

namespace ell {

	template<typename O, typename ... Args>
	O* make(Args ... args)
	{
		O* o = new O;
		o->init(args...);
		return o;
	}

	class Object {
	public:

		virtual Object* init()
		{
			this->type = Object::TYPE;
			return this;
		}

		virtual std::string repr()
		{
			std::ostringstream s;
			s << "<" << this->type << ": " << (void*)this << ">";
			return s.str();
		}

		virtual std::string str()
		{
			return this->repr();
		}

		virtual bool boolean()
		{
			return true;
		}

		virtual bool is_a_number()
		{
			return false;
		}

		virtual long double number()
		{
			error("Type `%s' is not a number.", this->type.c_str());
			return 0.0;
		}

		virtual bool equals(Object* o)
		{
			return (this == o);
		}

		std::string type;

		static const std::string TYPE;
		
	};

}

#endif /*ELECTRUM_BASE_OBJECT_HPP*/
