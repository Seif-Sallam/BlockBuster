#pragma once

#include <SFML/Graphics.hpp>

#include "BlockBuster/Common.h"

#include <vector>
#include <string>
#include <map>

class Map : public sf::Drawable
{
public:
    Map();
    void loadMap(const std::string_view& filePath);
    BlockType getTileType(const sf::Vector2i& position);

private:
    void initializeShader();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

private:
    std::vector<std::vector<BlockType>> m_MapValues;
    sf::VertexArray m_Verticies;
    sf::Shader m_Shader;
    sf::Vector2u m_ExitCoord;
};