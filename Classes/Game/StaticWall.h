#pragma once

#include "cocos2d.h"
USING_NS_CC;


class StaticWall : public Node {

public:
	static StaticWall* createWall(Size size, float restitution=0.5f, float friction = 0.6f);
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(StaticWall);


protected:

    float spriteScale;
	Sprite* spriteChild;
	PhysicsBody* body;
};