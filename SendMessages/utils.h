#pragma once
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>

inline double SystemTime() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	__int64 uit;
	CopyMemory(&uit, &ft, sizeof(ULARGE_INTEGER));
	return 0.0000001 * uit;
}

inline std::ostream &operator<< (std::ostream &out, SYSTEMTIME const &st) {
	return out << "= Logger initialized: " << st.wDay << "." << st.wMonth << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond;
}

inline std::wstring toUnicode(std::string str) {
	WCHAR *buf = new WCHAR[str.size() + 1];
	MultiByteToWideChar(CP_ACP, NULL, str.c_str(), -1, buf, str.size() + 1);
	std::wstring wstr(buf);
	delete [] buf;
	return wstr;	
}

static class LoggedStream {
	std::ostringstream ss;
	template<typename T> void print(T& v) {
		ss << v;
		std::string strCont = ss.str();
		if (strCont.find_first_of("\n") != strCont.npos) {
			OutputDebugString(toUnicode(strCont).c_str());
			ss.str("");
		}
		out << v;
		out.flush();
	}

public:
	LoggedStream(): out("log.txt", std::ios::app) {
			
	}

	template<typename T> LoggedStream& operator<<(T& v) {
		print(v);
		//out << v;
		//out.flush();
		return *this;
	}

	LoggedStream& operator<<(std::ostream& (*v)(std::ostream&)) {
		print(v);
		//out << v;
		//out.flush();
		return *this;
	}

	void startMessage() {
		*this << "=====================================================" << std::endl;
		SYSTEMTIME st;
		GetLocalTime(&st);
		*this << st << std::endl;	
		*this << "=====================================================" << std::endl;	
	}
	
protected:
	std::ofstream out;
} lout;