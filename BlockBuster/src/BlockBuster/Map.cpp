#include "BlockBuster/Map.h"
#include "BlockBuster/Common.h"

#include <Utils/Logger.h>

#include <string>
#include <array>

inline static BlockType
determineBlock(const sf::Color& clr){
    if (clr.r == 255 && clr.g == 0 && clr.b == 0)
        return BLOCKED;
    if (clr.r == 0 && clr.g == 255 && clr.b == 0)
        return WALKABLE;
    if (clr.r == 0 && clr.g == 0 && clr.b == 255)
        return BLOCKED_EXIT;
    if (clr.r == 0 && clr.g == 0 && clr.b == 0)
        return CRATE_DEST;
    return COUNT;
}

// inline static std::string
// fromVec2ToString(const sf::Vector2f& v)
// {
//     return fmt::format("({}, {})", v.x, v.y);
// }

template<>
struct fmt::formatter<sf::Vector2f>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx){
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(sf::Vector2f const& v, FormatContext& ctx)
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

inline static std::array<sf::Vertex, 4>
constructBox(sf::Vertex& vertex)
{
    std::array<sf::Vertex, 4> vs;
    for (auto& v : vs)
        v = vertex;

    vs[1].position += sf::Vector2f(TILE_SIZE, 0);
    vs[2].position += sf::Vector2f(TILE_SIZE, TILE_SIZE);
    vs[3].position += sf::Vector2f(0, TILE_SIZE);

    Util::Logger::Debug("Box verticies: {}, {}, {}, {}", vs[0].color, vs[1].color, vs[2].color, vs[3].color);
    return vs;
}


Map::Map(){
    initializeShader();
}

void
Map::initializeShader()
{
    // TODO: Add the shader code! to make the gorund tiled!
//     constexpr const char* fragmentShader =
//     R"(
// void main(){
//     vec4 backgroundColor =
// }
//     )";
}

BlockType
Map::getTileType(const sf::Vector2i& position)
{
    if (position.x >= 0 && position.y >= 0 && position.x < m_MapValues.size() && position.y < m_MapValues[position.x].size())
        return m_MapValues[position.x][position.y];
    else
        return BlockType::COUNT;
}

void
Map::loadMap(const std::string_view& file_path)
{

    m_Verticies.clear();
    m_Verticies.setPrimitiveType(sf::Quads);

    sf::Image image;
    image.loadFromFile(file_path.data());
    auto pixels = image.getPixelsPtr();
    auto size = image.getSize();

    m_MapValues.clear();
    m_MapValues.resize(size.x);
    for(auto& v : m_MapValues)
        v.resize(size.y);

    for (uint32_t i = 0; i < size.x; i++)
        for(uint32_t j = 0; j < size.y; j++)
        {
            const uint32_t index = j * size.x + i;
            sf::Color clr = image.getPixel(i, j);
            m_MapValues[i][j] = COUNT;
            // We represent the map with a bunch of pixels in a png, as RGBA
            // (255, 0, 0, -) (Blocked Path)
            // (0, 255, 0, -) (Walkable Path)
            // (0, 0, 255, -) (Exit)
            // We can allocate the alpha to have any extra data if we want to.

            auto block = determineBlock(clr);
            if (block == COUNT)
            {
                Util::Logger::Error("Couldnot determine the block at pixel: {}, {}", i, j);
                Util::Logger::Error("Found: ({}, {}, {}, {})", clr.r, clr.g, clr.b, clr.a);
                continue;
            }

            sf::Vector2f position = sf::Vector2f(float(i * TILE_SIZE), float(j * TILE_SIZE));

            m_MapValues[i][j] = block;

            switch(block)
            {
                case BLOCKED:
                    clr = sf::Color(200, 2, 2);
                break;
                case WALKABLE:
                    clr = sf::Color(66, 66, 66);
                break;
                case BLOCKED_EXIT:
                    clr = sf::Color(232, 210, 42, 200);
                    m_ExitCoord = sf::Vector2u(i, j);
                break;
                case CRATE_DEST:
                    clr = sf::Color(0, 134, 134, 255);
                break;
            }

            sf::Vertex vertex(position, clr);
            auto box = constructBox(vertex);
            for (auto v : box){
                m_Verticies.append(v);
            }
        }

    Util::Logger::Debug("Number of Verticies: {}", m_Verticies.getVertexCount());
}

void
Map::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    // state.shader = &m_Shader;
    target.draw(m_Verticies, state);
}