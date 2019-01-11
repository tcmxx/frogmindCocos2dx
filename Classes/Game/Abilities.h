#pragma once
#include "cocos2d.h"
#include "PlayerCommand.h"

/// An axis aligned bounding box.
//copied from Box2D library
struct b2AABB
{
    /// Verify that the bounds are sorted.
    bool IsValid() const;

    /// Get the center of the AABB.
    Vec2 GetCenter() const
    {
        return 0.5f * (lowerBound + upperBound);
    }

    /// Get the extents of the AABB (half-widths).
    Vec2 GetExtents() const
    {
        return 0.5f * (upperBound - lowerBound);
    }

    /// Get the perimeter length
    float GetPerimeter() const
    {
        float wx = upperBound.x - lowerBound.x;
        float wy = upperBound.y - lowerBound.y;
        return 2.0f * (wx + wy);
    }
    /// Does this aabb contain the provided AABB.
    bool Contains(const b2AABB& aabb) const
    {
        bool result = true;
        result = result && lowerBound.x <= aabb.lowerBound.x;
        result = result && lowerBound.y <= aabb.lowerBound.y;
        result = result && aabb.upperBound.x <= upperBound.x;
        result = result && aabb.upperBound.y <= upperBound.y;
        return result;
    }

    Vec2 lowerBound;	///< the lower vertex
    Vec2 upperBound;	///< the upper vertex
};
inline bool b2AABB::IsValid() const
{
    Vec2 d = upperBound - lowerBound;
    bool valid = d.x >= 0.0f && d.y >= 0.0f;
    return valid;
}



class Ability:public PlayerCommandExecuter {
public:
	virtual b2AABB GetRange(int playeIndex) = 0;

	virtual PlayerCommand GenerateCommand(Vec2 position, int playeIndex) = 0;
	virtual void ExecuteCommand(PlayerCommand command) = 0 ;
	virtual string GetCommandName() = 0;
	virtual float GetCoolDownTime() = 0;
	virtual int GetManaCost() = 0;

	virtual string GetAbilityName() = 0;
};


class AbilityLargeBall :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex)override ;
	virtual PlayerCommand GenerateCommand(Vec2 position, int playeIndex)override ;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual float GetCoolDownTime() override  {return COOLDOWN_TICK;};
	virtual int GetManaCost() override  {return MANACOST;};
	virtual string GetAbilityName() override { return ABILITY_NAME; };
private:
	const int MANACOST = 4;	//not used yet
	const float COOLDOWN_TICK = 10;
	const int DELAY_TICK = 50;
	const string NAME = "AbilityLargeBall";
	const string ABILITY_NAME = "Large Ball";
};

class AbilityFloatingBeam :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex) override ;
	virtual PlayerCommand GenerateCommand(Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual float GetCoolDownTime() override  { return COOLDOWN_TICK; };
	virtual int GetManaCost() override  { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 4;
	const float COOLDOWN_TICK = 10;
	const int DELAY_TICK = 50;
	const string NAME = "AbilityFloatingBeam";
	const string ABILITY_NAME = "Floating Beam";
};


class AbilitySmallCube :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex) override ;
	virtual PlayerCommand GenerateCommand(Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual float GetCoolDownTime() override  { return COOLDOWN_TICK; };
	virtual int GetManaCost() override  { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 1;
	const float COOLDOWN_TICK = 12;
	const int DELAY_TICK = 50;
	const string NAME = "AbilitySmallCube";
	const string ABILITY_NAME = "Small Cube";
};


class AbilityExplosion :public Ability {
public:
	virtual b2AABB GetRange(int playeIndex) override ;
	virtual PlayerCommand GenerateCommand(Vec2 position, int playeIndex)override;
	virtual void ExecuteCommand(PlayerCommand command) override;
	virtual string GetCommandName() override { return NAME; };
	virtual float GetCoolDownTime() override  { return COOLDOWN_TICK; };
	virtual int GetManaCost() override  { return MANACOST; };
	virtual string GetAbilityName() override { return ABILITY_NAME; };

private:
	const int MANACOST = 4;
	const float COOLDOWN_TICK = 4;
	const int DELAY_TICK = 50;
	const string NAME = "Explosion";
	const string ABILITY_NAME = "Explosion";
};