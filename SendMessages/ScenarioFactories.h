#pragma once
#include "Scenario.h"

//========= Triggers

class AbstractTriggerCreator {
public:
	virtual Trigger *factoryMethod(std::vector<std::string> args) = 0;
};

class ConstantTriggerCreator: public AbstractTriggerCreator {
public:
	virtual Trigger *factoryMethod(std::vector<std::string> args);
};

class TriggerFactory {
	std::map<std::string, AbstractTriggerCreator *> creators;
public:
	Trigger *createTrigger(std::vector<std::string> args);
	TriggerFactory();
};

//========= Commands

class AbstractCommandCreator {
public:
	virtual Command *factoryMethod(std::vector<std::string> args) = 0;
};

class CreateProcessCommandCreator: public AbstractCommandCreator {
public:
	virtual Command *factoryMethod(std::vector<std::string> args);
};

class CommandFactory {
	std::map<std::string, AbstractCommandCreator *> creators;
public:
	CommandFactory();
	Command *createCommand(std::vector<std::string> args);
};