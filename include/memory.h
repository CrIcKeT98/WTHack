#pragma once
#include <cstdint>

struct GameContext;
struct Player;
struct PlayerList;
struct UnitList;
struct HUD;
struct LeadingIndicators;

namespace memory {
	//stores static pointers of aces.exe for easier using and update of pointers
	struct static_pointers {
		static uintptr_t* game_context_ptr;
		static Player** local_player_ptr;
		static PlayerList* player_list_ptr;
		static UnitList* unit_list_ptr;
		static HUD** hud_ptr;
		static uintptr_t* lead_indicator_ptr;
	};

	std::uintptr_t scan(const char* signature) noexcept;

	// Get addr by <mnemonic [OFFSET]>. 2nd arg is mnemonic size
	template<typename T = std::uintptr_t>
	T get_addr(std::uintptr_t addr, int mnemonic_size) noexcept {
		std::uint32_t offset_4sz = *reinterpret_cast<std::uintptr_t*>(addr + mnemonic_size) & 0xFFFFFFFF;
		return reinterpret_cast<T>(addr + offset_4sz + 0x7);
	}
}