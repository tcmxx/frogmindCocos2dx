#pragma once

#include "cocos2d.h"
#include "PlayerCommand.h"

USING_NS_CC;


class Explosion : public Node {

public:
	const float MARK_RADIUS = 0.5f;
	static const float EXPLOSION_RADIUS;
	const float EXPLOSION_IMPULSE = 30000000;
	const int LIVE_TICKS = 10;

	void InitializeWithCommand(PlayerCommand command);

	static Explosion* createExplosion();
	void update(float dt) override;

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(Explosion);
protected:

	void Explode();

	bool exploded = false;
	int playerIndex;
	GameTime* time;
	int tickToEffect;
	int tickToDestroy;

	float spriteScale;
	Sprite* spriteChild;
};