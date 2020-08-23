#pragma once
#include "Participant.h"

class Interaction
{
public:
	Interaction(int index, Participant& from_participant, Participant& to_participant, const std::string& message, bool is_reply = false, bool is_async = false);

	std::string get_message() const;
	
	Participant get_from() const;
	
	Participant get_to() const;
	
	int get_index() const;

	bool is_self_referential() const;

	bool is_reply() const;

	bool is_async() const;
	
private:
	int index_;
	Participant from_participant_;
	Participant to_participant_;
	std::string message_;
	bool is_reply_;
	bool is_async_;
};
