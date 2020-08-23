#pragma once
#include <list>
#include <string>

class Participant;

class ParticipantsParser
{
public:
	static std::list<Participant> parse(const std::string& input);

private:
	static std::list<std::string> parse_lane_lanes(const std::string& line, const std::string token);
};
