#pragma once
#include <SFML/Graphics.hpp>

class Bob : public sf::Drawable, public sf::Transformable, public sf::FloatRect
{
public:
    void Init();
    void setTilePosition(const sf::Vector2i& pos);
    inline sf::Vector2i getTilePosition() { return m_Position; }

    void update(const sf::Time& deltaTimem);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
private:
    sf::Sprite m_Sprite;
    sf::Vector2i m_Position;
    sf::Texture* m_Texture;
};