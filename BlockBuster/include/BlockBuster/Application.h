#include <SFML/Graphics.hpp>
#include <Utils/Logger.h>

#include <BlockBuster/Bob.h>
#include <BlockBuster/Map.h>

#include "BlockBuster/LevelEditor.h"

class Application{
public:
    Application(int argc, const char* argv[]);
    void run();
private:

    void bobMovement(const sf::Time& deltaTime);
    void cratesLogic(const sf::Time& deltaTime);

    void handleEvents();
    void update();
    void render();
    void imGuiLayer();
    void parseArgs(int argc, const char* argv[]);

private:
    sf::RenderWindow m_Window;
    sf::Clock m_InternalClock;
    Bob m_Bob;
    Map m_Map;
    sf::View m_View;

    LevelEditor m_LevelEditor;
    bool m_InLevelEditor;

    bool m_DrawLogger;
    bool m_IsInFocus;
};