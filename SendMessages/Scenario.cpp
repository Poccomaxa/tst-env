#include "stdafx.h"
#include "Scenario.h"
#include "utils.h"

using namespace std;

void Scenario::step(double dt) {
	if (currentInstruction == instructions.end())
		return;
	if (currentInstruction->ready()) {
		currentInstruction->process();
		++currentInstruction;
	}
}

void CreateProcessCommand::process() {
	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess(toUnicode(processName).c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi) == TRUE) {
		lout << "process" << endl;
		lout << "handle " << pi.hProcess << endl;
	} else {
		DWORD er = GetLastError();
		lout << "Cannot create process: " << er << endl;		
	}
}