#include "BlockBuster/Block.h"
#include "BlockBuster/Common.h"
#include "BlockBuster/ResourceManager.h"

#include <Utils/Logger.h>

Block::Block()
{
    m_Sprite.setOrigin(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f);
}

void Block::setTiledPosition(const sf::Vector2i& tiledPoistion)
{
    m_TiledPosition = tiledPoistion;
    setPosition(m_TiledPosition.x * (float)TILE_SIZE, m_TiledPosition.y * (float)TILE_SIZE);
}

const sf::Vector2i Block::getTiledPosition() const
{
    return m_TiledPosition;
}

void Block::setTexture(const std::string& textureName)
{
    Texture texture = ResourceManager::get().getTexture(textureName);
    if (texture.isValid())
    {
        Util::Logger::Error("Invalid texture for the Block {}", m_TiledPosition);
        return;
    }
    m_Texture = texture.texture();
    m_Sprite.setTexture(*m_Texture);
    m_Sprite.setTextureRect(texture.textureRect());
    m_Sprite.setOrigin(texture.textureRect().width / 2.0f, texture.textureRect().height / 2.0f);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // states.shader = m_Shader;
    target.draw(m_Sprite, states);
}
