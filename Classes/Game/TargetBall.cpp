#include "TargetBall.h"

#include <string>
#include <iostream>

const int TargetBall::DEFAULT_TAG = 2;

TargetBall* TargetBall::createTargetBall(){
    TargetBall* ball = TargetBall::create();
    return ball;
}

bool TargetBall::init() {

	spriteChild = Sprite::create("circleWithDirection.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/64;
	spriteChild->setScale(DEFAULT_RADIUS*spriteScale);
	addChild(spriteChild);

	body = PhysicsBody::createCircle(DEFAULT_RADIUS, PhysicsMaterial(DEFAULT_DENSITY, DEFAULT_RESTITUTION, DEFAULT_FRICTION));
	body->setDynamic(true);
	addComponent(body);

	body->setAngularDamping(0.1f);
	body->setLinearDamping(0.15f);
    body->setContactTestBitmask(0xFFFFFFFF);
    setTag(DEFAULT_TAG);
	return true;
}
