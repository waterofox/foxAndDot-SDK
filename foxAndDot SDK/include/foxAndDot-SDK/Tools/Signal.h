#pragma once
#include "Connectable.h"

#include <queue>

enum class Connection_Types
{
	Undefined = -1,
	Signal = 0,
	Slot = 1,
};

template<typename args_package>
class Signal : public Connectable<args_package>
{
	friend class Core;
private:

	std::queue<Executable*>* core_queue = nullptr;

	void handle_connected_slot()
	{
		this->core_queue->push(this->next_connectable);
	}

	void handle_connected_signal()
	{
		Signal<args_package>* next_signal_pointer = static_cast<Signal<args_package>*>(next_connectable);
		next_signal_pointer->core_queue = this->core_queue;

		(*(this->next_connectable))();
	}

	Connectable<args_package>* next_connectable = nullptr;
	
	Connection_Types next_connectable_type = Connection_Types::Undefined;

	void operator()() override 
	{
		
		if (this->core_queue == nullptr)
		{
			printf("SIGNAL ERROR: Incorrect signal call. Use <Core::emit>\n");
			return;
		}
		else if (this->next_connectable == nullptr)
		{
			printf("SIGNAL WARNING: No Signal/Slot is connected\n");
			return;
		}

		next_connectable->push_args(this->args);

		switch (next_connectable_type)
		{
		case Connection_Types::Signal: { this->handle_connected_signal(); } break;
		case Connection_Types::Slot: { this->handle_connected_slot(); } break;
		default: 
			break;
		}

		this->core_queue = nullptr;

		Connectable<args_package>::operator()();
		
	}

public:
	Signal() = default;
	~Signal() = default;
};
