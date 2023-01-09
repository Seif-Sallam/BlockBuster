#include "BlockBuster/ResourceManager.h"

#include <filesystem>

#include <Utils/Logger.h>
#include <Utils/Functions.h>

ResourceManager ResourceManager::s_Instance;

Texture ResourceManager::registerTexture(const std::string& filePath, const std::string& name, const sf::IntRect& intRect)
{
    // It is an old texture.
    if (auto texture = getTexture(name); texture.isValid())
        return texture;

    Texture& texture = m_TextureMap[name];
    // It is a new texture, but we have loaded that image before
    if (m_InternalTextureMap.find(filePath) != this->m_InternalTextureMap.end())
    {
        auto& actualTexture = m_InternalTextureMap[filePath];
        texture.m_Name = name;
        texture.m_HashName = filePath;
        texture.m_ParentTexture = &actualTexture;

        if (intRect.width == 0)
        {
            texture.m_TextureRect.width = actualTexture.getSize().x;
            texture.m_TextureRect.height = actualTexture.getSize().y;
        }
        else
        {
            texture.m_TextureRect = intRect;
        }

        Util::Logger::Info("Found an already loaded image, so we added Texture: {}", name, filePath);
        return texture;
    }

    // It is a new texture and we have not loaded the image before
    sf::Texture& actualTexture = this->m_InternalTextureMap[filePath];
    if (actualTexture.loadFromFile(filePath))
    {
        texture.m_Name = name;
        texture.m_HashName = filePath;
        texture.m_ParentTexture = &actualTexture;
        if (intRect.width == 0)
        {
            texture.m_TextureRect.width = actualTexture.getSize().x;
            texture.m_TextureRect.height = actualTexture.getSize().y;
        }
        else
        {
            texture.m_TextureRect = intRect;
        }

        Util::Logger::Info("Did not find an already loaded texture, so we loaded Texture: {} from {}", name, filePath);
    }
    else
    {
        // We weren't able to load the texture at all
        Util::Logger::Error("Was not able to load the texture: {} from the path {}", name, filePath);
        // Cleanup the entries from the table
        this->m_TextureMap.erase(name);
        this->m_InternalTextureMap.erase(filePath);
    }
    // Return the texture eventually
    return texture;
}

void ResourceManager::registerFromXML(const std::string& xmlFilePath)
{
    if (std::filesystem::is_regular_file(xmlFilePath))
    {
        tinyxml2::XMLDocument document;
        if (document.LoadFile(xmlFilePath.data()) != tinyxml2::XML_SUCCESS)
        {
            Util::Logger::Error("Error Parsing the xml file: {}", xmlFilePath);
            return;
        }

        auto textureAtlasTag = document.FirstChildElement("TextureAtlas");
        auto imagePath = textureAtlasTag->Attribute("imagePath");
        std::filesystem::path path(xmlFilePath);
        path = path.parent_path();
        path.concat("/");
        path.concat(imagePath);
        registerTexture(path.string(), path.string() + ".ATLAS");

        auto textureElement = textureAtlasTag->FirstChildElement("SubTexture");
        uint32_t subTextureCount{};
        while(textureElement != nullptr)
        {
            auto name = textureElement->Attribute("name");
            auto x = textureElement->IntAttribute("x");
            auto y = textureElement->IntAttribute("y");
            auto width = textureElement->IntAttribute("width");
            auto height = textureElement->IntAttribute("height");

            auto sanitizedName = Util::RemovePrefix(".png", name);

            registerTexture(path.string(), sanitizedName, sf::IntRect(x, y, width, height));

            textureElement = textureElement->NextSiblingElement("SubTexture");

            subTextureCount++;
        }
        Util::Logger::Info("Added {} Sub-Textures from the texture at {}", subTextureCount, path.string());
    }
    else
    {
        Util::Logger::Error("Was not able to open the XML file {}", xmlFilePath);
    }
}

Texture ResourceManager::getTexture(const std::string& name)
{
    if (auto itr = m_TextureMap.find(name); itr != m_TextureMap.end())
        return itr->second;
    return Texture{};
}