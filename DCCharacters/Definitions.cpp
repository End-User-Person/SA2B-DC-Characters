#include "stdafx.h"


DataPointer(int, dword_1DB0BC0, 0x1DB0BC0);
DataPointer(int, dword_1DB0BC4, 0x1DB0BC4);
DataPointer(int, dword_1DB0BC8, 0x1DB0BC8);
DataPointer(int, dword_1DB0BCC, 0x1DB0BCC);
DataPointer(int, dword_1DB0BD0, 0x1DB0BD0);
DataPointer(int, dword_1DB0BD4, 0x1DB0BD4);
DataPointer(int, dword_1DB0BD8, 0x1DB0BD8);
DataPointer(int, dword_1DB0BDC, 0x1DB0BDC);
DataPointer(int, dword_1DB0BE0, 0x1DB0BE0);
DataPointer(int, dword_1A55834, 0x1A55834);
FunctionPointer(int, sub_5FA2B0, (), 0x5FA2B0);
char* eventModels_LoadAlt()
{
	signed int v0; // esi
	char* result; // eax

	pRenderInfo->CurrentTexlist = EventData.texlist;
	sub_5FA2B0();
	dword_1DB0BC0 = 0;
	dword_1DB0BC4 = 0;
	dword_1DB0BC8 = 0;
	dword_1DB0BCC = 0;
	dword_1DB0BD0 = 0;
	dword_1DB0BD4 = 0;
	dword_1DB0BD8 = 0;
	dword_1DB0BDC = 0;
	dword_1DB0BE0 = 0;
	dword_1A55834 = 0;
	//Theory: This loads Scene 0 assets
	for (v0 = 0; v0 < 5; v0++)
	{
		loadEventModels(0, v0, 0);
	}
	//This loads in the rest of the entities. The middle number is likely a layer order check
	loadEventModels(EventSceneNumber, 0, 0);
	result = loadEventUpgradeModels();
	loadEventModels(EventSceneNumber, 1, 0);
	loadEventModels(EventSceneNumber, 2, 0);
	loadEventModels(EventSceneNumber, 3, 0);
	loadEventModels(EventSceneNumber, 4, 0);
	nj_control_3d_flag_ |= 0x2400u;
	nj_control_3d_flag_ &= 0xFFFFDBFF;
	//This loads the reflection data
	pRenderInfo->CurrentTexlist = EventData.texlist;
	LoadEventReflections(0);
	LoadEventReflections(EventSceneNumber);
	return result;
}