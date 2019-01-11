#pragma once
#include <string>
#include "cocos2d.h"
#include <list> 
#include <map>
#include "Time.h"

using namespace std;
USING_NS_CC;
//player command that can be sent for networking
//It is for deterministic simulation so that each client can simulate the game only based on player inputs while keep sync
//the actual command time is the use tick and effecting time should be delayed to overcome the network latency




class PlayerCommand {
public:
	int useTick;
	int effectDelay;
	string name;

	Vec2 usePosition;
	Vec2 useDirection;
	int playerIndex;
};

class PlayerCommandExecuter {
public:
	//parse the command and use it
	virtual void ExecuteCommand(PlayerCommand command) = 0;
	virtual string GetCommandName() = 0;
};

///This is used to enqueue player command and execute them.
///This seems useless now,but it can be modified to support networking;
class PlayerCommandController {
public:
	PlayerCommandController(GameTime* time);
	PlayerCommandController();
	~PlayerCommandController();

	void SetTime(GameTime* time);
	void AddExecuter(PlayerCommandExecuter* executer);

	void EnqueueCommand(PlayerCommand command);

	void ExecuteCommands();
private:
	GameTime* time;
	list<PlayerCommand> commands;
	map<string, PlayerCommandExecuter*> executers;
};

inline void PlayerCommandController::SetTime(GameTime* gameTime){
	time = gameTime;
}