#include "stdafx.h"
#include "Processor.h"

Processor Processor::instance;

void Processor::processTimer() {
	if (sendSpaces) {
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
}