#include "object.hpp"

namespace ell {

	const std::string Object::TYPE = ELL_CORE_TYPE(Object);
	const std::string Integer::TYPE = ELL_CORE_TYPE(Integer);
	const std::string Float::TYPE = ELL_CORE_TYPE(Float);
	const std::string String::TYPE = ELL_CORE_TYPE(String);
	const std::string Symbol::TYPE = ELL_CORE_TYPE(Symbol);
	const std::string Pair::TYPE = ELL_CORE_TYPE(Pair);
	const std::string Keyword::TYPE = ELL_CORE_TYPE(Keyword);
	const std::string Quote::TYPE = ELL_CORE_TYPE(Quote);
	const std::string Boolean::TYPE = ELL_CORE_TYPE(Boolean);

	bool is_empty(Pair* p)
	{
		return (not p->car and not p->cdr);
	}

	bool is_not_empty(Pair* p)
	{
		return (p->car or p->cdr);
	}

	void push_back(Pair* p, Object* o)
	{

		if (is_empty(p)) {
			p->car = o;
			return;
		}

		Pair* node = p;
		
		for (; node->cdr != nullptr; node = (Pair*)node->cdr) { }
		node->cdr = make<Pair>(o, nullptr);
	}

	Object* pop_back(Pair* p)
	{
		if (is_empty(p)) {
			error("Attempted to pop_back on an empty list.");
		}

		Pair* node = p;
		Pair* prev;

		for (; node->cdr != nullptr; node = (Pair*)node->cdr) { prev = node; }
		prev->cdr = nullptr;
		Object* res = node->car;
		node->init(nullptr, nullptr);
		return res;
	}

	Object* nd_pop_front(Pair*& p)
	{
		if (is_empty(p)) {
			error("Attempted to pop_front on an empty list.");
		}

		Object* res = p->car;
		if (p->cdr) {
			p = (Pair*)p->cdr;
		} else {
			p = ELL_NEW_NIL;
		}
		return res;
	}
	
}
