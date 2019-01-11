#include "SmallCube.h"
#include "GameScene.h"

#include <string>
#include <iostream>

const Size SmallCube::DEFAULT_SIZE = Size(1, 1);

SmallCube* SmallCube::createSmallCube(){
	SmallCube* cube = SmallCube::create();
    cube->spriteChild->setScale(cube->DEFAULT_SIZE.width*cube->spriteScale,cube->DEFAULT_SIZE.height*cube->spriteScale);

	return cube;
}
bool SmallCube::init() {

	scheduleUpdate();

	time = GameScene::getInstance()->GetTime();

	spriteChild = Sprite::create("square.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/128;
	addChild(spriteChild);

	return true;
}

void SmallCube::InitializeWithCommand(PlayerCommand command) {
	setPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;

	spriteChild->setColor(playerIndex == 0?Color3B(0,255,0):Color3B(0,0,255));
	spriteChild->setOpacity(55);
}


void SmallCube::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;

	body = PhysicsBody::createBox(DEFAULT_SIZE, PhysicsMaterial(DEFAULT_DENSITY, DEFAULT_RESTITUTION, DEFAULT_FRICTION));
	body->setDynamic(true);
	addComponent(body);

	body->setAngularDamping(0.1f);
	body->setLinearDamping(0.5f);

	spriteChild->setOpacity(255);
}



void SmallCube::update(float deltaTime) {
	if (time->tick >= tickToEffect) {
		AddPhysics();
	}
	if (time->tick >= tickToDestroy) {
		removeFromParent();
	}
}

