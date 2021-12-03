#pragma once

//Start Position
StartPosition RougeStartingArray[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_PumpkinHill, 0xD000, 0xD000, 0xD000, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SecurityHall, 0xA000, 0xA000, 0x6000, { 405, -830, 410 }, { 405, -830, 410 }, { -405, -830, 410 } },
	{ LevelIDs_DeathChamber, 0xA000, 0x8000, 0xC000, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_EggQuarters, 0xA000, 0xA000, 0xA000, { 940, -30, 940 }, { 940, -30, 940 }, { 940, -30, 940 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 65, -400 }, { 200, 65, -400 }, { 200, 65, -400 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_KnucklesVsRouge, 0x8000, 0x8000, 0x8000, { 20, 0, 0 }, { 20, 0, 0 }, { 20, 0, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_CannonsCoreR, 0xC000, 0xC000, 0xC000, { 0, 480, 150 }, { 0, 480, 150 }, { 0, 480, 150 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -450, -1025 }, { 25, -450, -1025 }, { -25, -450, -1025 } },
	{ LevelIDs_MadSpace, 0x7000, 0x7000, 0x7000, { 0, 660, 0 }, { 0, 660, 0 }, { 0, 660, 0 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 220, 210, 1350 }, { 225, 480, 1325 }, { 185, 480, 1325 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_PlanetQuest, 0, 0x4000, 0x4000, { 0, 660, 0 }, { -470, 1500, -630 }, { -430, 1500, -630 } },
	{ LevelIDs_DeathChamber2P, 0xA000, 0x8000, 0xC000, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_Invalid }
};

//End Positions
StartPosition RougeEndingArray[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_PumpkinHill, 0xD000, 0xD000, 0xD000, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SecurityHall, 0xA000, 0xA000, 0x6000, { 405, -933, 410 }, { 405, -933, 410 }, { -405, -933, 410 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 15, -140 }, { 200, 15, -140 }, { 200, 15, -140 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 856, -140 }, { 220, 856, -140 }, { 180, 856, -140 } },
	{ LevelIDs_DeathChamber, 0x2000, 0xE000, 0xE000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_EggQuarters, 0x2000, 0x2000, 0x2000, { 980, -30, 980 }, { 980, -30, 980 }, { 980, -30, 980 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { 10, -340, 0 }, { 10, -340, 0 }, { 10, -340, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0x4000, { 200, 65, -400 }, { 220, 65, -400 }, { 180, 65, -400 } },
	{ LevelIDs_CannonsCoreR, 0x8000, 0x8000, 0x8000, { 120, 20, 0 }, { 120, 20, 0 }, { 120, 20, 0 } },
	{ LevelIDs_FlyingDog, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -500, -1025 }, { 25, -500, -1025 }, { -25, -500, -1025 } },
	{ LevelIDs_MadSpace, 0x7000, 0x7000, 0x7000, { 0, 620, 0 }, { 0, 620, 0 }, { 0, 620, 0 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 200, 210, 1350 }, { 200, 210, 1350 }, { 200, 210, 1350 } },
	{ LevelIDs_PoolQuest, 0, 0, 0, { 0, 130, -200 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { 0, 620, 0 }, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_DeathChamber2P, 0x2000, 0xE000, 0xE000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_Invalid }
};