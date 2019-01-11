#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Basket : public Node {

public:
	static Basket* createBasket(Size size, bool isPlayerOne, Color3B color, float restitution=0.5f, float friction = 0.5f);
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Basket);

    bool onContactBegin(PhysicsContact& contact);
protected:
	bool isPlayerOne;

    float spriteScale;
    Sprite* spriteChild;
    PhysicsBody* body;
};