#include "BlockBuster/StaticBlock.h"
#include "BlockBuster/ResourceManager.h"
#include "BlockBuster/Common.h"

StaticBlock::StaticBlock()
{
    width = (float)TILE_SIZE;
    height = (float)TILE_SIZE;
}

void StaticBlock::setTiledPosition(const sf::Vector2i& tiledPosition)
{
    m_TiledPosition = tiledPosition;
    setPosition((sf::Vector2f)m_TiledPosition * (float)TILE_SIZE);
    left = getPosition().x;
    top = getPosition().y;
}

const sf::Vector2i& StaticBlock::getTiledPosition() const
{
    return m_TiledPosition;
}

void StaticBlock::setTexture(const std::string& textureName)
{
    auto texture = ResourceManager::get().getTexture(textureName);
    if (texture.isValid() == false)
    {
        Util::Logger::Error("Invalid texture for the Static Block at {}!", m_TiledPosition);
        return;
    }
    m_Texture = texture.texture();
    m_Sprite.setTexture(*m_Texture);

    m_Sprite.setTextureRect(texture.textureRect());
}

void StaticBlock::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    state.transform *= getTransform();
    target.draw(m_Sprite, state);
}