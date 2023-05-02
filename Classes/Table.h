#pragma once
#ifndef __TABLE_H__
#define __TABLE_H__

#include <string.h>
#include "cocos2d.h"

enum table_half { LEFT, RIGHT, CENTER};

class Table {
private:
	int headStringX = 545;
	cocos2d::Vec2 headSpot = cocos2d::Vec2(545, 550);
	cocos2d::Vec2 centerSpot = cocos2d::Vec2(750, 550);
	cocos2d::Vec2 footSpot = cocos2d::Vec2(965,550);
	//cocos2d::Vec2 railBorder[2] = {cocos2d::Vec2::ZERO, cocos2d::Vec2::ZERO};
public:
	cocos2d::Sprite* tableSprite;
	cocos2d::Node* tableBorder;
	cocos2d::PhysicsBody* phBody;
	cocos2d::Node* pocketUpLeft;
	cocos2d::Node* pocketUpCenter;
	cocos2d::Node* pocketUpRight;
	cocos2d::Node* pocketDownLeft;
	cocos2d::Node* pocketDownCenter;
	cocos2d::Node* pocketDownRight;

	//constructor
	Table(cocos2d::Scene* scene, int zOrder, cocos2d::Vec2 position);
	//behavior
	int getHeadStringX() { return headStringX; };
	cocos2d::Vec2 getHeadSpot() { return headSpot; };
	cocos2d::Vec2 getFootSpot() { return footSpot; };
	cocos2d::Vec2 getOffsetFromFootSpot(int ballPositions, table_half side);
	//Ball(ball_group group, int number, std::string faceImage);

	void setScale(float scale);
};

#endif // __TABLE_H__
