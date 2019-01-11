#include "Basket.h"

#include "GameController.h"
#include "TargetBall.h"
#include <string>
#include <iostream>


Basket* Basket::createBasket(Size size, bool isPlayerOne, Color3B color, float restitution, float friction){
	Basket* basket = Basket::create();

	basket->body = PhysicsBody::createBox(size,
										PhysicsMaterial(1, restitution, friction));
	basket->body->setDynamic(false);

    basket->body->setContactTestBitmask(0xFFFFFFFF);
	basket->addComponent(basket->body);

	basket->spriteChild->setScale(size.width*basket->spriteScale,size.height*basket->spriteScale);

	basket->spriteChild->setColor(color);

	basket->isPlayerOne = isPlayerOne;

	return basket;
}
bool Basket::init(){
	spriteChild = Sprite::create("square.png");
	spriteScale = Director::getInstance()->getContentScaleFactor()/128;
	addChild(spriteChild);


    //adds contact event listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Basket::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool Basket::onContactBegin(PhysicsContact& contact){
    //removeFromParent();
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if(nodeA){
        if(nodeA->getTag()==TargetBall::DEFAULT_TAG && nodeB == this){
            GameController::GetInstance()->AddPlayerPoint(isPlayerOne);
            nodeA->removeFromParentAndCleanup(true);
        }
    }

    if(nodeB){
        if(nodeB->getTag()==TargetBall::DEFAULT_TAG && nodeA == this){
            GameController::GetInstance()->AddPlayerPoint(isPlayerOne);
            nodeB->removeFromParentAndCleanup(true);
        }
    }

    return true;
}

