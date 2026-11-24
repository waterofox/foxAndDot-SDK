#pragma once
#include "Slot.h"

#include <unordered_map>


template<typename args_package>
class Signal : public Connectable<args_package>
{
	friend class Core;

	std::unordered_map<Connectable<args_package>*, Connection_Types> next_c;


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
	
	void back_disconnect(Connectable<args_package>* connected) override
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

	Signal() = default;
	Signal(const Signal<args_package>& other){}
	Signal<args_package>& operator=(const Signal<args_package>& other) 
	{
		return *this;
	}

	~Signal()
	{
		disconnect_all();
	}

	template <typename args_p, typename owner>
	friend void connect(Signal<args_p>* signal, Slot<args_p, owner>* slot);

	template<typename args_p> 
	friend void connect(Signal<args_p>* signal, Signal<args_p>* signal_2); //initialisation of connection with signal

	void disconnect(Connectable<args_package>* connected)  override                          //disconnect signal or slot from this signal
	{
		if (this->next_c.find(connected) != this->next_c.end())
		{
			this->next_c.erase(connected);
			connected->connected_to.erase(this);
		}
		else
		{
			printf("SIGNAL WARNING: Attempting to disconnect an unconnected slot or signal\n");
			return;
		}
	}

	void disconnect_all() //disconnect all signals and slots from this signal
	{
		for (auto& connected : next_c)
		{
			disconnect(connected.first);
		}
	}
	


};
