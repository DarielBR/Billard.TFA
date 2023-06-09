#include "Ball.h"
#include "Table.h"

USING_NS_CC;

Ball::Ball(int number, cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position) {

	faceNumber = number;

	std::string faceImage = "";
	switch (number) {
		case 0:
			faceImage = "img/cue_ball.png";
			faceGroup = ball_group::CUE;
			allowRotation = false;
			break;
		case 1:
			faceImage = "img/1.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 2:
			faceImage = "img/2.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 3:
			faceImage = "img/3.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 4:
			faceImage = "img/4.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 5:
			faceImage = "img/5.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 6:
			faceImage = "img/6.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 7:
			faceImage = "img/7.png";
			faceGroup = ball_group::SOLID;
			allowRotation = true;
			break;
		case 8:
			faceImage = "img/8.png";
			faceGroup = ball_group::EIGHT;
			allowRotation = true;
			break;
		case 9:
			faceImage = "img/9.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 10:
			faceImage = "img/10.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 11:
			faceImage = "img/11.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 12:
			faceImage = "img/12.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 13:
			faceImage = "img/13.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 14:
			faceImage = "img/14.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		case 15:
			faceImage = "img/15.png";
			faceGroup = ball_group::STRIPED;
			allowRotation = true;
			break;
		default:
			faceImage = "img/cue_ball.png";
			faceGroup = ball_group::CUE;
			allowRotation = false;
	}
	faceSprite = cocos2d::Sprite::create(faceImage);
	faceSprite->setPosition(position);
	
	shineSprite = cocos2d::Sprite::create("img/ball_shine.png");
	shineSprite->setAnchorPoint(Vec2(0.0f,0.0f));
	phBody = cocos2d::PhysicsBody::createCircle(shineSprite->getBoundingBox().size.width / 2, cocos2d::PhysicsMaterial(density,
																													   restitution,
																													   friction));
	phBody->setDynamic(true);
	phBody->setLinearDamping(damping);
	phBody->setAngularDamping(damping);
	phBody->setRotationEnable(allowRotation);
	phBody->setTag(faceNumber);
	phBody->setCategoryBitmask(0x03); //0011 will collide with the border and the pockets
	phBody->setCollisionBitmask(0x03); //0011
	phBody->setContactTestBitmask(0x03); //0011

	faceSprite->addComponent(phBody);
	faceSprite->addChild(shineSprite);
	faceSprite->setTag(faceNumber);
	scene->addChild(faceSprite, zOrder);

	//faceSprite->setScale(.12f);
}