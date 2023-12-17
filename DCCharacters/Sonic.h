#pragma once

void SonicDrawCallBack_r(NJS_OBJECT* mdl);
void SuperDrawCallBack_r(NJS_OBJECT* mdl);
void DisplayPSOSonicEarpiece(EntityData1* data, SonicCharObj2* sco2);
void DisplayHSonicMask(EntityData1* data, SonicCharObj2* sco2);
void DisplayPSOSuperEarpiece(EntityData1* data, SuperSonicCharObj2* ssco2);
void DisplayHSuperMask(EntityData1* data, SuperSonicCharObj2* ssco2);
void SetSonicAccessoryParams(ObjectMaster* obj);
void SetSuperSonicAccessoryParams(ObjectMaster* obj);
void __cdecl Sonic_Display_PSO(ObjectMaster* obj);
void __cdecl Sonic_DispDelay1_H(ObjectMaster* obj);
void __cdecl Super_Display_PSO(ObjectMaster* obj);
void __cdecl Super_DispDelay3_H(ObjectMaster* obj);
void Init_Sonic();
void Init_SonicMDL(const char* name, const char* supername);
void Init_SonicAltMDL(const char* name);
void Init_Trial();
void Init_PSOP1(ModelInfo* info, ModelInfo* superinfo);
void Init_PSOAlt(ModelInfo* info);
void Init_HSonic(ModelInfo* info, ModelInfo* superinfo);

static NJS_MATRIX SonicHeadMatrix;
static NJS_MATRIX SuperHeadMatrix;
static ModelInfo* headset = nullptr;
static ModelInfo* hmask = nullptr;
static ModelInfo* superpart = nullptr;
static char* sonicmdlpack = nullptr;

FunctionPointer(void, SuperSonicDrawCallBack, (NJS_OBJECT* obj), 0x49C130);
//Start Position
StartPosition SonicDCStartingArray[];

//End Position
StartPosition SonicDCEndingArray[];

//Trial Sonic Animation List
AnimationInfo TrialSonicAnimListEdits[];