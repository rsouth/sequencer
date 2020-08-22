#include "Diagram.h"

#include <utility>

Diagram::Diagram(MetaData meta_data, std::list<Participant> participants, std::list<Interaction> interactions):
	meta_data_(std::move(meta_data)),
	participants_(std::move(participants)),
	interactions_(std::move(interactions))
{
}

MetaData Diagram::get_meta_data() const
{
	return this->meta_data_;
}

std::list<Participant> Diagram::get_participants() const
{
	return this->participants_;
}

std::list<Interaction> Diagram::get_interactions() const
{
	return this->interactions_;
}
