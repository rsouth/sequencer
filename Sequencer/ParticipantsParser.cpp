/*
 *     Copyright (C) 2020 rsouth (https://github.com/rsouth)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "ParticipantsParser.h"

#include <set>


#include "Participant.h"
#include "StringUtils.h"
#include "ParsingUtils.h"

std::list<Participant> ParticipantsParser::parse(const std::string& input)
{
	std::list<Participant> found_participants;

	try
	{
		std::list<std::string> known_participants;
		auto input_lines = StringUtils::split(input, "\n");

		// iterate input, parsing [FirstLane] -> [SecondLane] : Message
		for (const auto& line : input_lines)
		{
			if (StringUtils::contains(line, "->"))
			{
				auto token = ParsingUtils::parse_token(line);
				auto participant_names = parse_lane_lanes(line, token);
				known_participants.insert(known_participants.end(), participant_names.begin(), participant_names.end());
			}
		}

		// remove duplicate names found (keeping the order they were seen in the source)
		std::list<std::string>::iterator i, j;
		std::set<std::string> t_set;
		for (i = known_participants.begin(), j = known_participants.begin(); i != known_participants.end(); ++i)
		{
			if (t_set.insert(*i).second)
			{
				*j++ = *i;
			}
		}
		known_participants.erase(j, known_participants.end());

		// create a Participant for each found Participant
		auto it = known_participants.begin();
		for (unsigned long long ii = 0; ii < known_participants.size(); ii++)
		{
			// add new Participant
			found_participants.emplace_back(Participant(ii, *it));

			// advance the iterator by 1
			std::advance(it, 1);
		}
	}
	catch (const std::exception& e)
	{
		// logger.atWarning().log("Exception while parsing lanes, exception: " + ex.getMessage());
	}

	// logger.atInfo().log("Found [" + foundLanes.size() + "] Lanes " + foundLanes);
	return found_participants;
}


std::list<std::string> ParticipantsParser::parse_lane_lanes(const std::string& line, const std::string& token)
{
	std::list<std::string> lane_names;
	try
	{
		auto lanes_split = StringUtils::split(line, token);

		// 'from' lane is the first entry
		if (!lanes_split.empty())
		{
			const auto from_node = lanes_split.at(0);
			lane_names.emplace_back(StringUtils::trim_copy(from_node));
		}

		// 'to' lane is the second entry, but any message_ (":msg") must be removed first
		if (lanes_split.size() == 2)
		{
			const auto second_part = lanes_split.at(1);
			auto to_node_and_msg = StringUtils::split(second_part, ":");
			if (!to_node_and_msg.empty())
			{
				lane_names.emplace_back(StringUtils::trim_copy(to_node_and_msg.at(0)));
			}
		}
	}
	catch (const std::exception& e)
	{
		return lane_names;
	}

	return lane_names;
}

// private boolean isValid(String line) {
//     // it is not valid to have no 'from' Lane
//     if (line.startsWith(INTERACTION_TOKEN)) {
//         return false;
//     }
//
//     // only expect one instance of "->"
//     if (line.indexOf(INTERACTION_TOKEN) != line.lastIndexOf(INTERACTION_TOKEN)) {
//         return false;
//     }
//
//     // cannot have a message_ (:) without a toNode being named
//     if (line.contains(INTERACTION_MESSAGE_TOKEN) && !line.contains(INTERACTION_TOKEN)) {
//         return false;
//     }
//
//     // check that message_ token : is AFTER the toNode name
//     if (line.contains(INTERACTION_TOKEN) && line.contains(INTERACTION_MESSAGE_TOKEN)) {
//         if (line.split(INTERACTION_TOKEN)[1].trim().startsWith(INTERACTION_MESSAGE_TOKEN)) {
//             // first instance of : must be after the toNode name
//             return false;
//         }
//     }
//
//     return true;
// }
