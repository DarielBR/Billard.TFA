#include "Ball.h"

USING_NS_CC;

Ball::Ball(ball_group group, int number, std::string faceImage, cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position) {
	faceGroup = group;
	faceNumber = number;
	faceSprite = cocos2d::Sprite::create(faceImage);
	faceSprite->setPosition(position);
	
	shineSprite = cocos2d::Sprite::create("res/ball_shine.png");
	shineSprite->setPosition(Vec2(position.x -600, position.y -300));
	//shineSprite->setScale(.10f);
	//shineSprite->setPosition(Vec2(position.x-41, position.y+41));
	phBody = cocos2d::PhysicsBody::createCircle(shineSprite->getBoundingBox().size.width / 2, cocos2d::PhysicsMaterial(density,
																													   restitution,
																													   friction));
	phBody->setDynamic(true);
	faceSprite->addComponent(phBody);
	faceSprite->addChild(shineSprite);
	scene->addChild(faceSprite, zOrder);

	faceSprite->setScale(.12f);
}

void Ball::setScale(float scale) {
	//shineSprite->setScale(scale);
	faceSprite->setScale(scale);
}