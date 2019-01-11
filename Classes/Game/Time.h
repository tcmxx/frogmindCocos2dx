#pragma once
using namespace std;

///time related. useful for network compensation and prediction/sync related stuff
///ported from Unity FPSSample project
struct GameTime
{
public:

	GameTime(int tickRate);
	GameTime();
	const int GetTickRate() const;
	void SetTickRate(int tickRate);
 	void IncreaseTime(float dt);
	const float GetTickInterval();

	int tick;
	float tickDuration;

private:
	int mTickRate;
	float tickInterval;
};

inline GameTime::GameTime(){
	mTickRate = 60;
	tickInterval = 1.0f / mTickRate;
	tick = 1;
	tickDuration = 0;
}
inline GameTime::GameTime(int tickRate) {
	mTickRate = tickRate;
	tickInterval = 1.0f / mTickRate;
	tick = 1;
	tickDuration = 0;
};

inline const float GameTime::GetTickInterval() {
	return tickInterval;
}

inline const int GameTime::GetTickRate() const {
	return mTickRate;
}

inline void GameTime::SetTickRate(int tickRate) {
	mTickRate = tickRate;
	tickInterval = 1.0f / mTickRate;
}
inline void GameTime::IncreaseTime(float dt){
	tickDuration+=dt;
	if(tickDuration > tickInterval){
		tick++;
		tickDuration -= tickInterval;
	}
}