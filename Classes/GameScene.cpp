//
// Created by tcmxx on 2019/1/9.
//

#include "GameScene.h"
#include "Game/StaticWall.h"
#include "Game/TargetBall.h"
#include "Game/TargetSpawner.h"
#include "Game/Basket.h"
#include "Game/GameplayUI.h"
#include "Game/GameController.h"

USING_NS_CC;


GameScene* GameScene::instance;
const float GameScene::CAMERA_SCALE = 10;
Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //initialize physics
    if( !Scene::initWithPhysics() )
    {

    }
    gameTime.SetTickRate(60);
    instance = this;
    //schedule the update
    scheduleUpdate();

    //root
    gameObjectRootNode = Node::create();
    addChild(gameObjectRootNode);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    gameObjectRootNode->setPosition(Vec2(origin.x + visibleSize.width/2,
                                         origin.y + visibleSize.height/2-8*CAMERA_SCALE));
    gameObjectRootNode->setScale(CAMERA_SCALE);


    //add game controller. This needs to be created first
    auto controller = GameController::create();
    addChild(controller);

    //add ui
    auto ui = GameplayUI::create();
    addChild(ui,10);

    //add other objects
    addGameObjects();

    //add the b2 debug draw layer
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    getPhysicsWorld()->setGravity(Vec2(0,-100));

    /////////////////////////////
    // setup the ccamera
   Camera* camera = getDefaultCamera();
    camera->createOrthographic(100,100,1,1000);



    return true;
}



void GameScene::update(float dt){
    //note that the udpate is not fixed timestep so this is useless. only to do it so that I dont ahve to change the code too much
    gameTime.IncreaseTime(dt);
}


void GameScene::addGameObjects(){

    //walls
    //grounds
    auto wallSize = Size(40,2);
    StaticWall* wall = StaticWall::createWall(wallSize);
    wall->setPosition(0,0);
    gameObjectRootNode->addChild(wall);

    wall = StaticWall::createWall(wallSize);
    wall->setPosition(-45,0);
    gameObjectRootNode->addChild(wall);

    wall = StaticWall::createWall(wallSize);
    wall->setPosition(45,0);
    gameObjectRootNode->addChild(wall);

    //side walls
    wallSize = Size(2,20);
    wall = StaticWall::createWall(wallSize);
    wall->setPosition(-28,10);
    gameObjectRootNode->addChild(wall);

    wall = StaticWall::createWall(wallSize);
    wall->setPosition(28,10);
    gameObjectRootNode->addChild(wall);

    //add player baskets
    auto basket = Basket::createBasket(Size(4,2), true, Color3B(0,255,0));
    basket->setPosition(Vec2(-22.5,-4));
    gameObjectRootNode->addChild(basket);

    basket = Basket::createBasket(Size(4,2), false, Color3B(0,0,255));
    basket->setPosition(Vec2(22.5,-4));
    gameObjectRootNode->addChild(basket);

    ///game logit related
    // target spawner
    TargetSpawner* spawner = TargetSpawner::createTargetSpawner();
    gameObjectRootNode->addChild(spawner);

}

Vec2 GameScene::screenPosToWorldPos(Vec2 screenPos){
    return (screenPos - gameObjectRootNode->getPosition())/CAMERA_SCALE;
}

Vec2 GameScene::worldPosToPhysicsPos(Vec2 worldPos){
    return (worldPos*CAMERA_SCALE + gameObjectRootNode->getPosition());
}