#pragma once

#include <fmt/core.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

enum BlockType : uint8_t {
    BLOCKED = 1,
    WALKABLE = 0,
    BLOCKED_EXIT = 255,
    UNBLOCKED_EXIT = 128,
    CRATE_DEST = 240,
    COUNT = 100,
};

enum TileType : uint8_t {
    ORANGE,
    RED,
    SILVER,
    GREEN,
    BLUE
};

constexpr size_t TILE_SIZE = 64U;

template<class T>
struct fmt::formatter<sf::Vector2<T>>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx){
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(sf::Vector2<T> const& v, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}, {})", v.x, v.y);
    }
};

template<>
struct fmt::formatter<sf::Color>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx){
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(sf::Color const& v, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}, {}, {}, {})", v.r, v.g, v.b, v.a);
    }
};