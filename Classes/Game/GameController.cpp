#include "GameController.h"

#include "TargetBall.h"
#include "GameScene.h"

GameController* GameController::instance;




void GameController::AddPlayerPoint(bool isPlayerOne) {
	if (isPlayerOne) {
		playerOnePoint++;
	}
	else {
		playerTwoPoint++;
	}
}

int GameController::GetPlayerPoint(int index) {
	if (index == 0) {
		return playerOnePoint;
	}
	else {
		return playerTwoPoint;
	}
}


bool GameController::init(){
	instance = this;
	commandController.SetTime(GameScene::getInstance()->GetTime());
	scheduleUpdate();
	return true;
}

void GameController::update(float deltaTime) {

	if (playerOneMana < MAX_MANA) {
		playerOneMana += deltaTime * MANA_REGEN_RATE;
	}
	if (playerTwoMana < MAX_MANA) {
		playerTwoMana += deltaTime * MANA_REGEN_RATE;
	}
	commandController.ExecuteCommands();
}

void GameController::RegisterAbility(Ability* ability) {
	commandController.AddExecuter(ability);
}

void GameController::UseAbility(Ability* ability, Vec2 position, int playerIndex) {
	commandController.EnqueueCommand(ability->GenerateCommand(position, playerIndex));
}