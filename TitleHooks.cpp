#include "stdafx.h"

Title pTitle;

DWORD WINAPI Plugin_Menu_Load() {
	/*initialize Game Mod content here*/

	return ERROR_SUCCESS;
}

bool Title::ApplyHooks() {
	if (!bInitialized) {

		pUtils.MakeThread(reinterpret_cast<LPTHREAD_START_ROUTINE>(Plugin_Menu_Load));
		LOG_DEV("Applied detours!");
		bInitialized = true;
		return true;
	}
	else {
		LOG_DEV("TitleHooks already initialized!");
	}

	return false;
}

void Title::Remove(bool bOverride) {
	if (bInitialized || bOverride) {
		pHooking.UnhookAll();

		Sleep(1000);

		LOG_DEV("Removed detours!");
		bInitialized = false;
	}
	else {
		LOG_DEV("TitleHooks have not been initialized!");
	}
}
