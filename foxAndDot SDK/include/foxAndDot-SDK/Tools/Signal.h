#pragma once
#include "Slot.h"

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

	std::queue<Executable*>* core_queue = nullptr;

	void handle_connected_slot(Connectable<args_package>* next_connectable)
	{
		this->core_queue->push(next_connectable);
	}

	void handle_connected_signal(Connectable<args_package>* next_connectable)
	{
		Signal<args_package>* next_signal_pointer = static_cast<Signal<args_package>*>(next_connectable);
		next_signal_pointer->core_queue = this->core_queue;

		(*(next_connectable))();
	}
	
	std::unordered_map<Connectable<args_package>*, Connection_Types> next_c;

	void operator()() override 
	{	
		if (this->core_queue == nullptr)
		{
			printf("SIGNAL ERROR: Incorrect signal call. Use <Core::emit>\n");
			return;
		}
		for (auto& next_connectable : next_c)
		{
			next_connectable.first->push_args(this->args);

			switch (next_connectable.second)
			{
			case Connection_Types::Signal: { this->handle_connected_signal(next_connectable.first); } break;
			case Connection_Types::Slot: { this->handle_connected_slot(next_connectable.first); } break;
			default:
				break;
			}
		}
		this->core_queue = nullptr;
		Connectable<args_package>::operator()();
	}

public:

	template<typename owner>
	friend static void connect(Signal<args_package>* signal,Slot<args_package,owner>* slot)
	{
		signal->next_c.emplace(slot, Connection_Types::Slot);
	}
	
	friend static void connect(Signal<args_package>* signal, Signal<args_package>* signal_2)
	{
		signal->next_c.emplace(signal_2, Connection_Types::Signal);
	}

	void disconnect(Connectable<args_package>* connected)
	{
		if (this->next_c.find(connected) != this->next_c.end())
		{
			this->next_c.erase(connected);
		}
		else
		{
			printf("SIGNAL WARNING: Attempting to disconnect an unconnected slot or signal\n");
			return;
		}
	}
	


};
