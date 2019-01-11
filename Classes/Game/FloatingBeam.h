#pragma once

#include "cocos2d.h"
#include "PlayerCommand.h"
USING_NS_CC;

class FloatingBeam : public Node {

public:
	const float DEFAULT_RESTITUTION = 0.5f;
	const float DEFAULT_DENSITY = 2.0f;
	const float DEFAULT_FRICTION = 0.5f;
	const Size DEFAULT_SIZE = Size(6,1.0f);
	const float DEFAULT_ANGLE = -15.0f;
	const int LIVE_TICKS = 800;

	void InitializeWithCommand(PlayerCommand command);

	static FloatingBeam* createFloatingBeam();
	void update(float dt) override;

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(FloatingBeam);
protected:

	void AddPhysics();

	int playerIndex;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;

	bool hasPhysics = false;

	float spriteScale;
	Sprite* spriteChild;
	PhysicsBody* body;
};