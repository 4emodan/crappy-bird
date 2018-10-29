#pragma once

#include "cocos2d.h"
#include "_include/CustomPhysics.h"
#include "_include/GameSettings.h"
#include "_include/Utils.h"

namespace Utils {
    cocos2d::Sprite *
    createColorRectangleSprite(const cocos2d::Size &size, const cocos2d::Color3B &color = cocos2d::Color3B::RED);

//    void debugDrawCollision(Collision collision, cocos2d::Layer *debugLayer);

    cocos2d::Rect pixelsToMeters(const cocos2d::Rect &rect);

    cocos2d::Rect metersToPixels(const cocos2d::Rect &rect);

    cocos2d::Vec2 getRectCenter(const cocos2d::Rect &rect);

    bool intersectsCircle(const cocos2d::Rect &rect, const cocos2d::Rect &circleRect);

    float getRectRadius(const cocos2d::Rect &rect);

    cocos2d::Rect moveRectX(const cocos2d::Rect &rect, float xDelta);

    cocos2d::Rect moveRectY(const cocos2d::Rect &rect, float yDelta);

	std::string toString(ShapeType shapeType);

    template<typename T, typename = std::enable_if<std::is_base_of<PhysicalObject, T>::value>>
    std::shared_ptr<T> getObject(std::multimap<std::string, std::shared_ptr<T>> &collection,
                                 const std::string &layer,
                                 int id) {
        auto range = collection.equal_range(layer);
        for (auto i = range.first; i != range.second; ++i) {
            auto object = i->second;
            if (object->getId() == id) {
                return object;
            }
        }
        return nullptr;
    }

    // TODO find a way to extract find function returning an iterator
    template<typename T, typename = std::enable_if<std::is_base_of<PhysicalObject, T>::value>>
    void removeObject(std::multimap<std::string, std::shared_ptr<T>> &collection,
                      const std::string &layer,
                      int id) {
        auto range = collection.equal_range(layer);
        for (auto i = range.first; i != range.second; ++i) {
            auto object = i->second;
            if (object->getId() == id) {
                collection.erase(i);
                break;
            }
        }
    }

    template<typename T, typename = std::enable_if<std::is_base_of<PhysicalObject, T>::value>>
    static void addObject(std::multimap<std::string, std::shared_ptr<T>> &map,
                          const std::string &layer,
                          const std::shared_ptr<PhysicalObject> &object,
                          std::function<T(std::shared_ptr<PhysicalObject>)> create) {
        map.insert({layer, std::make_shared<T>(create(object))});
    }

    template<typename T, typename = std::enable_if<std::is_base_of<PhysicalObject, T>::value>>
    static std::list<std::shared_ptr<PhysicalObject>> getLayerObjects(
            const std::multimap<std::string, std::shared_ptr<T>> &collection,
            const std::string &layer) {
        auto layerObjects = std::list<std::shared_ptr<PhysicalObject>>();

        auto range = collection.equal_range(layer);
        for (auto i = range.first; i != range.second; ++i) {
            auto object = i->second;
            layerObjects.push_back(std::static_pointer_cast<PhysicalObject>(object));
        }
        return layerObjects;
    }

    template<class Key, class Value>
    std::map<Key, Value> listToMap(std::list<Value> &list, std::function<Key(Value)> &extractKey) {
        auto out = std::map<Key, Value>();
        for (const auto &item: list) {
            out.insert({extractKey(item), item});
        }
        return out;
    }
}