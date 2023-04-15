#include "stdafx.h"

Log pLog;

HRESULT Log::Initialize() {
	ClearLog();

	LOG_PRINT("[Log] Log allocated");
	LOG_PRINT("[Service] Class version 1.0");

	return S_OK;
}

void Log::ClearLog() {
	remove(LOG_PATH);
}

void Log::LogToFile(const char* message) {
	FILE* f = fopen(LOG_PATH, "a+");
	if (f) {
		fprintf(f, message);
		fclose(f);
	}
}

const char* Log::GetTimeAsString() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	auto str = asctime(timeinfo);
	auto n = strlen(str) - 1;

	if (n < 0)
		n = 0;

	str[n] = '\0';

	static char buffer[50];
	sprintf_s(buffer, "[%s]", str);
	return buffer;
}

void Log::Message(const char* type, const char* fmt, ...) {
	if (xbLive.bExternUnload || xbLive.bTerminateProcess) return;

	char buffer[0x100] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	RtlVsnprintf(buffer, 0x100, fmt, va_alist);
	va_end(va_alist);

	char buffer2[0x200] = { 0 };
	sprintf_s(buffer2, "%s %s %s\n", GetTimeAsString(), type, buffer);

	LogToFile(buffer2);

	DbgPrint(buffer2);
}