#pragma once
#include "Connectable.h"
#include <queue>
template <typename args_package, typename Owner>
class Slot : public Connectable<args_package>
{
	friend class Core;

	Owner* slot_owner = nullptr;
	void(Owner::* owner_function)(const args_package&) = nullptr;

	//------------------------------------------------------------------------------------

		std::queue<args_package> args_buffer;

	//------------------------------------------------------------------------------------
		void push_args(const args_package& args) override
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
				printf("SLOT ERROR: Slot construction is not completed.\n");
			}
			Connectable<args_package>::operator()();		
		}

	//------------------------------------------------------------------------------------

public:

	Slot() : Connectable<args_package>() {}

	Slot(const Slot<args_package, Owner>& other)
	{
		this->args = other.args;
		this->args_buffer = other.args_buffer;

		this->slot_owner = nullptr;
		this->owner_function = nullptr;
	}

	Slot<args_package,Owner>& operator=(const Slot<args_package,Owner>& other)
	{
		if (this == &other) { return *this; }
		
		this->args = other.args;
		this->args_buffer = other.args_buffer;

		this->slot_owner = nullptr;
		this->owner_function = nullptr;

		return *this;
	}

	void reassign(void(Owner::* owner_function)(const args_package&), Owner* owner)
	{
		this->owner_function = owner_function;
		this->slot_owner = owner;
	}

	Slot(void(Owner::* owner_function)(const args_package&),Owner* owner) : Slot<args_package,Owner>()
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
