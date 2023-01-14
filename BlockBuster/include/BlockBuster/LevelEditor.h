#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <array>
#include <map>
#include <unordered_map>

#include <Utils/Logger.h>

#include "BlockBuster/Block.h"
#include "BlockBuster/Grid.h"

class LevelEditor : public sf::Drawable
{
public:
    LevelEditor(sf::RenderWindow* renderWindow);

    void handleEvents(sf::Event& event);
    void imguiLayer();
    void update(const sf::Time& deltaTime);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    sf::Vector2f getMousePosition();
    sf::Vector2i getTilePosition(const sf::Vector2i);

    void updateBlockHighlight();
    void addBlock(const sf::Vector2i& tilePosition);

private:
    sf::RenderWindow* m_RenderWindow;

    // std::unordered_map<sf::Vector2i, Block> m_BlocksMap;
    sf::VertexArray m_BlockHighlight;
    sf::Vector2i m_MinTile;
    sf::Vector2i m_MaxTile;

    Grid m_Grid;
    std::map<std::string, sf::RenderTexture> m_Textures;

    sf::View m_View;
    float m_ZoomLevel;

    bool m_UpdateGrid;
};