#pragma once
#include <list>
#include <string>

class Interaction;
class Participant;

class InteractionParser
{
public:
	static std::list<Interaction> parse(const std::list<Participant>& participants, const std::string& input);

private:
	static Participant lane_by_name(const std::list<Participant>& participants, const std::string& name);
};
