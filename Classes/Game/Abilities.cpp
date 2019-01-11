#include "Abilities.h"
#include "BigRollingBall.h"
#include "GameController.h"
#include "FloatingBeam.h"
#include "SmallCube.h"
#include "Explosion.h"
#include "GameScene.h"




Ability::Ability(string indicatorSpriteName){
	indicatorSprite = Sprite::create(indicatorSpriteName);
	indicatorSprite->setVisible(false);
    GameScene::getInstance()->getGameObjectRootNode()->addChild(indicatorSprite);
}



///-------------------Ability Large Ball--------------------------

AbilityLargeBall::AbilityLargeBall():Ability("largeBallIndicator.png"){
    float scale = Director::getInstance()->getContentScaleFactor()/64;
    indicatorSprite->setScale(BigRollingBall::DEFAULT_RADIUS*scale);
}

b2AABB AbilityLargeBall::GetRange(int playeIndex) {
	b2AABB aabb;
	if (playeIndex == 0) {
		aabb.lowerBound = Vec2(-20, 0);
		aabb.upperBound = Vec2(5, 25);
	}
	else {
		aabb.lowerBound = Vec2(-5, 0);
		aabb.upperBound = Vec2(20, 25);
	}
	return aabb;
}
PlayerCommand AbilityLargeBall::GenerateCommand(Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = GameScene::getInstance()->GetTime()->tick;
	return command;
};
void AbilityLargeBall::ExecuteCommand(PlayerCommand command) {
    BigRollingBall* ball = BigRollingBall::createBigRollingBall();
    GameScene::getInstance()->getGameObjectRootNode()->addChild(ball);
    ball->setPosition(command.usePosition);
	ball->InitializeWithCommand(command);
};
///-----------------------------------------------------------------


///-------------------Ability Beam--------------------------

AbilityFloatingBeam::AbilityFloatingBeam():Ability("floatingBeamIndicator.png"){
    float scale = Director::getInstance()->getContentScaleFactor()/128;
    indicatorSprite->setScale(FloatingBeam::DEFAULT_SIZE.width*scale,FloatingBeam::DEFAULT_SIZE.height*scale);
}

b2AABB AbilityFloatingBeam::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = Vec2(-20, -10);
	aabb.upperBound = Vec2(20, 40);
	return aabb;
}
PlayerCommand AbilityFloatingBeam::GenerateCommand(Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = GameScene::getInstance()->GetTime()->tick;
	return command;
};
void AbilityFloatingBeam::ExecuteCommand(PlayerCommand command) {
    FloatingBeam* beam = FloatingBeam::createFloatingBeam();
    GameScene::getInstance()->getGameObjectRootNode()->addChild(beam);
    beam->setPosition(command.usePosition);
	beam->InitializeWithCommand(command);
};
///-----------------------------------------------------------------



///-------------------Ability Small Cube--------------------------
AbilitySmallCube::AbilitySmallCube():Ability("smallCubeIndicator.png"){
    float scale = Director::getInstance()->getContentScaleFactor()/128;
    indicatorSprite->setScale(SmallCube::DEFAULT_SIZE.width*scale,SmallCube::DEFAULT_SIZE.height*scale);
}

b2AABB AbilitySmallCube::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = Vec2(-30, 20);
	aabb.upperBound = Vec2(30, 40);
	return aabb;
}
PlayerCommand AbilitySmallCube::GenerateCommand(Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = GameScene::getInstance()->GetTime()->tick;
	return command;
};
void AbilitySmallCube::ExecuteCommand(PlayerCommand command) {
    SmallCube* cube = SmallCube::createSmallCube();
    GameScene::getInstance()->getGameObjectRootNode()->addChild(cube);
    cube->setPosition(command.usePosition);

	cube->InitializeWithCommand(command);
};
///-----------------------------------------------------------------

///-------------------Ability Explosion--------------------------
AbilityExplosion::AbilityExplosion():Ability("explosionIndicator.png"){
	float scale = Director::getInstance()->getContentScaleFactor()/64;
	indicatorSprite->setScale(Explosion::EXPLOSION_RADIUS*scale);
}

b2AABB AbilityExplosion::GetRange(int playeIndex) {
	b2AABB aabb;
	aabb.lowerBound = Vec2(-30, -10);
	aabb.upperBound = Vec2(30, 40);
	return aabb;
}
PlayerCommand AbilityExplosion::GenerateCommand(Vec2 position, int playeIndex) {
	PlayerCommand command;
	command.effectDelay = DELAY_TICK;
	command.name = NAME;
	command.usePosition = position;
	command.playerIndex = playeIndex;
	command.useTick = GameScene::getInstance()->GetTime()->tick;
	return command;
};
void AbilityExplosion::ExecuteCommand(PlayerCommand command) {
    Explosion* exp = Explosion::createExplosion();
    GameScene::getInstance()->getGameObjectRootNode()->addChild(exp);
    exp->setPosition(command.usePosition);
	exp->InitializeWithCommand(command);
};
///-----------------------------------------------------------------
