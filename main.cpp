
#include "main.h"

BOOL Globals::sleepy = FALSE;
BOOL Globals::cachefix = FALSE;
//BOOL Globals::rdblock = FALSE;
BOOL Globals::ftjReduce = FALSE;

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID lpReserved) 
{
	if(dwReason==DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hDll);
		LoadLibraryA("D2Client.dll");
		LoadLibraryA("Bnclient.dll");
		LoadLibraryA("kernel32.dll");
		LoadLibraryA("PD2_EXT.dll");
		//LoadLibraryA("ProjectDiablo.dll");
		LoadLibraryA("D2Net.dll");
		LoadLibraryA("Fog.DLL");
		LoadLibraryA("user32.dll");
		LoadLibraryA("D2GFX.dll");
		LoadLibraryA("D2WIN.dll");
		Install();
	}
	if (dwReason == DLL_PROCESS_DETACH)
		RemovePatches();

	return TRUE;
}

VOID WINAPI Install()
{
	sLine *Command;

	

	ParseCommandLine(GetCommandLineA());

	Command = GetCommand("-ftj");
	if(Command)
		Globals::ftjReduce = TRUE;

	/*Command = GetCommand("-rd");
	if(Command)
		Globals::rdblock = TRUE;*/

	Command = GetCommand("-cachefix");
	if(Command)
		Globals::cachefix = TRUE;

	Command = GetCommand("-sleepy");
	if(Command)
		Globals::sleepy = TRUE;

	DefineOffsets();
	InstallPatches();
}

DWORD WINAPI Unload(LPVOID lpParam)
{
	Sleep(100);
	FreeLibraryAndExitThread(GetModuleHandleA("D2M.dll"),0);
	return 0;
}

VOID WINAPI Shutdown()
{
	if (!Globals::cachefix && !Globals::sleepy)
		CreateThread(0,0,Unload,0,0,0);
}

