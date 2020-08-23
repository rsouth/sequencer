#include "InteractionParser.h"


#include "Interaction.h"
#include "StringUtils.h"
#include "ParsingUtils.h"

std::list<Interaction> InteractionParser::parse(const std::list<Participant>& participants, const std::string& input)
{
	std::list<Interaction> interactions;

	try
	{
		auto all_lines_split = StringUtils::split(input, "\n");
		auto interaction_count = 0;
		for (const auto& line : all_lines_split)
		{
			// lines with -> are 'interactions'
			if (StringUtils::contains(line, "->"))
			{
				std::string token = ParsingUtils::parse_token(line);
				auto line_split = StringUtils::split(line, token);
				auto from_name = StringUtils::trim_copy(line_split[0]);
				auto to_name = StringUtils::trim_copy(line_split[1]);

				// parse interaction message
				std::string message;
				try
				{
					if (StringUtils::contains(to_name, ":"))
					{
						auto message_start_index = to_name.find_first_of(':');
						auto name = StringUtils::trim_copy(to_name.substr(0, message_start_index));
						message = StringUtils::trim_copy(
							to_name.substr(message_start_index + 1, to_name.length() - (message_start_index + 1)));
						to_name = name;
					}
				}
				catch (std::exception& ex)
				{
					// logger.atWarning().log("Interaction message_ is incomplete, not parsing");
				}

				if (from_name.length() > 0 && to_name.length() > 0)
				{
					auto from_lane = lane_by_name(participants, from_name);
					auto to_lane = lane_by_name(participants, to_name);

					bool is_reply = StringUtils::contains(token, "--");
					bool is_async = StringUtils::contains(token, ">>");
					auto interaction = Interaction(interaction_count, from_lane, to_lane, message, is_reply, is_async);
					interactions.emplace_back(interaction);
					interaction_count++;

					if (interaction.is_self_referential())
					{
						// self-referential so increment interaction count one more time, for the interaction back to self
						interaction_count++;
					}
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		// logger.atWarning().log("Exception while parsing interactions, exception: " + ex.getMessage());
	}

	// logger.atInfo().log("Found [" + interactions.size() + "] interactions " + interactions);
	return interactions;
}

Participant InteractionParser::lane_by_name(const std::list<Participant>& participants, const std::string& name)
{
	for (auto participant : participants)
	{
		if (participant.get_name() == name)
		{
			return participant;
		}
	}

	throw std::exception("no participant found");
}
