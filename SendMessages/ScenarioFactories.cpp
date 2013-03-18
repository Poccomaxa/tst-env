#include "stdafx.h"
#include "ScenarioFactories.h"
#include "utils.h"

using namespace std;

TriggerFactory::TriggerFactory() {
	creators["true"] = new ConstantTriggerCreator();
	creators[""] = creators["true"];
	creators["false"] = creators["true"];
}

Trigger *ConstantTriggerCreator::factoryMethod(std::vector<std::string> args) {
	if (args[0] == "")
		return new ConstantTrigger();
	else if (args[0] == "true")
		return new ConstantTrigger(true);
	else if (args[0] == "false")
		return new ConstantTrigger(false);
}

Trigger *TriggerFactory::createTrigger(std::vector<std::string> args) {
	auto it = creators.find(args[0]);
	if (it != creators.end())
		return creators[args[0]]->factoryMethod(args);
	else {
		lout << "Unknown trigger: " << args[0] << std::endl;
		return NULL;
	}
}

CommandFactory::CommandFactory() {
	creators["create_process"] = new CreateProcessCommandCreator();
}

Command *CommandFactory::createCommand(std::vector<std::string> args) {
	auto it = creators.find(args[0]);
	if (it != creators.end())
		return creators[args[0]]->factoryMethod(args);
	else {
		lout << "Unknown command: " << args[0] << std::endl;
		return NULL;
	}
}

Command *CreateProcessCommandCreator::factoryMethod(std::vector<std::string> args) {
	args.erase(args.begin(), args.begin() + 1);
	if (args.empty()) {
		lout << "Create process: process name should be first argument. " << endl;
		return NULL;
	}
	string app = args[0];
	args.erase(args.begin(), args.begin() + 1);
	bool console = false;
	for (auto it = args.begin(); it != args.end(); ++it) {
		if (*it == "console")
			console = true;	
	}

	return new CreateProcessCommand(app, true);
}