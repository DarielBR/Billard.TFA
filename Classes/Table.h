#pragma once
#ifndef __TABLE_H__
#define __TABLE_H__

#include <string.h>
#include "cocos2d.h"

class Table {
private:
	//cocos2d::Vec2 railBorder[2] = {cocos2d::Vec2::ZERO, cocos2d::Vec2::ZERO};
public:
	cocos2d::Sprite* tableSprite;
	cocos2d::Node* tableBorder;
	cocos2d::PhysicsBody* phBody;

	//constructor
	Table(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position);
	//behavior

	//Ball(ball_group group, int number, std::string faceImage);

	void setScale(float scale);
};

#endif // __TABLE_H__
