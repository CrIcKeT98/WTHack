#include <Windows.h>
#include <vector>

#include "memory.h"

//To fix LNK2019: A static data member is declared but not defined
namespace memory {
    uintptr_t* memory::static_pointers::game_context_ptr;
    Player** memory::static_pointers::local_player_ptr;
    PlayerList* memory::static_pointers::player_list_ptr;
    UnitList* memory::static_pointers::unit_list_ptr;
    HUD** memory::static_pointers::hud_ptr;
    uintptr_t* memory::static_pointers::lead_indicator_ptr;
}

std::uintptr_t memory::scan(const char* signature) noexcept {
    auto pattern_to_byte = [](const char* pattern) noexcept -> std::vector<int> {
        auto bytes = std::vector<int>{ };
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;

                if (*current == '?') {
                    ++current;
                }

                bytes.push_back(-1);
            }
            else {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }

        return bytes;
    };

    static const auto handle = ::GetModuleHandle("aces.exe");

    if (!handle)
        return 0;

    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);

    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i) {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }

        if (found) {
            return reinterpret_cast<std::uintptr_t>(&scanBytes[i]);
        }
    }

    return 0;
}
