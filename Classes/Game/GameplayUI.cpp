#include "GameplayUI.h"
#include "GameController.h"
#include "GameScene.h"
#include <string> 

bool AbilityButton::isInUse1 = false;
bool AbilityButton::isInUse2 = false;

AbilityButton* AbilityButton::createAbilityButton(Ability* ability, Size size, int playerIndex){

    AbilityButton* button = AbilityButton::create();

    button->mAbility = ability;
    button->mPlayerIndex = playerIndex;

    button->buttonChild->setTitleText(ability->GetAbilityName());
	GameController::GetInstance()->RegisterAbility(ability);

    button->buttonChild->setScale(size.width*button->buttonScale,size.height*button->buttonScale);

    //create the range sprite
    button->rangeSprite = Sprite::create("square.png");
    button->rangeSprite->setPosition(ability->GetRange(playerIndex).GetCenter());
    auto rangeSize = ability->GetRange(playerIndex).GetExtents();
    float scale = Director::getInstance()->getContentScaleFactor()/128;
    button->rangeSprite->setScale( rangeSize.x*2* scale, rangeSize.y*2 * scale);

    button->rangeSprite->setOpacity(60);
    button->rangeSprite->setColor(playerIndex == 0?Color3B(0,255,0):Color3B(0,0,255));
    GameScene::getInstance()->getGameObjectRootNode()->addChild(button->rangeSprite);

    button->rangeSprite->setVisible(false);

    return button;
}


bool AbilityButton::init(){
    scheduleUpdate();

    buttonChild = ui::Button::create("abilityButton.png");
    buttonScale = Director::getInstance()->getContentScaleFactor()/128;
    buttonChild->setTitleColor(Color3B(0,0,0));
    buttonChild->setTitleFontSize(18);
    addChild(buttonChild);

    buttonChild->addClickEventListener([&](Ref* sender){
        OnClicked();
    });

    buttonChild->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:

                break;
            default:
                break;
        }
    });


    //register the general touch listener
    auto listener1 = EventListenerTouchOneByOne::create();
    // trigger when you push down
    listener1->onTouchBegan = [this](Touch* touch, Event* event){
        if(this->isPreparing){

            //this->Use(GameScene::getInstance()->screenPosToWorldPos(touch->getLocation()));
            return true;
        }
        return false; // if you are consuming it
    };

    // trigger when moving touch
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        // your code
        return false; // if you are consuming it
    };

    // trigger when you let up
    listener1->onTouchEnded = [this](Touch* touch, Event* event){
        // your code
        if(this->isPreparing){
            auto position = GameScene::getInstance()->screenPosToWorldPos(touch->getLocation());
            if (range.lowerBound.x < position.x && range.lowerBound.y < position.y
                &&range.upperBound.x > position.x && range.upperBound.y > position.y) {
                this->Use(position);
                return true;
            }
        }
        return false; // if you are consuming it
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}

void AbilityButton::OnClicked(){
    bool inUse = (mPlayerIndex == 0 ? isInUse1 : isInUse2);
    if (cooldownTimer <= 0 && !isPreparing && !inUse) {
        isPreparing = true;
        rangeSprite->setVisible(true);

        range = mAbility->GetRange(mPlayerIndex);
        if (mPlayerIndex == 0) {
            isInUse1 = true;
        }
        else {
            isInUse2 = true;
        }
    }
    else if (cooldownTimer <= 0 && isPreparing) {
        isPreparing = false;
        rangeSprite->setVisible(false);
        if (mPlayerIndex == 0) {
            isInUse1 = false;
        }
        else {
            isInUse2 = false;
        }
    }
}


void AbilityButton::update(float deltaTime) {
	if (cooldownTimer > 0)
		cooldownTimer-= deltaTime;

    if(isPreparing){

    }

    if (cooldownTimer > 0) {
        buttonChild->setTitleText(std::to_string(cooldownTimer));
    }else{
        buttonChild->setTitleText(mAbility->GetAbilityName());
    }

    if(!ManaEnough()){
        buttonChild->setColor(Color3B(55,55,55));
    }else{
        buttonChild->setColor(Color3B(255,255,255));
    }
}

void AbilityButton::Use(const Vec2& position) {
	cooldownTimer = mAbility->GetCoolDownTime();
	isPreparing = false;
    rangeSprite->setVisible(false);
	GameController::GetInstance()->UseAbility(mAbility, position, mPlayerIndex);
	if (mPlayerIndex == 0) {
		isInUse1 = false;
		GameController::GetInstance()->playerOneMana -= mAbility->GetManaCost();
	}
	else {
		isInUse2 = false;
		GameController::GetInstance()->playerTwoMana -= mAbility->GetManaCost();
	}
}

bool AbilityButton::ManaEnough() {
	if (mPlayerIndex == 0) {
		return mAbility->GetManaCost() <= GameController::GetInstance()->playerOneMana;
	}
	else {
		return mAbility->GetManaCost() <= GameController::GetInstance()->playerTwoMana;
	}
}






bool GameplayUI::init() {
    scheduleUpdate();

    // score label
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    scoreLabel = Label::createWithTTF("00 : 00", "fonts/Marker Felt.ttf", 28);
    if (scoreLabel == nullptr)
    {
    }
    else
    {
        // position the label on the center of the screen
        scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                     origin.y + visibleSize.height - scoreLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(scoreLabel, 1);
    }

    //mana bars
    float scaleFactor = Director::getInstance()->getContentScaleFactor()/120;
    manaBarPlayer1 = Sprite::create("manabar.png", Rect(0,0,0,0));
    manaBarPlayer1->setScale(250*scaleFactor,150*scaleFactor);
    manaBarPlayer1->setPosition(Vec2(origin.x + 150,
                                     origin.y + visibleSize.height - 25));
    this->addChild(manaBarPlayer1, 1);

    manaBarPlayer2 = Sprite::create("manabar.png", Rect(0,0,0,0));
    manaBarPlayer2->setScale(250*scaleFactor,150*scaleFactor);
    manaBarPlayer2->setPosition(Vec2(origin.x + visibleSize.width -  150,
                                     origin.y + visibleSize.height - 25));
    this->addChild(manaBarPlayer2, 1);

    //ability buttons
    auto button = AbilityButton::createAbilityButton(&abilityLargeBall,CARD_BUTTON_SIZE,0);
    button->setPosition(Vec2(origin.x + 60,origin.y + visibleSize.height/2 - 150));
    addChild(button);button = AbilityButton::createAbilityButton(&abiliityFloatingBeam,CARD_BUTTON_SIZE,0);
    button->setPosition(Vec2(origin.x + 60,origin.y  + visibleSize.height/2 - 50));
    addChild(button);
    button = AbilityButton::createAbilityButton(&abilitySmallCube,CARD_BUTTON_SIZE,0);
    button->setPosition(Vec2(origin.x + 60,origin.y +  + visibleSize.height/2 + 50));
    addChild(button);
    button = AbilityButton::createAbilityButton(&abilityExplosion,CARD_BUTTON_SIZE,0);
    button->setPosition(Vec2(origin.x + 60,origin.y +  + visibleSize.height/2 + 150));
    addChild(button);

    button = AbilityButton::createAbilityButton(&abilityLargeBall,CARD_BUTTON_SIZE,1);
    button->setPosition(Vec2(origin.x  + visibleSize.width - 60,origin.y + visibleSize.height/2 - 150));
    addChild(button);
    button = AbilityButton::createAbilityButton(&abiliityFloatingBeam,CARD_BUTTON_SIZE,1);
    button->setPosition(Vec2(origin.x + visibleSize.width - 60,origin.y + visibleSize.height/2 - 50));
    addChild(button);
    button = AbilityButton::createAbilityButton(&abilitySmallCube,CARD_BUTTON_SIZE,1);
    button->setPosition(Vec2(origin.x + visibleSize.width - 60,origin.y + visibleSize.height/2 + 50));
    addChild(button);
    button = AbilityButton::createAbilityButton(&abilityExplosion,CARD_BUTTON_SIZE,1);
    button->setPosition(Vec2(origin.x + visibleSize.width - 60,origin.y + visibleSize.height/2 + 150));
    addChild(button);

    GameController* gameController = GameController::GetInstance();
    gameController->RegisterAbility(&abilityLargeBall);
    gameController->RegisterAbility(&abiliityFloatingBeam);
    gameController->RegisterAbility(&abilitySmallCube);
    gameController->RegisterAbility(&abilityExplosion);



    return true;
}

void GameplayUI::update(float dt){
    scoreLabel->setString(std::to_string(GameController::GetInstance()->GetPlayerPoint(0)) + " : " + std::to_string(GameController::GetInstance()->GetPlayerPoint(1)));

    //mana sprite update
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    float manaRatio = GameController::GetInstance()->playerOneMana/GameController::GetInstance()->MAX_MANA;
    manaBarPlayer1->setTextureRect(Rect(0,0,manaRatio*120,20));
    manaBarPlayer1->setPosition(Vec2(origin.x  + manaRatio*150,
                                     origin.y + visibleSize.height - 25));

    manaRatio = GameController::GetInstance()->playerTwoMana/GameController::GetInstance()->MAX_MANA;
    manaBarPlayer2->setTextureRect(Rect((1-manaRatio)*120,0,manaRatio*120,20));
    manaBarPlayer2->setPosition(Vec2(origin.x  + visibleSize.width - manaRatio*150,
                                     origin.y + visibleSize.height - 25));

}
