#pragma once
#include "ScenarioFactories.h"

class Parser {
	TriggerFactory tf;
	CommandFactory cf;
	int curLine;
	Scenario *formErrorMessage(const std::string &er);
public:
	Scenario *parse(std::istream &input);
};