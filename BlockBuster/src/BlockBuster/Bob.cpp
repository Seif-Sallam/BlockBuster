#include "BlockBuster/Bob.h"
#include "BlockBuster/Common.h"
#include "BlockBuster/Map.h"
#include "BlockBuster/ResourceManager.h"

#include <Utils/Logger.h>

void
Bob::Init()
{
    auto texture = ResourceManager::get().getTexture("player_01");
    if (texture.isValid() == false)
    {
        Util::Logger::Error("Could not initalize Bob Texture");
        return;
    }
    m_Texture = texture.texture();
    m_Sprite.setTexture(*m_Texture);
    m_Sprite.setTextureRect(texture.textureRect());
    this->width = texture.textureRect().width;
    this->height = texture.textureRect().height;
}

void
Bob::setTilePosition(const sf::Vector2i& pos)
{
    this->m_Position = pos;
    setPosition(float(pos.x * TILE_SIZE), float(pos.y * TILE_SIZE));
    this->left = getPosition().x;
    this->top = getPosition().y;
}

void
Bob::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    state.transform *= getTransform();
    target.draw(this->m_Sprite, state);
}

void
Bob::update(const sf::Time& deltaTime)
{

}