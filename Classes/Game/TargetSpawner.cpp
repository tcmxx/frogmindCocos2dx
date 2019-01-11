#include "TargetSpawner.h"

#include "GameScene.h"
#include "TargetBall.h"

TargetSpawner* TargetSpawner::instance;

TargetSpawner* TargetSpawner::createTargetSpawner(){
	TargetSpawner* spawner = TargetSpawner::create();
	return spawner;
}

bool TargetSpawner::init() {
	scheduleUpdate();
	instance = this;

	countDownTimer = initialDelay;
	return true;
}

void TargetSpawner::update(float deltaTime) {
	countDownTimer -= deltaTime;
	if (countDownTimer <= 0) {
		countDownTimer = spawnInterval;
		TargetBall* ball = TargetBall::createTargetBall();
		GameScene::getInstance()->getGameObjectRootNode()->addChild(ball);
		ball->setPosition(spawnPosition);
	}
	
}
