#pragma once

#ifndef __BALL_H__
#define __BALL_H__

#include <string.h>
#include "cocos2d.h"

enum ball_group {SOLID, STRIPED, EIGHT, CUE};

class Ball{
private:
	int faceNumber;
	ball_group faceGroup;
	//physics values
	float density = 1.5;
	float restitution = 0.8f;
	float friction = 1.0;
	float damping = 0.25;
	float angularDamping = 0.25;

public:
	cocos2d::Sprite* faceSprite;
	cocos2d::Sprite* shineSprite;
	cocos2d::PhysicsBody* phBody;

	//constructor
	Ball(int number, cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position);
	//behavior
	bool isSolid() { return faceGroup == SOLID; };
	bool isStriped() { return faceGroup == STRIPED; };
	bool isCueBall() { return faceGroup == CUE; };
	bool isEightBall() { return faceGroup == EIGHT; };
	void setPosition(cocos2d::Vec2 position) { faceSprite->setPosition(position); };
	//void rotationUpdate(float dt);
	//Ball(ball_group group, int number, std::string faceImage);

	void setScale(float scale);
};

#endif // __BALL_H__