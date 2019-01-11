#pragma once

#include "cocos2d.h"

USING_NS_CC;


class TargetBall : public Node {

public :
	const float DEFAULT_RADIUS = 2.0f;
	const float DEFAULT_RESTITUTION = 0.5f;
	const float DEFAULT_DENSITY = 2.0f;
	const float DEFAULT_FRICTION =0.5f;
    const static int DEFAULT_TAG;
	static TargetBall* createTargetBall();
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TargetBall);

protected:
	float spriteScale;
	Sprite* spriteChild;
	PhysicsBody* body;
};