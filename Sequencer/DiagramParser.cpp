#include "DiagramParser.h"
#include "Interaction.h"
#include "InteractionParser.h"
#include "Participant.h"
#include "ParticipantsParser.h"

Diagram DiagramParser::parse(const std::string& input)
{
	const MetaData meta_data = MetaDataParser::parse(input);
	const std::list<Participant> participants = ParticipantsParser::parse(input);
	const std::list<Interaction> interactions = InteractionParser::parse(participants, input);

	return Diagram(meta_data, participants, interactions);
}
