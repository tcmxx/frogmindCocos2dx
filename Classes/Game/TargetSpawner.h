#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TargetSpawner : public Node {

public:
	static TargetSpawner*  GetInstance();

	static TargetSpawner* createTargetSpawner();
	void update(float dt) override;

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(TargetSpawner);


	float initialDelay = 3;
	float spawnInterval = 10;
	Vec2 spawnPosition = Vec2(0,35);
private:
	static TargetSpawner* instance;
	float countDownTimer;
};

inline TargetSpawner*  TargetSpawner::GetInstance() {
	return instance;
}