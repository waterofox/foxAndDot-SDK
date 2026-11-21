#pragma once
#include "Signal.h"
#include "Slot.h"

template <typename args_p, typename owner>
void connect(Signal<args_p>* signal, Slot<args_p, owner>* slot)  //initialisation of connection with slot
{
	signal->next_c.emplace(slot, Connection_Types::Slot);
	slot->connected_to.insert(signal);
}

template<typename args_p>
void connect(Signal<args_p>* signal, Signal<args_p>* signal_2) //initialisation of connection with signal
{
	signal->next_c.emplace(signal_2, Connection_Types::Signal);
	signal_2->connected_to.insert(signal);
}