#include "BlockBuster/Map.h"
#include "BlockBuster/Common.h"

#include <Utils/Logger.h>

#include <string>
#include <array>

static const std::vector<std::string> themeGroundTileNames = {
    "ground_01",     // Orange
    "ground_02",     // Green With Border
    "ground_03",     // Silver With Border
    "ground_04",     // Orange With Border
    "ground_05",     // Green
    "ground_06",     // Silver
};

static const std::vector<std::string> themeWallTileNames = {
    "block_01",     // Brick grayish 3D
    "block_02",     // Silver 3D
    "block_03",     // Wood 3D
    "block_04",     // Brick 2D
    "block_05",     // Brick Grayish 2D
    "block_06",     // Silver 2D
    "block_07",     // Wood 2D
    "block_08",     // Brick 3D
};

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
    // static const char* walkableTextureName  = "";
    // static const char* blockedTextureName   = "";
    // static const char* crateDestinationName = "";

    // The map load function is fucked up, we need a new format where you save the
    //      theme of the map, the ground theme, the starting position,
    //      the crates position, the crates destintations.

    // Util::Logger::Debug("Number of Verticies: {}", m_Verticies.getVertexCount());
}

void
Map::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    // state.shader = &m_Shader;
    target.draw(m_Verticies, state);
}