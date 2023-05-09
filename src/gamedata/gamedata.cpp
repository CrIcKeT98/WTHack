#include "gamedata/gamedata.h"
#include "memory.h"

GameData* GameData::instance() {
	static GameData inst;
	return &inst;
}

void GameData::init() {
	if (!is_init) {
		uintptr_t gamecontext_ptr = memory::scan("48 8B 05 ? ? ? ? F2 0F 10 4F 08");
		memory::static_pointers::game_context_ptr = memory::get_addr<uintptr_t*>(gamecontext_ptr, 0x03);	

		std::uintptr_t player_ptr = memory::scan("48 8b 2d ? ? ? ? 48 85 ed 74 ? f6 85 ? ? ? ? ? 74");
		memory::static_pointers::local_player_ptr = memory::get_addr<Player**>(player_ptr, 0x03);

		std::uintptr_t player_list_ptr = memory::scan("48 8B 05 ? ? ? ? 48 8D 14 D0 0F B7 79 08 EB 28");
		memory::static_pointers::player_list_ptr = memory::get_addr<PlayerList*>(player_list_ptr, 0x03);

		uintptr_t hud_ptr = memory::scan("48 8b 0d ? ? ? ? 80 b9 ? ? ? ? ? 0f 84 ? ? ? ? 80 bf");
		memory::static_pointers::hud_ptr = memory::get_addr<HUD**>(hud_ptr, 0x03);
		
		uintptr_t leading_indicator_ptr = memory::scan("48 8B 0D ? ? ? ? 48 85 C9 0F 94 C2");
		memory::static_pointers::lead_indicator_ptr = memory::get_addr<uintptr_t*>(leading_indicator_ptr, 0x03);

		update();
		is_init = true;
	}
}

void GameData::update() {
	if (!is_init)
		return;

	game_context = *memory::static_pointers::game_context_ptr;
	local_player = *memory::static_pointers::local_player_ptr;

	player_list = *memory::static_pointers::player_list_ptr;
	player_list.players_count = (std::uint32_t*)((uintptr_t)memory::static_pointers::player_list_ptr - 0x90);
	
	unit_list.list = *reinterpret_cast<Unit***>((uintptr_t)game_context + 0x368);
	unit_list.units_count = *(std::uint32_t*)((uintptr_t)game_context + 0x378);

	hud = *memory::static_pointers::hud_ptr;

	//aces.exe + ???? -> 0x660 -> 0x6E4
	lead_indicator = (LeadingIndicators*)(*(uintptr_t*)(*memory::static_pointers::lead_indicator_ptr + 0x660) + 0x6E4);
}

#include <iostream>
void GameData::print() {
	using namespace std;
	cout << "Game context: " << hex << game_context << endl;
	cout << "Local player: " << hex << local_player << endl;
	cout << "Player list: " << hex << player_list.list << endl;
	cout << "Players count: " << dec << *player_list.players_count << endl;
	cout << "Unit list: " << hex << unit_list.list << endl;
	cout << "Units count: " << dec << unit_list.units_count << endl;
	cout << "Hud: " << hex << hud << endl;
	cout << "Leading indicators: " << hex << lead_indicator << endl;
}