#include "object.hpp"

namespace electrum {

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
			error("Attempted to pop_back on an empty list."); //TODO upgrade error
		}

		Pair* node = p;
		Pair* prev;

		for (; node->cdr != nullptr; node = (Pair*)node->cdr) { prev = node; }
		prev->cdr = nullptr;
		Object* res = node->car;
		node->init(nullptr, nullptr);
		return res;
	}
	
}
