#include "PlayerCommand.h"






PlayerCommandController::PlayerCommandController(GameTime* time):time(time) {
}

PlayerCommandController::PlayerCommandController(){

}


PlayerCommandController::~PlayerCommandController() {

}

void PlayerCommandController::AddExecuter(PlayerCommandExecuter* executer) {
	executers[executer->GetCommandName()] = executer;
}

void PlayerCommandController::EnqueueCommand(PlayerCommand command) {
	//for networking, the command might be modified and sent to the other client
	commands.push_back(command);
}

void PlayerCommandController::ExecuteCommands() {
	//right now just execeute all commands that has a tick time smaller or equal than now
	//for networking, we might want to remove commands that are too late to be effective and
	//inform the other clients

	std::list<PlayerCommand>::iterator i = commands.begin();
	while (i != commands.end())
	{
		bool execute = (*i).useTick <= time->tick;
		if (!execute)
		{
			++i;
		}
		else
		{
			PlayerCommandExecuter* executer= executers[(*i).name];
			if (executer != nullptr) {
				executer->ExecuteCommand((*i));
			}
			i = commands.erase(i);
		}
	}
}