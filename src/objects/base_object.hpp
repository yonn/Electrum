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
			s << "Object[" << (void*)this << "]";
			return s.str();
		}

		virtual std::string str()
		{
			return this->repr();
		}

		std::string type;

		static const std::string TYPE;
		
	};

}

#endif /*ELECTRUM_BASE_OBJECT_HPP*/
