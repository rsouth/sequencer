#pragma once

#include <list>

#include "Interaction.h"
#include "MetaData.h"

class Participant;

class Diagram
{
public:
	Diagram(MetaData meta_data, std::list<Participant> participants, std::list<Interaction> interactions);

	MetaData get_meta_data() const;
	std::list<Participant> get_participants() const;
	std::list<Interaction> get_interactions() const;

private:
	MetaData meta_data_;
	std::list<Participant> participants_;
	std::list<Interaction> interactions_;
};
