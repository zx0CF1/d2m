
#include "main.h"

BOOL Globals::sleepy = FALSE;
BOOL Globals::cachefix = FALSE;

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved) 
{
	if(dwReason==DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hDll);

		if(GetModuleHandleA("Game.exe"))
		{
			LoadLibraryA("D2GFX.dll");
			InstallPatches();
		}
	}
	if (dwReason == DLL_PROCESS_DETACH)
		RemovePatches();

	return TRUE;
}

VOID WINAPI Install()
{
	sLine* Command;

	ParseCommandLine(GetCommandLineA());

	Command = GetCommand("-cachefix");
	if(Command)
		Globals::cachefix = TRUE;

	Command = GetCommand("-sleepy");
	if(Command)
		Globals::sleepy = TRUE;

	DefineOffsets();
	InstallPatches();

	Command = GetCommand("-mpq");
	if (Command)
	{
		D2_InitMPQ(Command->szText, 0, 0, 3000);
	}
}

DWORD WINAPI Unload(LPVOID lpParam)
{
	Sleep(100);
	FreeLibraryAndExitThread(GetModuleHandleA("D2Multi.dll"),0);
	return 0;
}

VOID WINAPI Shutdown()
{
	CreateThread(0,0,Unload,0,0,0);
}

