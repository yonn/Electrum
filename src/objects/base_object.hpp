#ifndef ELECTRUM_BASE_OBJECT_HPP
#define ELECTRUM_BASE_OBJECT_HPP

#include <string>
#include <sstream>

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
			return this;
		}

		virtual std::string repr()
		{
			std::ostringstream s;
			s << "Object[" << (void*)this << "]";
			return s.str();
		}
		
	};

}

#endif /*ELECTRUM_BASE_OBJECT_HPP*/
