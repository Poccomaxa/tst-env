#pragma once
#include <vector>

class Command {
public:
	virtual void process() = 0;
};

class Trigger {
public:
	virtual bool ready() = 0;
};

class Check {
public:
	virtual bool check() = 0;
};

class Instruction {
	Command *_command;
	Trigger *_trigger;
	Check *_check;
public:
	bool ready() { return _trigger->ready(); }
	bool check() { return _check->check(); }
	void process() { _command->process(); }
};

class Scenario {
	std::vector<Instruction> instructions;
};