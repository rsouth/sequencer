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
#include "DiagramParser.h"
#include "Interaction.h"
#include "InteractionParser.h"
#include "Participant.h"
#include "ParticipantsParser.h"
#include "StringUtils.h"

Diagram DiagramParser::parse(const std::string& input)
{
  // sanitise the input
  auto lines = StringUtils::split(input, "\n");
  std::vector<std::string> filtered_input;
  for (const std::string& line : lines) {
    if (StringUtils::starts_with(line, "#")) { continue; }

    filtered_input.push_back(line);
  }

  const MetaData meta_data = MetaDataParser::parse(filtered_input);
  const std::list<Participant> participants = ParticipantsParser::parse(filtered_input);
  const std::list<Interaction> interactions = InteractionParser::parse(participants, filtered_input);

  return Diagram(meta_data, participants, interactions);
}
