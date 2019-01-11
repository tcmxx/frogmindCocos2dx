#include "Explosion.h"
#include "GameScene.h"
#include <string>
#include <iostream>

Explosion* Explosion::createExplosion(){
	Explosion* ball = Explosion::create();
	ball->spriteChild->setScale(ball->MARK_RADIUS*ball->spriteScale);
	return ball;
}


bool Explosion::init() {

	scheduleUpdate();

	time = GameScene::getInstance()->GetTime();

	spriteChild = Sprite::create("circleWithDirection.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/64;
	addChild(spriteChild);

	return true;
}

void Explosion::InitializeWithCommand(PlayerCommand command) {
	setPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;
}


void Explosion::Explode() {
	if (exploded)
		return;
	exploded = true;
	spriteChild->setScale(EXPLOSION_RADIUS*spriteScale);

	//here we use rect instead of circle because the reimpelmentation takes extra time
	auto physicsWorld = GameScene::getInstance()->getPhysicsWorld();

	//query function

	auto func = [this](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
	{
		auto body = shape.getBody();
		if(body != nullptr && body->isDynamic()){
			Vec2 mCenter = this->getPosition();
			Vec2 center = body->getNode()->getPosition();

            //auto testSprite = Sprite::create("circleWithDirection.png");
            //testSprite->setPosition(center);
			//testSprite->setScale(0.01f);
            //GameScene::getInstance()->getGameObjectRootNode()->addChild(testSprite);

			auto dir = (center - mCenter);
            //dir = Vec2(-1,0);
			dir.normalize();
			dir.x *= EXPLOSION_IMPULSE;
			dir.y *= EXPLOSION_IMPULSE;
			dir = dir.rotateByAngle(Vec2(0,0),body->getNode()->getRotation()/180*3.14159f); //it is very weird that the impulse is not in global coordinate, and rotation/rotationbyangle is not in the same unit!!
			body->applyForce(dir,Vec2(0,0));
		}
		//Return true from the callback to continue rect queries
		return true;
	};

	Vec2 pos = GameScene::getInstance()->worldPosToPhysicsPos(getPosition() - Vec2(EXPLOSION_RADIUS,EXPLOSION_RADIUS));
	physicsWorld->queryRect(func, Rect(pos.x,pos.y,EXPLOSION_RADIUS*2*GameScene::CAMERA_SCALE,EXPLOSION_RADIUS*2*GameScene::CAMERA_SCALE),nullptr);

}



void Explosion::update(float deltaTime) {
	if (time->tick == tickToEffect) {
		Explode();
	}
	if (time->tick == tickToDestroy) {
		removeFromParent();
	}
}
