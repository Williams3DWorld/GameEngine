#ifndef __LAYER_HELPER_H__
#define __LAYER_HELPER_H__

#include "../game-objects/spriteLayer.hpp"
#include "../../scene/structs/MapObjectData.hpp"
#include "../../core/utils/tmx/tiled-map.hpp"

namespace ast
{
    class LayerHelper
    {
    public:
        static std::shared_ptr<ast::SpriteLayer> createSpriteLayerFromTiledLayer(ast::TiledLayer& tilelayer);
        
        static std::vector<ast::CollisionRectangle> createCollisionDataFromTiledLayer(ast::TiledMap& tilemap);
        static std::vector<std::shared_ptr<ast::SpriteLayer>> createSpriteLayersFromTiledMap(ast::TiledMap& tilemap);
    };
}

#endif