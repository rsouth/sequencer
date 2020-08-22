#pragma once
#include <string>

class Participant
{
public:
	Participant(int index, std::string name);

	int get_index() const;
	std::string get_name() const;

private:
	int index_;
	std::string name_;
};
