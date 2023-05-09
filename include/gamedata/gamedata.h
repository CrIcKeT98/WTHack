#pragma once
#include "player.h"
#include "hud.h"
#include "gamecontext.h"

class GameData {
public:
	static GameData* instance();
	void init();
	void update();
	void print();

	uintptr_t game_context;
	Player* local_player;
	PlayerList player_list;
	UnitList unit_list;
	HUD* hud;
	WTF* wtf;
	LeadingIndicators* lead_indicator;

private:
	GameData() = default;
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;

	bool is_init;
};