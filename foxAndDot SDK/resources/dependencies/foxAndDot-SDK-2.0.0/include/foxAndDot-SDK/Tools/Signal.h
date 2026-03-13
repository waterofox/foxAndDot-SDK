#pragma once
#include "Connectable.h"

#include <queue>

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
protected:
	Connectable<args_package>* next_connectable = nullptr;
	int next_connectable_type = 0;

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
		case 0: { this->handle_connected_signal(); } break;
		case 1: { this->handle_connected_slot(); } break;
		default: 
			break;
		}

		this->core_queue = nullptr;

		Connectable<args_package>::operator()();
		
	}
};
