#pragma once

class Processor {
	static Processor instance;
	Processor(): sendSpaces(false) {}

	bool sendSpaces;
public:
	static Processor &get() { return instance; }

	void processTimer();

	void setSendingSpaces(bool val) { sendSpaces = val; }
};