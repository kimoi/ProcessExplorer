// ProcessUtils.cpp : Defines the exported functions for the DLL application.
//

#include "ProcessUtils.h"


dllexport BOOL GetThreadContextById(DWORD threadId, CONTEXT * context) {
	HANDLE hThread;

	hThread = OpenThread(THREAD_GET_CONTEXT, FALSE, threadId);

	if (hThread == NULL) {
		return FALSE;
	}

	GetThreadContext(hThread, context);

	CloseHandle(hThread);

	return TRUE;
}

dllexport BOOL IsWow64ProcessById(DWORD processId, BOOL * isWow64) {
	HANDLE hProcess;

	hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);

	if (hProcess == NULL) {
		return FALSE;
	}

	BOOL result = IsWow64Process(hProcess, isWow64);

	return !!result;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

