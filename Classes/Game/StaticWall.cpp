#include "StaticWall.h"


#include <string>
#include <iostream>


StaticWall* StaticWall::createWall(Size size, float restitution, float friction){
	StaticWall* wall = StaticWall::create();

	wall->body = PhysicsBody::createBox(size,
						   PhysicsMaterial(1, restitution, friction));
	wall->body->setDynamic(false);

	wall->addComponent(wall->body);

    wall->spriteChild->setScale(size.width*wall->spriteScale,size.height*wall->spriteScale);

    return wall;
}
bool StaticWall::init(){
	spriteChild = Sprite::create("square.png");
    spriteScale = Director::getInstance()->getContentScaleFactor()/128;
	addChild(spriteChild);
    return true;
}
