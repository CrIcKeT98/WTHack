#pragma once
#include "math/math.h"

struct Player;
struct UnitInfo;
struct UnitWeapons;

enum class Types : std::uint32_t {
	AIRCRAFT = 0,
	TANK = 3,
	BOAT = 5
};

enum class State : std::uint32_t {
	ALIVE = 0,
	not_sure = 1,
	DEAD = 2
};

struct Unit {
	std::uint8_t pad_0000[0x1F8];
	Vector3 BBmin;
	Vector3 BBmax;

	std::uint8_t pad_0210[0x508];
	std::uint8_t visualReload;

	std::uint8_t pad_0719[0x21B];
	RotationMatrix rotationMatrix;
	Vector3 position;

	std::uint8_t pad_0964[0x590];
	float Invulnerable;

	std::uint8_t pad_0EF8[0x100];
	State state;
	Types type;

	std::uint8_t pad_1000[0x8];
	Player* player; //1008

	std::uint8_t pad_1010[0x40];
	std::uint8_t team;

	std::uint8_t pad_1051[0xF];
	UnitInfo* unitInfo;

	std::uint8_t pad_1068[0xA8];
	UnitWeapons* unitWeapons;
};

struct UnitInfo {
	char* modelName;
	char* blkShortPath;
	char* blkFullPath;
	char* fullLocalizedName;
	char* shortLocalizedName;
	char* tankType;
	char* unitType;
	char* placeholderName;
	std::uint8_t pad_0040[0x1A4];
	float zoomMulti;
	float zoomAlternateMulti;
	std::uint8_t pad_01EC[0x10];
	float vignetteMulti;

	//Skeleton nodes with name length less 8 are located after *modelName

	bool isPlane() {
		return (strcmp(unitType, "exp_bomber") == 0 || strcmp(unitType, "exp_assault") == 0 || strcmp(unitType, "exp_fighter") == 0);
	}

	bool isTank() {
		return (strcmp(unitType, "exp_tank"));
	}

	bool isDummy() {
		return (strcmp(unitType, "exp_fortification") == 0 || strcmp(unitType, "exp_structure") == 0 || strcmp(unitType, "exp_aaa") == 0 || strcmp(unitType, "dummy_plane") == 0 || strcmp(unitType, "exp_bridge") == 0);
	}
};

struct UnitList {
	Unit** list;
	std::uint32_t units_count;
};

struct UnitWeaponInfo {
	auto name() const noexcept {
		return *reinterpret_cast<const char**>(std::uintptr_t(this) + 0x8);
	}

	auto& weapon_info_size() const noexcept {
		return *reinterpret_cast<int*>(std::uintptr_t(this) + 0xB0);
	}
};

struct UnitWeapon {
	auto weapon_info() const noexcept {
		return *reinterpret_cast<UnitWeaponInfo**>(std::uintptr_t(this) + 0x2A8);
	}

	auto& current_ammo_slot() const noexcept {
		return *reinterpret_cast<char*>(std::uintptr_t(this) + 0x524);
	}

	auto& next_ammo_slot() const noexcept {
		return *reinterpret_cast<char*>(std::uintptr_t(this) + 0x525);
	}
};

struct UnitWeaponList {
	UnitWeapon** m_weapons;
	int m_count;
};

struct UnitWeapons {
	auto weapon_list() const noexcept {
		return *reinterpret_cast<UnitWeaponList**>(std::uintptr_t(this) + 0x390);
	}
};
