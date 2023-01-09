#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include <tinyxml2.h>

class ResourceManager;

class Texture
{
public:
    Texture() = default;
    inline std::string getName() const { return m_Name; }
    inline sf::Texture* texture() const { return m_ParentTexture; }
    inline sf::IntRect textureRect() const { return m_TextureRect; }
    inline bool isValid() const { return m_ParentTexture != nullptr; }
private:
    sf::Texture* m_ParentTexture;
    sf::IntRect m_TextureRect;
    std::string m_Name;
    std::string m_HashName;
    friend ResourceManager;
};

class ResourceManager
{
public:
    inline static ResourceManager& get() { return s_Instance; }

    Texture registerTexture(const std::string& filePath, const std::string& name, const sf::IntRect& intRect = sf::IntRect(0, 0, 0, 0));
    void registerFromXML(const std::string& xmlFilePath);
    Texture getTexture(const std::string& filePath);

private:
    ResourceManager() = default;

    std::map<std::string, sf::Texture> m_InternalTextureMap;
    std::map<std::string, Texture> m_TextureMap;
    static ResourceManager s_Instance;
};
