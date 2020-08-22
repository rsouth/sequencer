#include "Participant.h"

Participant::Participant(int index, std::string name): index_(index), name_(std::move(name))
{
}


int Participant::get_index() const
{
	return this->index_;
}

std::string Participant::get_name() const
{
	return this->name_;
}
