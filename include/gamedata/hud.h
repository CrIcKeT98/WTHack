#pragma once
#include <cstdint>

struct HUD {
	std::uint8_t pad_0x0000[0x20];
	bool select_marker_by_cursor;
	bool marker_lock;
	
	std::uint8_t pad_0022[0x22];
	bool allow_3rd_person_camera;
	bool allow_virtual_cabine;
	
	std::uint8_t pad_0046[0x64];
	bool show_radar_in_3rd_person;

	std::uint8_t pad_00AB[0x115];
	std::uint32_t show_markers;
	std::uint32_t show_air_target_in_minimap; //0 - nothing, 1 - allies, 2 - all
	std::uint32_t show_ground_target_in_minimap; //0 - nothing, 1 - allies, 2 - all

	std::uint8_t pad_01CC[0xB5];
	bool air_leading_indicator;
	bool draw_plane_aim_indicator;
	bool show_marker_arrows;
	bool show_left_hud_panel;
	bool show_enemies_on_minimap;
	bool show_minimap;
	std::uint8_t pad_0287[0x2];
	bool hud_damage_panel; //0x289

	std::uint8_t pad_028A[0x2];
	bool cross_indicator; //show where the shell will strike and penetration probability
	bool unit_glow;
	bool gunner_sight_distance; //show distance in tank sight

	std::uint8_t pad_028F[0x45];
	bool bombsight;
};

struct WTF {
	std::uint8_t pad_0000[0x168];
	float cross_indicator_distance;
	float penetration_distance;
};

//Set draw distance of leading marker
struct LeadingIndicators {
	float air_distance;
	float tank_distance;
	float ship_distance;
};