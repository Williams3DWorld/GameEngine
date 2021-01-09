#include "sprite-layer.hpp"

namespace ast
{
    unsigned int& SpriteLayer::getTextureID()
    {
        return this->textureID;
    }

    void SpriteLayer::setTextureID(unsigned int value)
    {
        this->textureID = value;
    }

    void SpriteLayer::addChild(std::shared_ptr<GameObject>& value)
    {
        this->_children[value->getName()] = value;
    }

    void SpriteLayer::update(float dt)
    {
        for (auto sprite : this->_children)
            std::dynamic_pointer_cast<Sprite>(sprite.second)->update(dt);
    }

    void SpriteLayer::render()
    {
        for (auto sprite : this->_children)
            std::dynamic_pointer_cast<Sprite>(sprite.second)->render();
    }

    SpriteLayer::SpriteLayer(const char* name, unsigned int id, glm::vec3 position, unsigned int textureID, bool updatable)
    {
        this->_type = SPRITE_LAYER;
        this->_name = name;
        this->_layerID = id;
        this->textureID = textureID;
    }
} // namespace ast