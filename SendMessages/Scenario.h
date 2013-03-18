#pragma once
#include <vector>
#include <map>

class Command {
public:
	virtual void process() = 0;
};

class Trigger {
public:
	virtual void reached() {}
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
	Instruction(Trigger *trigger, Command *command): _command(command), _trigger(trigger) {}
};

class Scenario {
	std::vector<Instruction> instructions;
	std::vector<Instruction>::iterator currentInstruction;
public:
	void addInstruction(Instruction &instr) { instructions.push_back(instr); }
	Scenario() { currentInstruction = instructions.begin(); }
	bool isCompleted() { return currentInstruction == instructions.end(); }
	void step(double dt);
	void reset() { currentInstruction = instructions.begin(); }
};

//====== Actual Triggers

class ConstantTrigger: public Trigger {
	bool val;
public:
	virtual bool ready() { return val; }
	ConstantTrigger(): val(true) {}
	ConstantTrigger(bool val): val(val) {}
};

class WaitTrigger: public Trigger {
	unsigned long time;
public:
	virtual bool ready() { return true; }
};

//====== Actual commands

class CreateProcessCommand: public Command {
	std::string processName;
	bool console;
public:
	virtual void process();
	CreateProcessCommand(std::string processName, bool console): processName(processName), console(console) {}
};