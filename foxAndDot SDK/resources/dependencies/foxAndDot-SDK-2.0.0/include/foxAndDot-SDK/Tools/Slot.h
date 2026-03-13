#pragma once
#include "Connectable.h"
template <typename args_package>
class Slot : public Connectable<args_package>
{
	friend class Core;
public:
	virtual void do_something() {}
private:
	void operator()() override
	{
		do_something();
		Connectable<args_package>::operator()();
	}
};

