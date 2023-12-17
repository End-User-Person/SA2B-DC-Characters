#pragma once
#include "stdafx.h"

// Generic file replacement macro. Assumes "resource" is the start of the mod folder path.
#define ReplaceItem(sourcefile, editfolderpath, editfile, extension)  helperFunctions.ReplaceFile("resource\\gd_PC\\" sourcefile, "resource\\" editfolderpath "\\" editfile "." extension)
// MDL/MTN archive redirect macro.
#define ReplaceCharData(source, edit)  helperFunctions.ReplaceFile("resource\\gd_PC\\" source ".prs", (std::string(path) + "\\Data\\figure\\" edit ".prs").c_str())
#define ReplaceCharData2(source, edit)  helperFunctions.ReplaceFile("gd_PC\\" source ".prs", "gd_PC\\" edit ".prs")
// Texture archive redirect macro.
#define ReplaceTexPack(sourcepack, name)  helperFunctions.ReplaceFile("resource\\gd_PC\\" sourcepack ".prs", "resource\\gd_PC\\" name ".prs")
// Texture archive redirect macro for life icons.
#define ReplaceLifeTexPack(sourcepack, name)  helperFunctions.ReplaceFile("resource\\gd_PC\\PRS\\" sourcepack ".pak", "resource\\gd_PC\\" name ".prs")
// Used for replacing individual textures instead of the entire pack.
#define ReplaceSingleTex(gvm, gvr, folder, name, index, x, y) helperFunctions.ReplaceTexture(gvm, gvr, (std::string(path) + "\\textures\\" folder "\\" name ".png").c_str(), index, x, y)
// ModelInfo macro. Assumes all relevant animation files are stored in the Data folder
#define FindModel(file) new ModelInfo(std::string(path) + "\\Data\\" file);
// AnimationFile macro. Assumes all relevant animation files are stored in the Data folder
#define FindMotion(file) new AnimationFile(std::string(path) + "\\Data\\" file);
// WriteData macro for models.
#define WriteModel(address) WriteData((NJS_OBJECT**)address, mdlinf->getmodel());
// WriteData macro for animations.
#define WriteMotion(address) WriteData((NJS_MOTION**)address, animinf->getmotion());
// WriteData macro for MDL/MTN loading.
#define WriteCharDataFile(address, name) WriteData((const char**)address, name ".PRS")

#define SpeedTypeMasterMatrix ((NJS_MATRIX_PTR)0x1A51A00)
#define SuperMasterMatrix ((NJS_MATRIX_PTR)0x19EE0C0)
#define HuntingMasterMatrix ((NJS_MATRIX_PTR)0x1A51BEC)
#define RougeTorsoMatrix ((NJS_MATRIX_PTR)0x1A51B0C)
#define RougeTorsoShdMatrix ((NJS_MATRIX_PTR)0x1A51B7C)
#define MechMasterMatrix ((NJS_MATRIX_PTR)0x1A51F70)
#define MechBlasterMatrix ((NJS_MATRIX_PTR)0x1A51EAC)
#define MechTailsPartMatrix ((NJS_MATRIX_PTR)0x1A520F0)

//Customization Options

enum DCSonic { SonicDC, SonicSA2B, SonicDCAlt, SonicTrial, SonicTrialBeta, HSonic, XSonic };
enum DCShadow { ShadowDC, ShadowSA2B, ShadowDCAlt, HShadow, XShadow };
enum DCKnuckles { KnucklesDC, KnucklesSA2B, KnucklesDCAlt, HKnuckles, XKnuckles };
enum DCRouge { RougeDefault, RougeDC, RougeSA2B, RougeDCAlt, HRouge, XRouge };
enum RougeWing { WingDC, WingSA2B, DefaultWing };
enum DCMechTails { MTailsDC, MTailsSA2B, MTailsDCAlt, HMTails, XMTails };
enum DCMechEggman { MEggmanDC, MEggmanSA2B, MEggmanDCAlt, HMEggman, XMEggman };
enum DarkChaoWalker { NoChange, Big };
enum DCSonicAnim { SonicAnimDC, SonicAnimSA2B, SonicAnimTrial };
enum RougeAnim { RougeDefaultAnim, RougeAnimDC, RougeAnimSA2B };

static int DCSonic = SonicDC;
static int DCShadow = ShadowDC;
static int DCKnuckles = KnucklesDC;
static int DCRouge = RougeDC;
static int RougeWing = WingDC;
static int DCMechTails = MTailsDC;
static int DCMechEggman = MEggmanDC;
static int DarkChaoWalker = Big;
static int DCSonicAnim = SonicAnimDC;
static int RougeAnim = RougeAnimDC;

static bool DCTails = true;
static bool DCEggman = true;
static bool DCAmy = true;
static bool DCMetalSonic = true;
static bool DCTikal = true;
static bool DCChaos = true;
static bool DCChaoWalker = true;
static bool DCBattleScreen = true;
static bool MetalSonicEffTex = true;
static bool DCLifeIcons = true;
static bool DisableSpBG = true;
static bool DCFieldUpgrades = true;
static bool BetaSShadowTex = false;
static bool DCShadowAnim = true;
static bool DCKnucklesAnim = true;
static bool DCRougeAnim = true;
static bool DCMechTailsAnim = true;
static bool DCMechEggmanAnim = true;
static bool DCTailsAnim = true;
static bool DCEggmanAnim = true;
static bool DCAmyAnim = true;
static bool DCMetalSonicAnim = true;
static bool DCTikalAnim = true;
static bool DCChaosAnim = true;
static bool DCChaoWalkerAnim = true;

static const void* const setGenericMatrixPtr = (void*)0x42F770;
static inline void setGenericMatrix(float* a1)
{
	__asm
	{
		mov eax, [a1]
		call setGenericMatrixPtr
	}
}

static const void* const setGenericLightPtr = (void*)0x487060;
static inline void setGenericLight(int a1)
{
	__asm
	{
		mov eax, [a1]
		call setGenericLightPtr
	}
}

static const void* const setGenericGCLightPtr = (void*)0x486E50;
static inline void setGenericGCLight(char a1, char a2)
{
	__asm
	{
		mov al, [a2]
		mov cl, [a1]
		call setGenericGCLightPtr
	}
}

FunctionPointer(void, sub_427040, (NJS_MATRIX_PTR a1, NJS_MATRIX_PTR a2), 0x427040);
FunctionPointer(signed int, sub_7983F0, (NJS_VECTOR* a1, float a2), 0x7983F0);
DataPointer(char, byte_174AFE2, 0x0174AFE2);
DataPointer(char, byte_174AFE0, 0x0174AFE0);
using ModelFuncPtr = void(__cdecl*)(NJS_OBJECT*);
DataPointer(char, byte_174AFFD, 0x174AFFD);
DataPointer(char, byte_1DE4660, 0x1DE4660);

DataPointer(ModelFuncPtr, GenericModelCallBack, 0x1A55834);