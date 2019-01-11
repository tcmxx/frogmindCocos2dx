#pragma once

#include "cocos2d.h"
#include "PlayerCommand.h"

USING_NS_CC;

class BigRollingBall : public Node {

public :
	static const float DEFAULT_RADIUS;
	const float DEFAULT_RESTITUTION = 0.5f;
	const float DEFAULT_DENSITY = 2.0f;
	const float DEFAULT_FRICTION =0.5f;
	const int LIVE_TICKS = 1200;
	const int ROTATION_TORQUE = 5000000;

	void InitializeWithCommand(PlayerCommand command);

	static BigRollingBall* createBigRollingBall();
	void update(float dt) override;

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(BigRollingBall);
protected:

	void AddPhysics();

	int playerIndex;
	bool hasPhysics = false;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;

	float spriteScale;
	Sprite* spriteChild;
	PhysicsBody* body;
};


