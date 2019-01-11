//
// Created by tcmxx on 2019/1/9.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include "Game/Time.h"

USING_NS_CC;

class GameScene  : public Scene{
public:
    static Scene* createScene();
    static GameScene* getInstance();
    GameTime* GetTime();
    Node* getGameObjectRootNode();
    virtual bool init();
    void update(float dt) override;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void addGameObjects();

    Vec2 screenPosToWorldPos(Vec2 screenPos);
    Vec2 worldPosToPhysicsPos(Vec2 worldPos);

    static const float CAMERA_SCALE;
protected:
    static GameScene* instance;

    Node* gameObjectRootNode;
    GameTime gameTime;
};

inline GameScene*  GameScene::getInstance() {
    return instance;
}
inline GameTime* GameScene::GetTime(){
    return &gameTime;
}
inline Node* GameScene::getGameObjectRootNode(){
    return gameObjectRootNode;
}

#endif //PROJ_ANDROID_GAMESCENE_H
