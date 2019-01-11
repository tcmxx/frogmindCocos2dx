#pragma once

#include "cocos2d.h"
#include "PlayerCommand.h"
USING_NS_CC;

class SmallCube : public Node {

public:
	const float DEFAULT_RESTITUTION = 0.1f;
	const float DEFAULT_DENSITY = 25.0f;
	const float DEFAULT_FRICTION = 0.5f;
	const Size DEFAULT_SIZE = Size(1, 1);
	const int LIVE_TICKS = 800;



	void InitializeWithCommand(PlayerCommand command);

    static SmallCube* createSmallCube();
	void update(float dt) override;

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(SmallCube);

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