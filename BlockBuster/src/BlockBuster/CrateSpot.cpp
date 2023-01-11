#include "BlockBuster/CrateSpot.h"
#include "BlockBuster/ResourceManager.h"

#include <Utils/Logger.h>

static const std::vector<std::string> textureNames = {
    "environment_02",
    "environment_05",
    "environment_14",
    "environment_10",
    "environment_08",};

CrateSpot::CrateSpot()
{
}

void CrateSpot::setTileTexture(const std::string& tileTextureName)
{
    auto texture = ResourceManager::get().getTexture(tileTextureName);
    if (texture.isValid() == false)
    {
        Util::Logger::Error("Could not get the Tile texture at: {}, Texure: {}", m_TilePosition, tileTextureName);
        return;
    }
    m_TileTexture = texture.texture();
    m_TileSprite.setTexture(*m_TileTexture);
    m_TileSprite.setTextureRect(texture.textureRect());
}

void CrateSpot::setTileType(TileType tileType)
{
    m_TileType = tileType;
    auto texture = ResourceManager::get().getTexture(textureNames[tileType]);
    if (texture.isValid() == false)
    {
        Util::Logger::Error("Could not get the environment texture at: {}, Texure: {}", m_TilePosition, textureNames[tileType]);
        return;
    }
    m_TileColorTexture = texture.texture();
    m_TileColorSprite.setTexture(*m_TileColorTexture);
    m_TileColorSprite.setTextureRect(texture.textureRect());
}

TileType CrateSpot::getTileType()
{
    return m_TileType;
}

void CrateSpot::setTiledPosition(const sf::Vector2i& position)
{
    m_TilePosition = position;
    setPosition((sf::Vector2f)m_TilePosition * (float)TILE_SIZE);
}

void CrateSpot::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    state.transform *= getTransform();
    target.draw(m_TileSprite, state);
    target.draw(m_TileColorSprite, state);
}
