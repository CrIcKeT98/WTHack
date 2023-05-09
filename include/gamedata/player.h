#pragma once
#include <cstdint>
#include "units.h"

enum class GuiState : std::uint8_t {
	NONE = 0,
	MENU = 1,
	ALIVE = 2,
	DEAD = 3,
	SPEC = 6,
	LIMBO = 8,
	LOADING = 10
};

//Size: 0xF38
struct Player {
	std::uint8_t pad_0000[0xA8];
	char nickname[0x20];

	std::uint8_t pad_00C8[0x50];
	char* userId;

	std::uint8_t pad_0120[0x80];
	char clanTag[0x8];

	std::uint8_t pad_01A8[0x338];
	GuiState guiState;

	std::uint8_t pad_04E1[0x1FF];
	Unit* ownedUnit;

	bool IsAlive() const noexcept
	{
		return guiState == GuiState::ALIVE;
	}

	bool IsDead() const noexcept
	{
		return guiState == GuiState::DEAD;
	}

	bool IsinHangar() const noexcept
	{
		return guiState == GuiState::MENU;
	}
};

struct PlayerList {
	Player** list;
	std::uint32_t* players_count;
};