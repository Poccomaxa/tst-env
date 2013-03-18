#include "stdafx.h"
#include "utils.h"
#include "Processor.h"
#include "Parser.h"

using namespace std;

Processor Processor::instance;

void Processor::processTimer() {
		INPUT inp;
		inp.type = INPUT_KEYBOARD;
		KEYBDINPUT kbd;
		kbd.wVk = VK_SPACE;
		kbd.dwFlags = 0;
		kbd.time = 0;
		kbd.dwExtraInfo = 0;
		kbd.wScan = 0x39;
		inp.ki = kbd;
		SendInput(1, &inp, sizeof(INPUT));
}

void Processor::update(double dt) {
	if (curScenario && !curScenario->isCompleted())
		curScenario->step(dt);
}

void Processor::openScenario() {
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	WCHAR fileName[256] = L"";
	ofn.lStructSize = sizeof(ofn);
	ofn.hInstance = hInst;
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = L"Test scenario file (*.scn)\0*.scn\0All files (*.*)\0*.*\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = 256;	
	GetOpenFileName(&ofn);
	lout << fileName << endl;

	//TODO: Transfer to normal location
	
	ifstream infile(fileName);
	Parser parser;
	curScenario = parser.parse(infile);
	curScenario->reset();
}