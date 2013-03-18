#pragma once

#include <Windows.h>
#include "utils.h"
#include "Scenario.h"

class Processor {
	HWND hWnd;
	HINSTANCE hInst;

	static Processor instance;

	Scenario *curScenario;

	Processor(): curScenario(NULL) {}

public:
	static Processor &get() { return instance; }

	void init(HWND hWnd, HINSTANCE hInst) { this->hWnd = hWnd; this->hInst = hInst; }

	void processTimer();
	void update(double dt);

	void openScenario();

	void ShowMessage(const std::string &message, const std::string &title = "") {
		
		MessageBox(hWnd, toUnicode(message).c_str(), toUnicode(title).c_str(), MB_OK);
	}
};