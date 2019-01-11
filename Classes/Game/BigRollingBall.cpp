#include "BigRollingBall.h"
#include "GameScene.h"
#include <string>
#include <iostream>




const float BigRollingBall::DEFAULT_RADIUS = 3.0f;

BigRollingBall* BigRollingBall::createBigRollingBall(){
	BigRollingBall* ball = BigRollingBall::create();
	ball->spriteChild->setScale(ball->DEFAULT_RADIUS*ball->spriteScale);
	return ball;
}

bool BigRollingBall::init() {

	scheduleUpdate();

	time = GameScene::getInstance()->GetTime();

	spriteChild = Sprite::create("circleWithDirection.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/64;
	addChild(spriteChild);

	return true;
}
void BigRollingBall::InitializeWithCommand(PlayerCommand command) {
	setPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;

    spriteChild->setColor(playerIndex == 0?Color3B(0,255,0):Color3B(0,0,255));
    spriteChild->setOpacity(55);
}


void BigRollingBall::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;

	body = PhysicsBody::createCircle(DEFAULT_RADIUS, PhysicsMaterial(DEFAULT_DENSITY, DEFAULT_RESTITUTION, DEFAULT_FRICTION));
	body->setDynamic(true);
	addComponent(body);

	body->setAngularDamping(0.1f);
	body->setLinearDamping(0.5f);

    spriteChild->setOpacity(255);
}


void BigRollingBall::update(float deltaTime) {
	if (time->tick >=tickToEffect) {
		AddPhysics();
	}
	if (playerIndex == 0) {
		if (hasPhysics) {
			body->applyTorque(-ROTATION_TORQUE);
		}
	}
	else {
		if (hasPhysics) {
			body->applyTorque(ROTATION_TORQUE);
		}
	}


	if (time->tick >= tickToDestroy) {
		removeFromParent();
	}


}


