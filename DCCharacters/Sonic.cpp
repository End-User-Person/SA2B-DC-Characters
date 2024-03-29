#include "stdafx.h"
#include "DCCharacters.h"
#include "Sonic.h"

static FunctionHook<void, ObjectMaster*>Sonic_Display_t(Sonic_Display);
static FunctionHook<void, ObjectMaster*>Sonic_DispDelay1_t(Sonic_DispDelay1);
static FunctionHook<void, ObjectMaster*>Super_Display_t(Super_Display);
static FunctionHook<void, NJS_OBJECT*>SonicDrawCallBack_t(SonicDrawCallBack);
static FunctionHook<void, NJS_OBJECT*>SuperDrawCallBack_t(SuperSonicDrawCallBack);
static FunctionHook<void, ObjectMaster*>Super_DispDelay3_t(Super_DispDelay3);

void SonicDrawCallBack_r(NJS_OBJECT* obj)
{
	SonicDrawCallBack_t.Original(obj);
	NJS_OBJECT* lod1 = CharacterModels[37].Model->child->sibling->sibling;
	NJS_OBJECT* lod2 = CharacterModels[54].Model->child->sibling->sibling;
	if (obj == CharacterModels[21].Model || obj == lod1 || obj == lod2)
		setGenericMatrix(SonicHeadMatrix);
	return;
}

void SuperDrawCallBack_r(NJS_OBJECT* obj)
{
	SuperDrawCallBack_t.Original(obj);
	if (obj == CharacterModels[21].Model || obj == CharacterModels[349].Model)
		setGenericMatrix(SuperHeadMatrix);
	return;
}

void DisplayPSOSonicEarpiece(EntityData1* data, SonicCharObj2* sco2)
{
	njSetTexture(sco2->TextureList);
	njPushMatrixEx();
	if (sco2->base.CharID2 == Characters_Sonic && AltCostume[sco2->base.PlayerNum] == 1)
	{
		memcpy(_nj_current_matrix_ptr_, &SonicHeadMatrix, 0x30u);
		DrawObject(headset->getmodel());
	}
	njPopMatrixEx();
}

void DisplayHSonicMask(EntityData1* data, SonicCharObj2* sco2)
{
	njSetTexture(sco2->TextureList);
	njPushMatrixEx();
	if (sco2->base.CharID2 == Characters_Sonic && AltCostume[sco2->base.PlayerNum] != 1)
	{
		memcpy(_nj_current_matrix_ptr_, &SonicHeadMatrix, 0x30u);
		DrawObject(hmask->getmodel());
	}
	njPopMatrixEx();
}

void DisplayPSOSuperEarpiece(EntityData1* data, SuperSonicCharObj2* ssco2)
{
	njSetTexture(ssco2->TextureList);
	njPushMatrixEx();
	if (ssco2->base.CharID2 == Characters_SuperSonic)
	{
		memcpy(_nj_current_matrix_ptr_, &SuperHeadMatrix, 0x30u);
		DrawObject(headset->getmodel());
	}
	njPopMatrixEx();
}

void DisplayHSuperMask(EntityData1* data, SuperSonicCharObj2* ssco2)
{
	njSetTexture(ssco2->TextureList);
	njPushMatrixEx();
	if (ssco2->base.CharID2 == Characters_SuperSonic)
	{
		memcpy(_nj_current_matrix_ptr_, &SuperHeadMatrix, 0x30u);
		DrawObject(superpart->getmodel());
	}
	njPopMatrixEx();
}

void SetSonicAccessoryParams(ObjectMaster* obj)
{
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char pnum = sco2->base.PlayerNum;
	char light = LightIndex[&pnum];
	bool screen;

	if (light != 1 && light != 5)
	{
		nj_control_3d_flag_ |= 0x2400u;
	}
	switch (byte_174AFFD)
	{
	case 1:
		screen = CurrentScreen == 0;
		break;
	case 2:
		screen = CurrentScreen == 1;
		break;
	case 3:
		light = byte_1DE4660;
		break;
	default:
		setGenericGCLight(byte_174AFFD, pnum);
		break;
	}
	memcpy(SpeedTypeMasterMatrix, _nj_current_matrix_ptr_, 0x30u);
	sub_427040(SpeedTypeMasterMatrix, _nj_current_matrix_ptr_);
	GenericModelCallBack = SonicDrawCallBack;
	if (data->Timer & 2 && !Pose2PStart_PlayerNum)
	{
		nj_control_3d_flag_ &= 0xFFFFDBFF;
		nj_constant_attr_or_ = _constant_attr_or_;
		GenericModelCallBack = 0;
		nj_constant_attr_and_ = _constant_attr_and_;
		setGenericLight(LightIndexBackupMaybe);
	}
}

void SetSuperSonicAccessoryParams(ObjectMaster* obj)
{
	SuperSonicCharObj2* ssco2 = (SuperSonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char pnum = ssco2->base.PlayerNum;
	char light = LightIndex[&pnum];

	_constant_attr_or_ = nj_constant_attr_or_;
	nj_constant_attr_or_ &= 0xFFFFFDFF;
	_constant_attr_and_ = nj_constant_attr_and_;
	if (light != 1 && light != 5)
	{
		nj_control_3d_flag_ |= 0x2400u;
	}
	setGenericGCLight(light, pnum);
	memcpy(SuperMasterMatrix, _nj_current_matrix_ptr_, 0x30u);
	sub_427040(SuperMasterMatrix, _nj_current_matrix_ptr_);
	GenericModelCallBack = SuperSonicDrawCallBack;
}

void __cdecl Sonic_Display_PSO(ObjectMaster* obj)
{
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char character = sco2->base.CharID2;
	int anim = sco2->base.AnimInfo.Current;
	char pnum = sco2->base.PlayerNum;
	if (character != Characters_Sonic && AltCostume[sco2->base.PlayerNum] != 1)
		return Sonic_Display_t.Original(obj);
	else
	{
		Sonic_Display_t.Original(obj);
		if (byte_174AFE2 || byte_174AFE0 != 1 || CurrentScreen == pnum || !sub_7983F0(&data->Position, 50.0)
			&& (!Pose2PStart_PlayerNum || Pose2PStart_PlayerNum == pnum + 1))
		{
			SetSonicAccessoryParams(obj);

			if (anim != 30 && !(data->Status & Status_Ball && sco2->gap35E[2] & 0x11))
			{
				njPushMatrixEx();
				DisplayPSOSonicEarpiece(data, sco2);
				njPopMatrixEx();
			}
		}
	}
}

void __cdecl Sonic_DispDelay1_H(ObjectMaster* obj)
{
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char character = sco2->base.CharID2;
	int anim = sco2->base.AnimInfo.Current;
	char pnum = sco2->base.PlayerNum;
	if (character != Characters_Sonic)
		return Sonic_DispDelay1_t.Original(obj);
	else
	{
		if (byte_174AFE2 || byte_174AFE0 != 1 || CurrentScreen == pnum || !sub_7983F0(&data->Position, 50.0)
			&& (!Pose2PStart_PlayerNum || Pose2PStart_PlayerNum == pnum + 1))
		{
			SetSonicAccessoryParams(obj);

			if (anim != 30 && !(data->Status & Status_Ball && sco2->gap35E[2] & 0x11))
			{
				njPushMatrixEx();
				DisplayHSonicMask(data, sco2);
				njPopMatrixEx();
			}
		}
		Sonic_DispDelay1_t.Original(obj);
	}
}

DataPointer(char, byte_174B002, 0x0174B002);
DataPointer(LastBoss2Data2*, FinalHazardPlayerData, 0x1A5A428);
void __cdecl Super_Display_PSO(ObjectMaster* obj)
{
	SuperSonicCharObj2* ssco2 = (SuperSonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char character = ssco2->base.CharID2;
	int anim = ssco2->base.AnimInfo.Current;
	char pnum = ssco2->base.PlayerNum;
	char light = LightIndex[&pnum];
	if (character != Characters_SuperSonic)
		return Super_Display_t.Original(obj);
	else
	{
		Super_Display_t.Original(obj);
		if (FinalHazardPlayerData->field_0 != ssco2->base.PlayerNum && byte_174B002 != 1)
		{
			return;
		}

		SetSuperSonicAccessoryParams(obj);

		njPushMatrixEx();
		DisplayPSOSuperEarpiece(data, ssco2);
		njPopMatrixEx();
	}
}

void __cdecl Super_DispDelay3_H(ObjectMaster* obj)
{
	SuperSonicCharObj2* ssco2 = (SuperSonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	char character = ssco2->base.CharID2;
	int anim = ssco2->base.AnimInfo.Current;
	char pnum = ssco2->base.PlayerNum;
	char light = LightIndex[&pnum];
	if (character != Characters_SuperSonic)
		return Super_DispDelay3_t.Original(obj);
	else
	{
		if (FinalHazardPlayerData->field_0 != ssco2->base.PlayerNum && byte_174B002 != 1)
		{
			return;
		}
		SetSuperSonicAccessoryParams(obj);

		njPushMatrixEx();
		DisplayHSuperMask(data, ssco2);
		njPopMatrixEx();
		nj_control_3d_flag_ &= 0xFFFFDBFF;
		nj_constant_attr_or_ = _constant_attr_or_;
		GenericModelCallBack = 0;
		nj_constant_attr_and_ = _constant_attr_and_;
		setGenericLight(LightIndexBackupMaybe);
		Super_DispDelay3_t.Original(obj);
	}
}

void Init_Sonic()
{
	WriteData((StartPosition**)0x43D939, SonicDCStartingArray);
	WriteData((StartPosition**)0x43DF74, SonicDCEndingArray);
}

void Init_SonicMDL(const char* name, const char* supername)
{
	WriteData((const char**)0x716F70, name);
	WriteData((const char**)0x49AA83, supername);
}

void Init_SonicAltMDL(const char* name)
{
	WriteData((const char**)0x716F50, name);
}

void Init_Trial()
{
	WriteData((StartPosition**)0x43D939, SonicDCStartingArray);
	WriteData((StartPosition**)0x43DF74, SonicDCEndingArray);
	WriteData((AnimationInfo**)0x716F0A, TrialSonicAnimListEdits);
}

void Init_PSOP1(ModelInfo* info, ModelInfo* superinfo)
{
	headset = info;
	superpart = superinfo;
	SonicDrawCallBack_t.Hook(SonicDrawCallBack_r);
	SuperDrawCallBack_t.Hook(SuperDrawCallBack_r);
	Sonic_Display_t.Hook(Sonic_Display_PSO);
	Super_Display_t.Hook(Super_Display_PSO);
}

void Init_PSOAlt(ModelInfo* info)
{
	headset = info;
	SonicDrawCallBack_t.Hook(SonicDrawCallBack_r);
	Sonic_Display_t.Hook(Sonic_Display_PSO);
}

void Init_HSonic(ModelInfo* info, ModelInfo* superinfo)
{
	hmask = info;
	superpart = superinfo;
	SuperDrawCallBack_t.Hook(SuperDrawCallBack_r);
	Sonic_DispDelay1_t.Hook(Sonic_DispDelay1_H);
	Super_DispDelay3_t.Hook(Super_DispDelay3_H);
}

//Start Position
StartPosition SonicDCStartingArray[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_GreenForest, 0x4000, 0x4000, 0x4000, { 1.61f, 40, -416 }, { 15, 40, -416 }, { -15, 40, -416 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -9.5f, 800, -526.1438f }, { -9.5f, 800, -526.1438f }, { 8.7f, 800, -526.1438f } },
	{ LevelIDs_MetalHarbor, 0xC000, 0xC000, 0xC000, { 0, 500, 40 }, { 10, 500, 45 }, { -10, 500, 45 } },
	{ LevelIDs_MetalHarbor2P, 0xC000, 0xC000, 0xC000, { 0, 500, 40 }, { -10, 500, 45 }, { 10, 500, 45 } },
	{ LevelIDs_CityEscape, 0x4000, 0x4000, 0x4000, { 0, 300, 340 }, { 10, 300, 340 }, { -10, 300, 340 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0x4000, 0x4000, { 0, -85, -45 }, { 10, -85, -45 }, { -10, -85, -45 } },
	{ LevelIDs_RadicalHighway, 0xC000, 0xC000, 0xC000, { 103, 182, -39 }, { 103, 182, -39 }, { -103, 182, -39 } },
	{ LevelIDs_SonicVsShadow1, 0, 0, 0, { -60, 64, 0 }, { -60, 64, 0 }, { -60, 64, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000, 0xC000, 0xC000, { 0, 180, 340 }, { 20, 180, 340 }, { -20, 180, 340 } },
	{ LevelIDs_PyramidCave, 0xC000, 0xC000, 0xC000, { 0, 300, 0 }, { 0, 300, 0 }, { 0, 300, 0 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, 0 }, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_FinalChase, 0, 0x4000, 0x4000, { -223, -100, 63 }, { 3206, -4000, 2455 }, { 3176, -4000, 2455 } },
	{ LevelIDs_CannonsCoreS, 0xC000, 0xC000, 0xC000, { 0, 45, 0 }, { 0, 45, 0 }, { 0, 45, 0 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 210 }, { 0, 200, 210 }, { 0, 200, 210 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_SonicVsShadow2, 0, 0, 0, { 0, 0, -15 }, { 0, 0, -15 }, { 0, 0, -15 } },
	{ LevelIDs_GreenHill, 0xC000, 0xC000, 0xC000, { 0, 40, 0 }, { 15, 40, 0 }, { -15, 40, 0 } },
	{ LevelIDs_DowntownRace, 0x4000, 0x4000, 0x4000, { -2215, 4320, -4670 }, { -2235, 4320, -4670 }, { -2195, 4320, -4670 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 10, -445, -900 }, { 10, -795, -900 }, { -10, -795, -900 } },
	{ LevelIDs_Invalid }
};

//End Position
StartPosition SonicDCEndingArray[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_GreenForest, 0x8000, 0x8000, 0x8000, { 10935, -1854, 11056 }, { 10935, -1854, 11076 }, { 10935, -1854, 11066 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -1343.7f, -4928, 10098 }, { -1333.7f, -4928, 10098 }, { -1353.7f, -4928, 10098 } },
	{ LevelIDs_MetalHarbor, 0, 0, 0, { 8854, -170, -10261 }, { 8854, -170, -10241 }, { 8854, -170, -10281 } },
	{ LevelIDs_CityEscape, 0x4000, 0x4000, 0x4000, { 3955, -22175, 16130 }, { 3955, -22175, 16130 }, { 3955, -22175, 16100 } },
	{ LevelIDs_RadicalHighway, 0xC000, 0xC000, 0xC000, { -9970, -6999, -18430 }, { -9970, -6999, -18430 }, { -9970, -6999, -18400 } },
	{ LevelIDs_SonicVsShadow1, 0x800, 0x800, 0x800, { -10, -42, 0 }, { -10, -42, 0 }, { -10, -42, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000, 0xC000, 0xC000, { -8470, -1097, -2904 }, { -8470, -1097, -2904 }, { -8470, -1097, -2904 } },
	{ LevelIDs_PyramidCave, 0x4000, 0x4000, 0x4000, { 940, -4060, -22190 }, { 940, -4060, -22190 }, { 940, -4060, -22190 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { 2530, -26495.5f, 7465 }, { 2530, -26495.5f, 7465 }, { 2530, -26495.5f, 7465 } },
	{ LevelIDs_BigFoot, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 220 }, { 0, 200, 220 }, { 0, 200, 220 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_CannonsCoreS, 0x1000, 0x1000, 0x1000, { -1600, -5755, -9565 }, { -308, 0, 0 }, { -308, 0, 0 } },
	{ LevelIDs_SonicVsShadow2, 0x4000, 0x4000, 0x4000, { -308, 0, 0 }, { -308, 0, 0 }, { -308, 0, 0 } },
	{ LevelIDs_GreenHill, 0xC000, 0xC000, 0xC000, { -1970, -1390, -6940 }, { -1970, -1390, -6940 }, { -1970, -1390, -6910 } },
	{ LevelIDs_DowntownRace, 0xC000, 0xC000, 0xC000, { -1540, -6060, 8800 }, { -1540, -6060, 8800 }, { -1540, -6060, 8770 } },
	{ LevelIDs_GrindRace, 0x8000, 0x8000, 0x8000, { 13990, -35280, 10050 }, { 13990, -35280, 10050 }, { 13990, -35280, 10050 } },
	{ LevelIDs_MetalHarbor2P, 0, 0x8000, 0x8000, { 8854, -31, -10370 }, { 4913, -31, -10370 }, { 4913, -31, -10370 } },
	{ LevelIDs_FinalChase, 0, 0, 0, { 122, -9960, 7627 }, { 122, -9960, 7627 }, { 122, -9960, 7627 } },
	{ LevelIDs_WhiteJungle, 0xC000, 0xC000, 0xC000, { 13166, -3599, -5518 }, { 13156, -3599, -5518 }, { 13176, -3599, -5518 } },
	{ LevelIDs_Invalid }
};

//Trial Sonic Animation List
AnimationInfo TrialSonicAnimListEdits[] = {
	{ 0, 0, 3, 0, 0.0625f, 0.1f },
	{ 1, 0, 3, 1, 0.25f, 0.1f },
	{ 2, 0, 3, 2, 0.25f, 0.1f },
	{ 3, 0, 4, 0, 0.25f, 1 },
	{ 4, 0, 3, 4, 0.03125f, 0.1f },
	{ 5, 0, 3, 5, 0.03125f, 0.1f },
	{ 6, 0, 11, 6, 0.25f, 3.4f },
	{ 7, 0, 11, 7, 0.25f, 1.4f },
	{ 8, 0, 11, 8, 0.25f, 0.8f },
	{ 9, 0, 11, 9, 0.25f, 0.6f },
	{ 10, 0, 10, 10, 0.5f, 0.4f },
	{ 11, 0, 11, 11, 0.25f, 0.2f },
	{ 12, 0, 10, 12, 0.25f, 0.7f },
	{ 13, 0, 3, 13, 0.25f, 0.4f },
	{ 14, 0, 4, 15, 0.125f, 0.3f },
	{ 15, 0, 3, 15, 0.125f, 0.4f },
	{ 16, 0, 4, 0, 1, 0.2f },
	{ 17, 0, 4, 0, 1, 0.4f },
	{ 18, 0, 9, 0, 0.25f, 0.3f },
	{ 19, 0, 4, 20, 0.125f, 0.2f },
	{ 20, 0, 3, 20, 0.25f, 0.6f },
	{ 21, 0, 6, 21, 1, 0.1f },
	{ 22, 0, 4, 0, 1, 1 },
	{ 23, 0, 3, 23, 0.0625f, 1 },
	{ 24, 0, 4, 25, 0.5f, 0.4f },
	{ 25, 0, 4, 0, 0.0625f, 0.3f },
	{ 26, 0, 4, 1, 0.0625f, 1 },
	{ 27, 0, 4, 0, 1, 0.5f },
	{ 28, 0, 3, 28, 0.0625f, 0.2f },
	{ 29, 0, 3, 29, 0.0625f, 0.2f },
	{ 30, 6, 3, 30, 0.5f, 1 },
	{ 31, 0, 9, 35, 0.125f, 0.2f },
	{ 32, 0, 11, 32, 0.5f, 0.4f },
	{ 33, 0, 6, 33, 0.25f, 0.2f },
	{ 34, 0, 4, 35, 0.5f, 1 },
	{ 35, 0, 3, 35, 0.125f, 0.1f },
	{ 36, 0, 3, 36, 0.03125f, 0.1f },
	{ 37, 0, 3, 37, 0.03125f, 0.1f },
	{ 38, 0, 11, 38, 0.5f, 0.5f },
	{ 39, 0, 4, 6, 0.5f, 0.5f },
	{ 40, 0, 3, 40, 0.5f, 0.6f },
	{ 41, 0, 3, 41, 0.5f, 0.4f },
	{ 42, 0, 3, 42, 0.125f, 0.3f },
	{ 43, 0, 4, 44, 0.5f, 0.2f },
	{ 44, 0, 3, 44, 0.5f, 0.1f },
	{ 45, 0, 3, 45, 0.5f, 0.1f },
	{ 46, 0, 4, 47, 0.5f, 0.1f },
	{ 47, 0, 3, 47, 0.5f, 0.3f },
	{ 48, 0, 4, 35, 1, 0.04f },
	{ 49, 0, 4, 0, 0.5f, 0.3f },
	{ 50, 0, 4, 0, 0.5f, 0.3f },
	{ 51, 0, 4, 15, 0.5f, 0.3f },
	{ 52, 0, 4, 15, 0.5f, 0.3f },
	{ 53, 0, 7, 0, 1, 0.2f },
	{ 54, 0, 6, 54, 1, 0.5f },
	{ 55, 0, 3, 55, 0.125f, 0.3f },
	{ 56, 0, 4, 15, 1, 0.25f },
	{ 57, 0, 4, 58, 0.125f, 0.1f },
	{ 58, 0, 3, 58, 1, 0.1f },
	{ 59, 0, 6, 59, 1, 0.2f },
	{ 60, 0, 6, 60, 0.25f, 1 },
	{ 61, 0, 3, 61, 0.25f, 0.5f },
	{ 62, 0, 6, 62, 0.25f, 0.1f },
	{ 63, 0, 4, 0, 0.25f, 0.3f },
	{ 64, 0, 4, 0, 0.25f, 0.3f },
	{ 65, 0, 4, 66, 0.25f, 1.4f },
	{ 66, 0, 3, 66, 0.25f, 1 },
	{ 67, 0, 4, 68, 0.125f, 0.4f },
	{ 68, 0, 3, 68, 0.125f, 0.4f },
	{ 69, 0, 4, 70, 0.25f, 0.1f },
	{ 70, 0, 3, 70, 1, 0.2f },
	{ 71, 0, 9, 0, 0.125f, 0.2f },
	{ 72, 0, 6, 72, 0.25f, 0.2f },
	{ 73, 0, 4, 0, 0.25f, 0.3f },
	{ 74, 0, 3, 74, 0.25f, 0.4f },
	{ 75, 0, 3, 75, 0.25f, 0.1f },
	{ 76, 0, 6, 76, 0.25f, 0.3f },
	{ 77, 0, 3, 77, 0.25f, 0.8f },
	{ 78, 0, 3, 78, 0.125f, 0.2f },
	{ 79, 0, 9, 35, 0.25f, 0.5f },
	{ 80, 0, 5, 81, 0.25f, 0.5f },
	{ 81, 0, 4, 0, 0.25f, 0.5f },
	{ 82, 0, 9, 0, 0.25f, 0.5f },
	{ 83, 0, 4, 0, 0.0625f, 0.15f },
	{ 84, 0, 4, 0, 0.0625f, 0.15f },
	{ 85, 0, 6, 85, 0.25f, 0.5f },
	{ 86, 0, 3, 86, 1, 0.2f },
	{ 87, 0, 3, 87, 1, 0.5f },
	{ 88, 0, 3, 88, 0.03125f, 0.15f },
	{ 89, 0, 3, 89, 0.03125f, 0.1f },
	{ 90, 0, 9, 0, 0.03125f, 0.25f },
	{ 91, 0, 4, 92, 0.25f, 1 },
	{ 92, 0, 4, 93, 0.25f, 1 },
	{ 93, 0, 4, 16, 0.25f, 0.2f },
	{ 94, 0, 9, 0, 0.25f, 0.3f },
	{ 95, 0, 9, 0, 0.25f, 0.3f },
	{ 96, 0, 4, 97, 0.25f, 1 },
	{ 97, 0, 4, 98, 0.25f, 1 },
	{ 98, 0, 4, 99, 0.25f, 0.2f },
	{ 99, 0, 4, 16, 0.25f, 1 },
	{ 66, 0, 3, 100, 1, 3 },
	{ 101, 0, 6, 67, 0.25f, 0.3f },
	{ 102, 0, 6, 67, 0.25f, 0.3f },
	{ 103, 0, 6, 67, 0.25f, 0.3f },
	{ 104, 0, 13, 104, 0.25f, 0.3f },
	{ 105, 0, 13, 105, 0.25f, 0.3f },
	{ 106, 0, 13, 106, 0.25f, 0.3f },
	{ 107, 0, 13, 107, 0.25f, 0.3f },
	{ 108, 0, 13, 108, 0.25f, 0.3f },
	{ 109, 0, 13, 109, 0.25f, 0.3f },
	{ 110, 0, 13, 110, 0.25f, 0.3f },
	{ 111, 0, 13, 111, 0.25f, 0.3f },
	{ 112, 0, 3, 112, 0.25f, 0.3f },
	{ 113, 0, 3, 113, 0.25f, 0.3f },
	{ 114, 0, 9, 15, 0.0625f, 0.2f },
	{ 115, 0, 4, 15, 0.0625f, 0.35f },
	{ 116, 0, 4, 15, 0.0625f, 0.35f },
	{ 117, 0, 4, 15, 0.125f, 1 },
	{ 118, 0, 6, 118, 1, 1 },
	{ 119, 0, 6, 119, 1, 1 },
	{ 120, 0, 3, 120, 1, 0.1f },
	{ 121, 0, 13, 121, 0.25f, 0.3f },
	{ 122, 0, 13, 122, 0.25f, 0.3f },
	{ 123, 0, 13, 123, 0.25f, 0.3f },
	{ 124, 0, 13, 124, 0.25f, 0.3f },
	{ 125, 0, 3, 125, 0.25f, 0.3f },
	{ 126, 0, 3, 126, 0.25f, 0.3f },
	{ 127, 0, 6, 127, 0.25f, 0.4f },
	{ 128, 0, 4, 129, 0.125f, 0.3f },
	{ 129, 0, 3, 129, 0.125f, 0.4f },
	{ 130, 0, 4, 121, 1, 0.3f },
	{ 132, 0, 4, 121, 0.25f, 0.3f },
	{ 131, 0, 4, 122, 0.25f, 0.3f },
	{ 133, 0, 4, 130, 1, 1 },
	{ 134, 0, 4, 130, 1, 1 },
	{ 135, 0, 4, 130, 0.0625f, 1.25f },
	{ 136, 0, 4, 130, 0.0625f, 1 },
	{ 137, 0, 4, 130, 1, 1 },
	{ 138, 0, 4, 130, 0.0625f, 1.25f },
	{ 139, 0, 4, 130, 1, 1 },
	{ 140, 0, 4, 130, 1, 1 },
	{ 141, 0, 4, 130, 0.0625f, 1.25f },
	{ 142, 0, 4, 130, 0.0625f, 1.25f },
	{ 143, 0, 4, 130, 1, 1 },
	{ 144, 0, 4, 130, 0.0625f, 1 },
	{ 145, 0, 13, 121, 0.25f, 0.3f },
	{ 146, 0, 13, 122, 0.25f, 0.3f },
	{ 147, 0, 13, 123, 0.25f, 0.3f },
	{ 148, 0, 13, 124, 0.25f, 0.3f },
	{ 149, 0, 3, 125, 0.25f, 0.3f },
	{ 150, 0, 3, 126, 0.25f, 0.3f },
	{ 151, 0, 6, 127, 0.25f, 0.4f },
	{ 152, 0, 4, 129, 0.125f, 0.3f },
	{ 153, 0, 3, 129, 0.125f, 0.4f },
	{ 154, 0, 4, 121, 0.125f, 0.4f },
	{ 156, 0, 4, 121, 0.25f, 0.3f },
	{ 155, 0, 4, 122, 0.25f, 0.3f },
	{ 157, 0, 9, 129, 0.0625f, 1 },
	{ 158, 0, 9, 129, 0.0625f, 1 },
	{ 159, 0, 9, 129, 0.0625f, 1 },
	{ 160, 0, 9, 129, 0.0625f, 1 },
	{ 161, 0, 9, 129, 0.0625f, 1 },
	{ 162, 0, 9, 129, 0.0625f, 1 },
	{ 163, 0, 9, 129, 0.0625f, 1 },
	{ 164, 0, 9, 129, 0.0625f, 1 },
	{ 165, 0, 9, 129, 0.0625f, 1 },
	{ 166, 0, 9, 129, 0.0625f, 1 },
	{ 167, 0, 9, 129, 0.0625f, 1 },
	{ 168, 0, 9, 129, 0.0625f, 1 },
	{ 169, 0, 3, 169, 0.0625f, 0.1f },
	{ 170, 0, 3, 170, 0.25f, 0.1f },
	{ 171, 0, 11, 171, 0.25f, 1.4f },
	{ 172, 0, 11, 172, 0.25f, 1.4f },
	{ 173, 0, 11, 173, 0.25f, 1.4f },
	{ 174, 0, 11, 174, 0.25f, 1.4f },
	{ 175, 0, 4, 169, 0.25f, 1.4f },
	{ 176, 0, 3, 176, 0.03125f, 0.1f },
	{ 177, 0, 3, 177, 0.03125f, 0.1f },
	{ 178, 0, 9, 0, 0.03125f, 0.25f },
	{ 179, 0, 4, 169, 0.25f, 1.4f },
	{ 180, 0, 6, 180, 0.25f, 1.4f },
	{ 181, 0, 6, 181, 0.25f, 1.4f },
	{ 182, 0, 6, 182, 1, 1 },
	{ 183, 0, 6, 183, 1, 1 },
	{ 184, 0, 3, 184, 1, 0.5f },
	{ 185, 0, 4, 186, 0.25f, 0.3f },
	{ 186, 0, 3, 186, 0.25f, 0.5f },
	{ 187, 0, 3, 187, 0.25f, 0.8f },
	{ 188, 0, 6, 188, 0.25f, 0.3f },
	{ 189, 0, 4, 189, 0.25f, 0.2f },
	{ 190, 0, 3, 190, 0.25f, 0.3f },
	{ 191, 0, 3, 191, 0.25f, 0.2f },
	{ 192, 0, 11, 192, 0.25f, 0.2f },
	{ 193, 0, 11, 192, 0.25f, 0.2f },
	{ 194, 0, 3, 194, 0.0625f, 0.2f },
	{ 195, 0, 3, 195, 0.0625f, 0.2f },
	{ 196, 0, 3, 196, 0.0625f, 0.2f },
	{ 197, 0, 3, 197, 0.0625f, 0.2f },
	{ 198, 0, 3, 198, 0.125f, 0.2f },
	{ 199, 0, 3, 199, 0.25f, 0.2f },
	{ 200, 0, 3, 200, 0.25f, 0.2f },
	{ 201, 0, 6, 201, 0.125f, 0.8f },
	{ 202, 0, 3, 202, 0.125f, 0.5f }
};
