#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Block : public sf::Drawable, public sf::Transformable
{
public:
    Block();

    void setTiledPosition(const sf::Vector2i& tiledPoistion);
    const sf::Vector2i getTiledPosition() const;
    void setTexture(const std::string& textureName);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    sf::Sprite m_Sprite;
    sf::Texture* m_Texture;
    sf::Shader m_Shader;

    sf::Vector2i m_TiledPosition;
};