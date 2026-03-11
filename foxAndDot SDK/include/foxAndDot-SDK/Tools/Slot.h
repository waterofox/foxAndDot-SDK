#pragma once
#include "Connectable.h"
#include <queue>
template <typename args_package>
class Slot : public Connectable<args_package>
{
	friend class Core;
private:
	std::queue<args_package> args_buffer;
	void operator()() override
	{
		Connectable<args_package>::push_args(args_buffer.front());
		do_something();
		Connectable<args_package>::operator()();
		this->args_buffer.pop();
	}
public:
	void push_args(const args_package& args)
	{
		this->args_buffer.push(args);
	}
	virtual void do_something() {}
};
