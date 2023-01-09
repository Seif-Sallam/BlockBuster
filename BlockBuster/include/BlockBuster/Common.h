#pragma once

enum BlockType : uint8_t {
    BLOCKED = 1,
    WALKABLE = 0,
    BLOCKED_EXIT = 255,
    UNBLOCKED_EXIT = 128,
    CRATE_DEST = 240,
    COUNT = 100,
};

constexpr size_t TILE_SIZE = 64U;