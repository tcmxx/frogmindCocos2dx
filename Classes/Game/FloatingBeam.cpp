#include "FloatingBeam.h"
#include "GameScene.h"

#include <string>
#include <iostream>


FloatingBeam* FloatingBeam::createFloatingBeam(){
	FloatingBeam* beam = FloatingBeam::create();
	beam->spriteChild->setScale(beam->DEFAULT_SIZE.width*beam->spriteScale,beam->DEFAULT_SIZE.height*beam->spriteScale);
	return beam;
}

bool FloatingBeam::init() {
	scheduleUpdate();

	time = GameScene::getInstance()->GetTime();

	spriteChild = Sprite::create("square.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/128;
	addChild(spriteChild);

	return true;
}

void FloatingBeam::InitializeWithCommand(PlayerCommand command) {
	setPosition(command.usePosition);
	tickToEffect = command.effectDelay + command.useTick;
	tickToDestroy = tickToEffect + LIVE_TICKS;
	playerIndex = command.playerIndex;

	setRotation(playerIndex == 0 ? DEFAULT_ANGLE : -DEFAULT_ANGLE);
    spriteChild->setRotation(playerIndex == 0 ? DEFAULT_ANGLE : -DEFAULT_ANGLE);

    spriteChild->setColor(playerIndex == 0?Color3B(0,255,0):Color3B(0,0,255));
}


void FloatingBeam::AddPhysics() {
	if (hasPhysics)
		return;
	hasPhysics = true;

	body = PhysicsBody::createBox(DEFAULT_SIZE, PhysicsMaterial(DEFAULT_DENSITY, DEFAULT_RESTITUTION, DEFAULT_FRICTION));
	body->setDynamic(false);
	addComponent(body);

	body->setAngularDamping(0.1f);
	body->setLinearDamping(0.5f);
}


void FloatingBeam::update(float deltaTime) {
	if (time->tick == tickToEffect) {
		AddPhysics();
	}
	if (time->tick == tickToDestroy) {
		removeFromParent();
	}
}

