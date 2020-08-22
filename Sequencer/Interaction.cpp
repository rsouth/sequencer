#include "Interaction.h"

Interaction::Interaction(int index, Participant& from_participant, Participant& to_participant,
                         const std::string& message):
	index_(index),
	from_participant_(std::move(from_participant)),
	to_participant_(std::move(to_participant)),
	message_(message)
{
}

bool Interaction::is_self_referential() const
{
	return this->from_participant_.get_name() == this->to_participant_.get_name();
}

std::string Interaction::get_message() const
{
	return this->message_;
}

Participant Interaction::get_from() const
{
	return this->from_participant_;
}

Participant Interaction::get_to() const
{
	return this->to_participant_;
}

int Interaction::get_index() const
{
	return this->index_;
}
