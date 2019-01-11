#pragma once

#include "cocos2d.h"
#include "Abilities.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace std;

class AbilityButton: public Node{
public:

    static AbilityButton* createAbilityButton(Ability* ability, Size size, int playerIndex);
	void StartPreparing();
    void StopPreparing();
    void TryUseAtOrCancel(const Vec2& touchPosition);
	void Use(const Vec2& position);
    void UpdateAbilityIndicator(const Vec2& touchPosition);
    void update(float dt) override;



    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(AbilityButton);

private:
	bool ManaEnough();

	static bool isInUse1;
	static bool isInUse2;

	bool isPreparing = false;
	float cooldownTimer = 0;

	Ability* mAbility;
	int mPlayerIndex;

	b2AABB range;

    //Vec2 touchPositoin;

	float buttonScale;
	ui::Button* buttonChild;
    Sprite* rangeSprite;
    Label* manaCostLabel;


};

class GameplayUI : public Node {

public:

    void update(float dt) override;

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(GameplayUI);

private:

	const Size CARD_BUTTON_SIZE = Size(80, 80);

	///----------------a bunch of abilities-------------------
	AbilityLargeBall abilityLargeBall;
	AbilityFloatingBeam abiliityFloatingBeam;
	AbilitySmallCube abilitySmallCube;
	AbilityExplosion abilityExplosion;
	///-----------------------------------------------------
	//AbilityButton *button11, *button12, *button13, *button14;
	//AbilityButton *button21, *button22, *button23, *button24;
    Label* scoreLabel;

    Sprite* manaBarPlayer1;
    Sprite* manaBarPlayer2;

    Label* manaLabelPlayer1;
    Label* manaLabelPlayer2;
};

