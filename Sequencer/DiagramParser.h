#pragma once

#include "Diagram.h"
#include "MetaDataParser.h"

class DiagramParser
{
public:
	static Diagram parse(const std::string& input);
};
