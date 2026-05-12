#pragma once
#include "Connectable.h"
#include <queue>
template <typename args_package, typename owner>
class Slot : public Connectable<args_package>
{
	friend class Core;

	owner* slot_owner = nullptr;
	void(owner::* owner_function)(const args_package&) = nullptr;

	//------------------------------------------------------------------------------------

		std::queue<args_package> args_buffer;

	//------------------------------------------------------------------------------------
		void push_args(const args_package& args)
		{
			this->args_buffer.push(args);
		}

		void operator()() override
		{
			this->args = this->args_buffer.front();
			this->args_buffer.pop();

			if (this->owner_function != nullptr and this->slot_owner != nullptr)
			{
				((*slot_owner).*owner_function)(this->args);
			}
			else
			{
				
			}
			Connectable<args_package>::operator()();		}

	//------------------------------------------------------------------------------------

public:

	Slot(void(owner::* owner_function)(const args_package&),owner* owner) : Connectable<args_package>()
	{
		this->owner_function = owner_function;
		this->slot_owner = owner;
	}
	~Slot()
	{
		this->owner_function = nullptr;
		this->slot_owner = nullptr;
	}
};
