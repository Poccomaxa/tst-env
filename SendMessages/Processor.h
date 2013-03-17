#pragma once

#include <Windows.h>

class Processor {
	HWND hWnd;
	HINSTANCE hInst;

	static Processor instance;
	Processor(): sendSpaces(false) {}

	bool sendSpaces;
public:
	static Processor &get() { return instance; }

	void init(HWND hWnd, HINSTANCE hInst) { this->hWnd = hWnd; this->hInst = hInst; }

	void processTimer();
	void update(double dt);

	void openScenario();

	void setSendingSpaces(bool val) { sendSpaces = val; }
};