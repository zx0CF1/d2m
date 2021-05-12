#pragma once

#include "Offset.h"
#include "D2Intercepts.h"

PatchHook pHooks[] = {
	{PatchCall, GetDllOffset("D2Gfx.DLL",0x85B7), (DWORD)Multi ,6},
	{PatchCall ,GetDllOffset("D2Gfx.DLL",0x87E8), (DWORD)Windowname ,6},
	{PatchJmp, GetDllOffset("D2Launch.dll",0x18153), (DWORD)InitMainMenu,5},
};
