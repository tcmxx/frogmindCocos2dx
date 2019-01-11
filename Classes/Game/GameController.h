#pragma once

#include "cocos2d.h"
#include "PlayerCommand.h"
#include "Abilities.h"
USING_NS_CC;

class GameController : public Node {
	
public:
	static GameController*  GetInstance();

	void AddPlayerPoint(bool isPlayerOne);
	int GetPlayerPoint(int index);

	void RegisterAbility(Ability* ability);
	void UseAbility(Ability* ability, Vec2 position, int playerIndex);



	///----------------callbacks-------------
	void update(float dt) override;

	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(GameController);
	///-----------------------------------

	//just make those public to save my time...
	float playerOneMana = 3;
	float playerTwoMana = 3;

	const float MAX_MANA = 10;
private:
	static GameController* instance;

	PlayerCommandController commandController;

	int playerOnePoint = 0;
	int playerTwoPoint = 0;


	const float MANA_REGEN_RATE = 0.7f;
};

inline GameController*  GameController::GetInstance() {
	return instance;
}